#include "serializer.h"
#include <ctime>
#include <iostream>

int main() {
    srand(time(NULL));
    std::cout << "Enter node count for serialized list:" << std::endl;

    uint32_t nodeCount;
    std::cin >> nodeCount;

    std::cout << "Enter filename for serialization:" << std::endl;

    std::string filename;
    std::getline(std::cin >> std::ws, filename);

    RandomDataList list(nodeCount);
    auto file = fopen(filename.data(), "wb");
    if (file != NULL) {
        list.Serialize(file);
        fclose(file);
    } else {
        std::cout << "Can't open file for writing" << std::endl;
        return 1;
    }

    List deserialized;
    file = fopen(filename.data(), "rb");
    if (file != NULL) {
        deserialized.Deserialize(file);
        fclose(file);
    } else {
        std::cout << "Can't open file for reading" << std::endl;
        return 1;
    }

    if (list == deserialized) {
        std::cout << "Lists are identical after roundtrip serialization" << std::endl;
    } else {
        std::cout << "Roundtrip serialization error, lists are not identical" << std::endl;
    }
}