#include "BattleVisitor.hpp"
#include <iostream>
#include <vector>

BattleVisitor::BattleVisitor(int range, std::vector<std::unique_ptr<NPC>>& npcs)
    : range(range), npcs(npcs) {}

void BattleVisitor::visit(Dragon* dragon) {
    std::cout << "Dragon " << dragon->getName() << " is eating a Bull!\n";
    std::vector<size_t> indicesToRemove;
    for (size_t i = 0; i < npcs.size(); ++i) {
        NPC* npc = npcs[i].get();
        if (dynamic_cast<Bull*>(npc) && abs(dragon->getX() - npc->getX()) <= range && abs(dragon->getY() - npc->getY()) <= range) {
            std::cout << "Dragon " << dragon->getName() << " ate Bull " << npc->getName() << "!\n";
            indicesToRemove.push_back(i);
        }
    }
    for (auto it = indicesToRemove.rbegin(); it != indicesToRemove.rend(); ++it) {
        npcs.erase(npcs.begin() + *it);
    }
}

void BattleVisitor::visit(Bull* bull) {
    std::cout << "Bull " << bull->getName() << " is trampling a Toad!\n";
    std::vector<size_t> indicesToRemove;
    for (size_t i = 0; i < npcs.size(); ++i) {
        NPC* npc = npcs[i].get();
        if (dynamic_cast<Toad*>(npc) && abs(bull->getX() - npc->getX()) <= range && abs(bull->getY() - npc->getY()) <= range) {
            std::cout << "Bull " << bull->getName() << " trampled Toad " << npc->getName() << "!\n";
            indicesToRemove.push_back(i);
        }
    }
    for (auto it = indicesToRemove.rbegin(); it != indicesToRemove.rend(); ++it) {
        npcs.erase(npcs.begin() + *it);
    }
}

void BattleVisitor::visit(Toad* toad) {
    std::cout << "Toad " << toad->getName() << " is trying to escape!\n";
}