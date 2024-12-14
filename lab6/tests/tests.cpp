#include <gtest/gtest.h>
#include <memory>
#include "NPCFactory.hpp"
#include "Bull.hpp"
#include "Toad.hpp"
#include "Dragon.hpp"
#include "BattleVisitor.hpp"
#include "LoggingVisitior.hpp"
#include "BullFactory.hpp"  
#include "ToadFactory.hpp" 
#include "DragonFactory.hpp"  


TEST(NPCFactoryTest, CreateNPC) {
    NPCFactory::registerFactory("Bull", std::make_unique<BullFactory>());
    NPCFactory::registerFactory("Toad", std::make_unique<ToadFactory>());
    NPCFactory::registerFactory("Dragon", std::make_unique<DragonFactory>());

    auto bull = NPCFactory::create("Bull", "Bully", 10, 20);
    auto toad = NPCFactory::create("Toad", "Toady", 30, 40);
    auto dragon = NPCFactory::create("Dragon", "Draggy", 50, 60);

    ASSERT_NE(bull, nullptr);  
    ASSERT_NE(toad, nullptr);  
    ASSERT_NE(dragon, nullptr); 

    EXPECT_EQ(typeid(*bull), typeid(Bull));  
    EXPECT_EQ(typeid(*toad), typeid(Toad)); 
    EXPECT_EQ(typeid(*dragon), typeid(Dragon));  

    EXPECT_EQ(bull->getName(), "Bully");  
    EXPECT_EQ(bull->getX(), 10); 
    EXPECT_EQ(bull->getY(), 20);  

    EXPECT_EQ(toad->getName(), "Toady"); 
    EXPECT_EQ(toad->getX(), 30); 
    EXPECT_EQ(toad->getY(), 40); 

    EXPECT_EQ(dragon->getName(), "Draggy");  
    EXPECT_EQ(dragon->getX(), 50);  
    EXPECT_EQ(dragon->getY(), 60);  
}

TEST(BattleVisitorTest, DragonEatsBull) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.emplace_back(std::make_unique<Dragon>("Draggy", 0, 0));
    npcs.emplace_back(std::make_unique<Bull>("Bully", 10, 10));

    BattleVisitor battleVisitor(100, npcs);

    npcs[0]->accept(battleVisitor);

    EXPECT_EQ(npcs.size(), 1);  
    EXPECT_EQ(typeid(*npcs[0]), typeid(Dragon));  
}

TEST(BattleVisitorTest, BullTramplesToad) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.emplace_back(std::make_unique<Bull>("Bully", 0, 0));
    npcs.emplace_back(std::make_unique<Toad>("Toady", 10, 10));

    BattleVisitor battleVisitor(100, npcs);

    npcs[0]->accept(battleVisitor);

    EXPECT_EQ(npcs.size(), 1);  
    EXPECT_EQ(typeid(*npcs[0]), typeid(Bull));  
}


TEST(BattleVisitorTest, ToadEscapes) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.emplace_back(std::make_unique<Toad>("Toady", 0, 0));
    npcs.emplace_back(std::make_unique<Bull>("Bully", 10, 10));

    BattleVisitor battleVisitor(100, npcs);

    npcs[0]->accept(battleVisitor);

    EXPECT_EQ(npcs.size(), 2);
    EXPECT_EQ(typeid(*npcs[0]), typeid(Toad)); 
}