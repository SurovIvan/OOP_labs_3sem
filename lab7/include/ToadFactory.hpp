#ifndef TOADFACTORY_HPP
#define TOADFACTORY_HPP

#include "NPCFactory.hpp"
#include "Toad.hpp"

class ToadFactory : public NPCFactory {
public:
    std::unique_ptr<NPC> createNPC(const std::string& name, int x, int y) override {
        return std::make_unique<Toad>(name, x, y);
    }
};

#endif