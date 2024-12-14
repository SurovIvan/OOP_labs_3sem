#ifndef LOGGINGVISITOR_HPP
#define LOGGINGVISITOR_HPP

#include "Visitor.hpp"
#include "NPC.hpp"
#include "Toad.hpp"
#include "Bull.hpp"
#include "Dragon.hpp"
#include <ostream>

class LoggingVisitor : public Visitor {
    public:
        LoggingVisitor(std::ostream& os);
        void visit(Dragon* Dragon) override;
        void visit(Toad* Toad) override;
        void visit(Bull* Bull) override;
    private:
        std::ostream& os;
};

#endif