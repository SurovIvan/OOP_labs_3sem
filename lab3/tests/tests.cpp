#include <gtest/gtest.h>
#include "../include/Rhomb.h"
#include "../include/Trapezoid.h"
#include "../include/Pentagon.h"
#include "../include/point.h"

// Rhomb tests
TEST(RhombTest, AreaCalculationSimple) {
    Rhomb r;
    std::istringstream input("-1 0 0 1 1 0 0 -1");
    input >> r;
    double area = static_cast<double>(r);
    ASSERT_NEAR(area, 2.0, 1e-6);
}

TEST(RhombTest, GeomCenterSimple) {
    Rhomb r;
    std::istringstream input("-1 0 0 1 1 0 0 -1");
    input >> r;
    Point center = r.calc_geom_center();
    ASSERT_NEAR(center._x, 0.0, 1e-6);
    ASSERT_NEAR(center._y, 0.0, 1e-6);
}

TEST(RhombTest, InvalidRhomb) {
    Rhomb r;
    std::istringstream input("0 0 1 1 2 2 3 3"); 
    ASSERT_EXIT((input >> r), ::testing::ExitedWithCode(1), "It's not a rhomb, your coordinates are wrong");
}

TEST(RhombTest, AreaCalculationLarge) {
    Rhomb r;
    std::istringstream input("-100 0 0 100 100 0 0 -100");
    input >> r;
    double area = static_cast<double>(r);
    ASSERT_NEAR(area, 20000.0, 1e-6);
}

TEST(RhombTest, GeomCenterLarge) {
    Rhomb r;
    std::istringstream input("-100 0 0 100 100 0 0 -100");
    input >> r;
    Point center = r.calc_geom_center();
    ASSERT_NEAR(center._x, 0.0, 1e-6);
    ASSERT_NEAR(center._y, 0.0, 1e-6);
}

// Trapezoid tests
TEST(TrapezoidTest, AreaCalculationSimple) {
    Trapezoid t;
    std::istringstream input("0 0 4 0 3 2 1 2");
    input >> t;
    double area = static_cast<double>(t);
    ASSERT_NEAR(area, 6.0, 1e-6);
}

TEST(TrapezoidTest, GeomCenterSimple) {
    Trapezoid t;
    std::istringstream input("0 0 4 0 3 2 1 2");
    input >> t;
    Point center = t.calc_geom_center();
    ASSERT_NEAR(center._x, 2.0, 1e-6);
    ASSERT_NEAR(center._y, 1.0, 1e-6);
}

TEST(TrapezoidTest, InvalidTrapezoid) {
    Trapezoid t;
    std::istringstream input("0 80 1 1 2 2 3 3"); 
    ASSERT_EXIT((input >> t), ::testing::ExitedWithCode(1), "It's not a trapezoid, your coordinates are wrong");
}

TEST(TrapezoidTest, AreaCalculationLarge) {
    Trapezoid t;
    std::istringstream input("0 0 100 0 50 50 -50 50");
    input >> t;
    double area = static_cast<double>(t);
    ASSERT_NEAR(area, 5000.0, 1e-6);
}

TEST(TrapezoidTest, GeomCenterLarge) {
    Trapezoid t;
    std::istringstream input("0 0 100 0 50 50 -50 50");
    input >> t;
    Point center = t.calc_geom_center();
    ASSERT_NEAR(center._x, 25.0, 1e-6);
    ASSERT_NEAR(center._y, 25.0, 1e-6);
}

// Pentagon tests

TEST(PentagonTest, InvalidPentagonCollinear) {
    Pentagon p;
    std::istringstream input("0 0 1 1 2 2 3 3 4 4"); 
    ASSERT_EXIT((input >> p), ::testing::ExitedWithCode(1), "It's not a pentagon, your coordinates are wrong");
}

TEST(PentagonTest, AreaCalculationSimple) {
    Pentagon p;
    std::istringstream input("0 0 1 0 1 1 0.5 1.5 0 1"); 
    input >> p;
    double area = static_cast<double>(p); 
    ASSERT_NEAR(area, 1.25, 1e-6); 
}

TEST(PentagonTest, GeomCenterSimple) {
    Pentagon p;
    std::istringstream input("0 0 1 0 1 1 0.5 1.5 0 1"); 
    input >> p;
    Point center = p.calc_geom_center(); 
    ASSERT_NEAR(center._x, 0.5, 1e-6); 
    ASSERT_NEAR(center._y, 0.7, 1e-6); 
}

TEST(PentagonTest, InvalidPentagon) {
    Pentagon p;
    std::istringstream input("0 0 1 1 2 2 3 3 4 4"); 
    ASSERT_EXIT((input >> p), ::testing::ExitedWithCode(1), "It's not a pentagon, your coordinates are wrong");
}

TEST(FigureTest, CopyAssignmentOperator) {
    Trapezoid t1;
    std::istringstream input1("0 0 4 0 3 2 1 2");
    input1 >> t1;

    Trapezoid t2; 
    t2 = t1; 

    ASSERT_TRUE(t1 == t2); 
}

TEST(FigureTest, MoveAssignmentOperator) {
    Trapezoid t1;
    std::istringstream input1("0 0 4 0 3 2 1 2");
    input1 >> t1; 

    Trapezoid t2; 
    t2 = std::move(t1); 

    ASSERT_TRUE(t2.is_trapezoid()); 
}


TEST(FigureTest, CopyConstructor) {
    Trapezoid t1;
    std::istringstream input1("0 0 4 0 3 2 1 2");
    input1 >> t1; 

    Trapezoid t2(t1); 

    ASSERT_TRUE(t1 == t2); 
}


TEST(FigureTest, MoveConstructor) {
    Trapezoid t1;
    std::istringstream input1("0 0 4 0 3 2 1 2");
    input1 >> t1; 

    Trapezoid t2(std::move(t1)); 

    ASSERT_TRUE(t2.is_trapezoid()); 
}


TEST(FigureTest, ComparisonOperator) {
    Trapezoid t1, t2;
    std::istringstream input1("0 0 4 0 3 2 1 2");
    std::istringstream input2("0 0 4 0 3 2 1 2");

    input1 >> t1; 
    input2 >> t2; 

    ASSERT_TRUE(t1 == t2); 
}







