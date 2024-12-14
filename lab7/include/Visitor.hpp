#ifndef VISITOR_HPP
#define VISITOR_HPP

class Dragon;
class Bull;
class Toad;

class Visitor {
    public:
        virtual void visit(Dragon* drago) = 0;
        virtual void visit(Bull* bull) = 0;
        virtual void visit(Toad* toad) = 0;
};

#endif