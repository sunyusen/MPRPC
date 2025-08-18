#include "test.pb.h"
#include <iostream>

int main() {
    Person p;
    p.set_name("Alice");
    p.set_id(123);
    std::string data;
    if (p.SerializeToString(&data)) {
        std::cout << "Serialized size: " << data.size() << std::endl;
    } else {
        std::cerr << "Serialization failed." << std::endl;
    }
    return 0;
}