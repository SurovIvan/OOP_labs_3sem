#ifndef BULLFACTORY_HPP
#define BULLFACTORY_HPP

#include "NPCFactory.hpp"
#include "Bull.hpp"

class BullFactory : public NPCFactory {
public:
    std::unique_ptr<NPC> createNPC(const std::string& name, int x, int y) override {
        return std::make_unique<Bull>(name, x, y);
    }
};

#endif