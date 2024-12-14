#include "Bull.hpp"

Bull::Bull(const std::string& name, int x, int y) : NPC(name, x, y) {}
void Bull::accept(Visitor& Visitor) {Visitor.visit(this);}
bool Bull::fight(NPC* other) { return dynamic_cast<Toad*>(other) != nullptr; }

const std::string Bull::type = "Bull";