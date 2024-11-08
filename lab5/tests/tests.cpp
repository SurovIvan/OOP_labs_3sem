#include "../include/list.hpp"  
#include "../include/allocator.hpp"  
#include "gtest/gtest.h"

TEST(ListTest, DefaultConstructor) {
    DynamicMemoryResource mr;
    List<int> list(&mr);
    ASSERT_TRUE(list.IsEmpty());
    ASSERT_EQ(list.Size(), 0);
}

TEST(ListTest, ConstructorWithSize) {
    DynamicMemoryResource mr;
    List<int> list(5, &mr);
    ASSERT_FALSE(list.IsEmpty());
    ASSERT_EQ(list.Size(), 5);
}

TEST(ListTest, ConstructorWithInitializerList) {
    DynamicMemoryResource mr;
    List<int> list({1, 2, 3, 4, 5}, &mr);
    ASSERT_FALSE(list.IsEmpty());
    ASSERT_EQ(list.Size(), 5);
    ASSERT_EQ(list.Front(), 1);
    ASSERT_EQ(list.Back(), 5);
}

TEST(ListTest, CopyConstructor) {
    DynamicMemoryResource mr;
    List<int> original(&mr);
    original.PushBack(1);
    original.PushBack(2);
    original.PushBack(3);

    List<int> copy(original);
    ASSERT_FALSE(copy.IsEmpty());
    ASSERT_EQ(copy.Size(), 3);
    ASSERT_EQ(copy.Front(), 1);
    ASSERT_EQ(copy.Back(), 3);
}

TEST(ListTest, MoveConstructor) {
    DynamicMemoryResource mr;
    List<int> original(&mr);
    original.PushBack(1);
    original.PushBack(2);
    original.PushBack(3);

    List<int> moved(std::move(original));
    ASSERT_TRUE(original.IsEmpty());
    ASSERT_EQ(original.Size(), 0);
    ASSERT_FALSE(moved.IsEmpty());
    ASSERT_EQ(moved.Size(), 3);
    ASSERT_EQ(moved.Front(), 1);
    ASSERT_EQ(moved.Back(), 3);
}

TEST(ListTest, PushBack) {
    DynamicMemoryResource mr;
    List<int> list(&mr);
    list.PushBack(1);
    list.PushBack(2);
    ASSERT_FALSE(list.IsEmpty());
    ASSERT_EQ(list.Size(), 2);
    ASSERT_EQ(list.Front(), 1);
    ASSERT_EQ(list.Back(), 2);
}

TEST(ListTest, PushFront) {
    DynamicMemoryResource mr;
    List<int> list(&mr);
    list.PushFront(1);
    list.PushFront(2);
    ASSERT_FALSE(list.IsEmpty());
    ASSERT_EQ(list.Size(), 2);
    ASSERT_EQ(list.Front(), 2);
    ASSERT_EQ(list.Back(), 1);
}

TEST(ListTest, PopBack) {
    DynamicMemoryResource mr;
    List<int> list(&mr);
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);

    list.PopBack();
    ASSERT_EQ(list.Size(), 2);
    ASSERT_EQ(list.Back(), 2);
    list.PopBack();
    ASSERT_EQ(list.Size(), 1);
    ASSERT_EQ(list.Back(), 1);
    list.PopBack();
    ASSERT_TRUE(list.IsEmpty());
}

TEST(ListTest, PopFront) {
    DynamicMemoryResource mr;
    List<int> list(&mr);
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);

    list.PopFront();
    ASSERT_EQ(list.Size(), 2);
    ASSERT_EQ(list.Front(), 2);
    list.PopFront();
    ASSERT_EQ(list.Size(), 1);
    ASSERT_EQ(list.Front(), 3);
    list.PopFront();
    ASSERT_TRUE(list.IsEmpty());
}

TEST(ListTest, Find) {
    DynamicMemoryResource mr;
    List<int> list(&mr);
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    list.PushBack(4);
    list.PushBack(5);

    auto it = list.Find(3);
    ASSERT_EQ(*it, 3);
    it = list.Find(6);
    ASSERT_EQ(it, list.end());
}

TEST(ListTest, Erase) {
    DynamicMemoryResource mr;
    List<int> list(&mr);
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    list.PushBack(4);
    list.PushBack(5);

    auto it = list.Find(3);
    list.Erase(it);
    ASSERT_EQ(list.Size(), 4);
    ASSERT_EQ(list.Find(3), list.end());
}

TEST(ListTest, Insert) {
    DynamicMemoryResource mr;
    List<int> list(&mr);
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(4);
    list.PushBack(5);

    auto it = list.Find(4);
    list.Insert(it, 3);
    ASSERT_EQ(list.Size(), 5);

    // Проверяем, что элемент 3 вставлен перед элементом 4
    auto it3 = list.Find(3);
    auto it4 = list.Find(4);
    ASSERT_EQ(*it3, 3);
    ASSERT_EQ(*it4, 4);
    
}

TEST(ListTest, Iterator) {
    DynamicMemoryResource mr;
    List<int> list(&mr);
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);

    int count = 1;
    for (int x : list) {
        ASSERT_EQ(count, x);
        ++count;
    }
}

struct MyStruct {
    int a;
    double b;
    std::string c;

    bool operator==(const MyStruct &other) const {
        return a == other.a && b == other.b && c == other.c;
    }
};

TEST(ListTest, ComplexType) {
    DynamicMemoryResource mr;
    List<MyStruct> list(&mr);

    list.PushBack({1, 2.5, "hello"});
    list.PushBack({2, 3.14, "world"});

    ASSERT_EQ(2, list.Size());
    ASSERT_EQ((MyStruct{1, 2.5, "hello"}), list.Front());
    ASSERT_EQ((MyStruct{2, 3.14, "world"}), list.Back());
}
TEST(DynamicMemoryResourceTest, AllocateAndDeallocate) {
    DynamicMemoryResource mr;
    void* p1 = mr.allocate(16, 16);  
    ASSERT_NE(nullptr, p1);           

    mr.deallocate(p1, 16, 16);        

    
    void* p2 = mr.allocate(16, 16);   
    ASSERT_NE(nullptr, p2);           

    mr.deallocate(p2, 16, 16);        
}

TEST(DynamicMemoryResourceTest, AllocateMultipleBlocks) {
    DynamicMemoryResource mr;
    void* p1 = mr.allocate(16, 16);
    ASSERT_NE(nullptr, p1);

    void* p2 = mr.allocate(32, 16);   
    ASSERT_NE(nullptr, p2);
    ASSERT_NE(p1, p2);                

    mr.deallocate(p1, 16, 16);
    mr.deallocate(p2, 32, 16);
}

TEST(DynamicMemoryResourceTest, DeallocateValidPointerWithDifferentSize) {
    DynamicMemoryResource mr;
    void* p = mr.allocate(16, 16);
    ASSERT_NE(nullptr, p);

    
    mr.deallocate(p, 32, 16);  

    mr.deallocate(p, 16, 16);
}

TEST(DynamicMemoryResourceTest, MultipleDeallocateSamePointer) {
    DynamicMemoryResource mr;
    void* p = mr.allocate(16, 16);
    ASSERT_NE(nullptr, p);

    mr.deallocate(p, 16, 16);  

   
    mr.deallocate(p, 16, 16); 
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}