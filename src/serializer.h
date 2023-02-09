#pragma once

#include <map>
#include <string>
#include <vector>

struct ListNode {
    ListNode * prev;
    ListNode * next;
    ListNode * rand; // указатель на произвольный элемент данного списка, либо NULL
    std::string data;
};

struct SerializedNodeHeader {
    uint32_t randPointer;
    uint64_t stringSize;
} __attribute__((packed));

class List {
public:
    void Serialize(FILE *file) // сохранение в файл (файл открыт с помощью fopen(path, "wb")
    {
        auto buffer = SerializeToBuffer();
        uint64_t full_data_size = buffer.size();
        fwrite(&full_data_size, sizeof(full_data_size), 1, file);
        fwrite(buffer.data(), full_data_size, 1, file);
    }

    void Deserialize(FILE *file) // загрузка из файла (файл открыт с помощью fopen(path, "rb")
    {
        uint64_t full_data_size;
        fread(&full_data_size, sizeof(full_data_size), 1, file);
        std::vector<uint8_t> buffer(full_data_size);
        fread(buffer.data(), full_data_size, 1, file);
        DeserializeFromBuffer(buffer);
    }

    std::vector<uint8_t> SerializeToBuffer()
    {
        std::vector<uint8_t> buffer(sizeof(count) + count * sizeof(SerializedNodeHeader) + CalculateTotalStringSize());
        memcpy(buffer.data(), &count, sizeof(count));
        std::size_t buffer_pos = sizeof(count);

        auto node_to_position_map = CalcNodeToPositionMap();

        auto next = head;
        while(next && next != tail->next)
        {
            buffer_pos = SerializeNode(node_to_position_map, buffer, buffer_pos, next);
            next = next->next;
        }
        return buffer;
    }

    void DeserializeFromBuffer(const std::vector<uint8_t>& buffer)
    {
        memcpy(&count, buffer.data(), sizeof(count));
        std::size_t buffer_pos = sizeof(count);
        auto allNodes = CreateEmptyNodes();
        for (auto node: allNodes)
        {
            buffer_pos = DeserializeNode(allNodes, buffer, buffer_pos, node);
        }
    }

    bool operator==(const List& other) const
    {
        if (count != other.count) return false;

        ListNode* myNode = head;
        auto myNodeToPositionMap = CalcNodeToPositionMap();
        ListNode* otherNode = other.head;
        auto otherNodeToPositionMap = other.CalcNodeToPositionMap();

        while (myNode && myNode != tail->next)
        {
            if (myNodeToPositionMap[myNode] != otherNodeToPositionMap[otherNode]) return false;
            if (myNodeToPositionMap[myNode->rand] != otherNodeToPositionMap[otherNode->rand]) return false;
            if (myNode->data != otherNode->data) return false;

            myNode = myNode->next;
            if (otherNode == other.tail->next) return false;
            otherNode = otherNode->next;
        }

        if (myNode == nullptr && otherNode == nullptr) return true;
        return otherNode == other.tail->next;
    }

protected:
    std::vector<ListNode*> CreateEmptyNodes()
    {
        std::vector<ListNode*> res(count);
        if (count == 0)
        {
            head = nullptr;
            tail = nullptr;
            return res;
        }

        head = new ListNode();
        head->prev = nullptr;
        res[0] = head;

        auto prev = head;
        for(int i = 1; i < count; i++)
        {
            auto node = new ListNode();
            prev->next = node;
            node->prev = prev;

            res[i] = node;
            prev = node;
        }

        tail = prev;
        tail->next = nullptr;
        return res;
    }

private:
    std::size_t SerializeNode(
            const std::map<ListNode*, uint32_t>& node_to_position_map,
            std::vector<uint8_t>& buffer,
            std::size_t buffer_pos,
            ListNode* node)
    {
        SerializedNodeHeader header {
            .randPointer = node_to_position_map.at(node->rand),
            .stringSize = node->data.size()
        };

        memcpy(buffer.data() + buffer_pos, &header, sizeof(SerializedNodeHeader));
        buffer_pos += sizeof(SerializedNodeHeader);
        memcpy(buffer.data() + buffer_pos, node->data.data(), header.stringSize);
        buffer_pos += header.stringSize;
        return buffer_pos;
    }

    std::size_t DeserializeNode(
            const std::vector<ListNode*>& allNodes,
            const std::vector<uint8_t> &buffer,
            std::size_t buffer_pos,
            ListNode* node)
    {
        SerializedNodeHeader header;
        memcpy(&header, buffer.data() + buffer_pos, sizeof(SerializedNodeHeader));
        buffer_pos += sizeof(SerializedNodeHeader);

        node->rand = allNodes[header.randPointer];

        node->data.resize(header.stringSize);
        memcpy(node->data.data(), buffer.data() + buffer_pos, header.stringSize);
        buffer_pos += header.stringSize;

        return buffer_pos;
    }

    std::map<ListNode*, uint32_t> CalcNodeToPositionMap() const
    {
        std::map<ListNode*, uint32_t> res;
        auto next = head;
        uint32_t pos = 0;
        while(next && next != tail->next)
        {
            res[next] = pos;
            next = next->next;
            pos++;
        }
        return res;
    }

    std::size_t CalculateTotalStringSize() const
    {
        std::size_t total_size = 0;
        auto next = head;
        while(next && next != tail->next)
        {
            total_size += next->data.size();
            next = next->next;
        }
        return total_size;
    }

protected: // only for convinience taking in account that is test assignment
    ListNode *head;
    ListNode *tail;
    int32_t count; // Specify concrete byte size
};

class RandomDataList: public List
{
public:
    RandomDataList(uint32_t count)
    {
        this->count = count;
        auto nodes = CreateEmptyNodes();
        for (auto node: nodes)
        {
            node->rand = nodes[rand()%nodes.size()];
            node->data = GenerateRandomString();
        }
    }

private:
    std::string GenerateRandomString()
    {
        static const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0987654321_";
        int randomSize = rand() % 1000;
        std::string res(randomSize, '0');
        for (int i = 0; i < randomSize; i++)
        {
            res[i] = letters[rand() % letters.size()];
        }
        return res;

    }
};