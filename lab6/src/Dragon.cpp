#include "Dragon.hpp"

Dragon::Dragon(const std::string& name, int x, int y) : NPC(name, x, y) {}
void Dragon::accept(Visitor& Visitor) {Visitor.visit(this);}
bool Dragon::fight(NPC* other) { return dynamic_cast<Bull*>(other) != nullptr; } 

const std::string Dragon::type = "Dragon";