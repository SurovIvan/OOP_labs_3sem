#include "NPC.hpp"
#include "Bull.hpp"
#include "Toad.hpp"
#include "Dragon.hpp"
#include "BattleVisitor.hpp"
#include "DragonFactory.hpp"
#include "NPCFactory.hpp"
#include "BullFactory.hpp"
#include "ToadFactory.hpp"
#include "NPCSaver.hpp"
#include "NPCLoader.hpp"
#include "LoggingVisitior.hpp"

void printNPCs(const std::vector<std::unique_ptr<NPC>>& npcs) {
    for (const auto& npc : npcs) {
        std::string type = typeid(*npc).name();
        type.erase(0, type.find_first_not_of("0123456789"));
        std::cout << "Type: " << type << ", Name: " << npc->getName() << ", Coord: (" << npc->getX() << " " << npc->getY() << ")\n";
    }
}

int main() {
    NPCFactory::registerFactory("Bull", std::make_unique<BullFactory>());
    NPCFactory::registerFactory("Toad", std::make_unique<ToadFactory>());
    NPCFactory::registerFactory("Dragon", std::make_unique<DragonFactory>());

    std::vector<std::unique_ptr<NPC>> npcs;

    npcs.emplace_back(NPCFactory::create("Toad", "Legolas", 200, 300));
    npcs.emplace_back(NPCFactory::create("Bull", "Radagast", 250, 350));
    npcs.emplace_back(NPCFactory::create("Dragon", "Smaug", 300, 400));

    std::cout << "Initial NPCs:\n";
    printNPCs(npcs);

    NPCSaver::saveNPCs(npcs, "npcs.txt");
    std::vector<std::unique_ptr<NPC>> loadedNpcs = NPCLoader::loadNPCs("npcs.txt");

    BattleVisitor battleVisitor(100, npcs);
    LoggingVisitor loggingVisitor(std::cout);

    std::cout << "\nStarting battles:\n";
    for (size_t i = 0; i < npcs.size();) {
        if (npcs[i]) {
            npcs[i]->accept(battleVisitor);
            ++i;
        } else {
            ++i;
        }
    }

    std::cout << "\nLogging NPCs:\n";
    for (const auto& npc : npcs) {
        if (npc) {
            npc->accept(loggingVisitor);
        }
    }

    NPCSaver::saveNPCs(npcs, "npcs.txt");

    return 0;
}