#include "LoggingVisitior.hpp"

LoggingVisitor::LoggingVisitor(std::ostream& os) : os(os) {}

void LoggingVisitor::visit(Toad* toad) {
    os << "Toad: " << toad->getName() << " at (" << toad->getX() << ", " << toad->getY() << ")\n";
}

void LoggingVisitor::visit(Bull* bull) {
    os << "Bull: " << bull->getName() << " at (" << bull->getX() << ", " << bull->getY() << ")\n";
}

void LoggingVisitor::visit(Dragon* dragon) {
    os << "Dragon: " << dragon->getName() << " at (" << dragon->getX() << ", " << dragon->getY() << ")\n";
}