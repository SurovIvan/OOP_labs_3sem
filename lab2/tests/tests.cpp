#include <gtest/gtest.h>
#include "../include/Twelve.h"

// Тестирование конструктора по умолчанию
TEST(TwelveTest, DefaultConstructor) {
    Twelve t;
    EXPECT_EQ(t.size(), 0);  
}

// Тестирование конструктора с std::string
TEST(TwelveTest, StringConstructor) {
    Twelve t("12345");
    EXPECT_EQ(t.size(), 5);  
    EXPECT_EQ(t[0], '1');    
    EXPECT_EQ(t[1], '2');
}

// Тестирование конструктора копирования
TEST(TwelveTest, CopyConstructor) {
    Twelve t1("123");
    Twelve t2 = t1; 
    EXPECT_EQ(t1, t2);
}

// Тестирование конструктора перемещения
TEST(TwelveTest, MoveConstructor) {
    Twelve t1("123");
    Twelve t2 = std::move(t1);  
    EXPECT_EQ(t2.size(), 3);    
    EXPECT_EQ(t1.size(), 0);    
}

// Тестирование оператора присваивания
TEST(TwelveTest, AssignmentOperator) {
    Twelve t1("123");
    Twelve t2;
    t2 = t1; 
    EXPECT_EQ(t1, t2);  
}

// Тестирование сложения чисел в 12-ричной системе
TEST(TwelveTest, AdditionOperator) {
    Twelve t1("1B");  
    Twelve t2("3A");  
    Twelve result = t1 + t2;
    EXPECT_EQ(result.size(), 3);  
    EXPECT_EQ(result[0], '4');    
    EXPECT_EQ(result[1], '9');    
}

// Тестирование вычитания чисел в 12-ричной системе
TEST(TwelveTest, SubtractionOperator) {
    Twelve t1("1B");  
    Twelve t2("3A");  
    Twelve result = t1 - t2;
    EXPECT_EQ(result.size(), 1);  
    EXPECT_EQ(result[0], 'A'); 
}

// Тестирование оператора сравнения
TEST(TwelveTest, EqualityOperator) {
    Twelve t1("123");
    Twelve t2("123");
    EXPECT_TRUE(t1 == t2); 
}

// Тестирование оператора инкремента
TEST(TwelveTest, IncrementOperator) {
    Twelve t1("321");
    ++t1;
    EXPECT_EQ(t1[0], '4'); 
}

// Тестирование деструктора
TEST(TwelveTest, DestructorTest) {
    Twelve* t = new Twelve("123");
    delete t;  
}

// Тестирование многоразового присваивания
TEST(TwelveTest, MultipleAssignments) {
    Twelve t1("A3B1");
    Twelve t2;
    Twelve t3;
    t2 = t1;
    t3 = t2;
    EXPECT_EQ(t1, t2);
    EXPECT_EQ(t2, t3);
}

// Тестирование инкремента до переполнения
TEST(TwelveTest, IncrementToOverflow) {
    Twelve t1("B"); // 11
    ++t1;           // 11 + 1 = 12 -> "10"
    EXPECT_EQ(t1.size(), 2);
    EXPECT_EQ(t1[0], '0');
    EXPECT_EQ(t1[1], '1');
}

// Тестирование декремента до нуля
TEST(TwelveTest, DecrementToZero) {
    Twelve t1("1"); // 1
    --t1;           // 1 - 1 = 0 -> "0"
    EXPECT_EQ(t1.size(), 1);
    EXPECT_EQ(t1[0], '0');
}

// Тестирование сравнения разных размеров
TEST(TwelveTest, ComparisonDifferentSizes) {
    Twelve t1("1");    // 1
    Twelve t2("10");   // 0,1
    EXPECT_TRUE(t1 < t2);
    EXPECT_FALSE(t2 < t1);
    EXPECT_TRUE(t2 > t1);
    EXPECT_FALSE(t1 > t2);
}

// Тестирование сложения разных размеров
TEST(TwelveTest, AdditionDifferentSizes) {
    Twelve t1("B");    
    Twelve t2("1");    
    Twelve result = t1 + t2; 
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], '0');
    EXPECT_EQ(result[1], '1');
}

// Тестирование вычитания до нуля при равных числах
TEST(TwelveTest, SubtractionEqualNumbers) {
    Twelve t1("A3B1");
    Twelve t2("A3B1");
    Twelve result = t1 - t2;
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], '0');
}
