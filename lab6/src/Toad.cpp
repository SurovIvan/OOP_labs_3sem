#include "Toad.hpp"

Toad::Toad(const std::string& name, int x, int y) : NPC(name, x, y) {}
void Toad::accept(Visitor& Visitor) {Visitor.visit(this);}
bool Toad::fight(NPC* other) { return false; }
const std::string Toad::type = "Toad";