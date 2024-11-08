#include "include/list.hpp"
#include "include/allocator.hpp"
#include <iostream>


struct my_struct {
    int age;
    double weight;
};

int main() {
    DynamicMemoryResource mem_resource;
    std::pmr::polymorphic_allocator<int> int_alloc(&mem_resource);
    List<int> int_list(&mem_resource);
    int_list.PushBack(100);
    int_list.PushBack(111);

    for (auto value : int_list) {
        std::cout << value << std::endl;
    }
    std::cout << std::endl;

    List<my_struct> struct_list(&mem_resource);
    struct_list.PushBack(my_struct{10, 35});
    struct_list.PushBack(my_struct{30, 88});

    for (auto& item : struct_list) {
        std::cout << "age: " << item.age << ", weight: " << item.weight << std::endl;
    }

    return 0;
}
