#ifndef BULL_HPP
#define BULL_HPP

#include "NPC.hpp"
#include "Visitor.hpp"
#include "Toad.hpp"

class Bull : public NPC {
    public: 
        Bull(const std::string& name, int x, int y);
        void accept(Visitor& visitor) override;
        bool fight(NPC* other) override;
        std::string getType() const override { return type; }
    private:
        static const std::string type;
};

#endif