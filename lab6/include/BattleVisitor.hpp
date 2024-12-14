#ifndef BATTLEVISITOR_HPP
#define BATTLEVISITOR_HPP

#include "Visitor.hpp"
#include "NPC.hpp"
#include "Toad.hpp"
#include "Bull.hpp"
#include "Dragon.hpp"
#include <memory>
#include <vector>

class BattleVisitor : public Visitor {
public:
    BattleVisitor(int range, std::vector<std::unique_ptr<NPC>>& npcs);
    void visit(Dragon* dragon) override;
    void visit(Bull* bull) override;
    void visit(Toad* toad) override;
private:
    int range;
    std::vector<std::unique_ptr<NPC>>& npcs;
};

#endif