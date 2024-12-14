#include "NPCFactory.hpp"

std::map<std::string, std::unique_ptr<NPCFactory>> NPCFactory::factories;

void NPCFactory::registerFactory(const std::string& type, std::unique_ptr<NPCFactory> factory) {
    factories[type] = std::move(factory);
}

std::unique_ptr<NPC> NPCFactory::create(const std::string& type, const std::string& name, int x, int y) {
    auto it = factories.find(type);
    if (it != factories.end()) {
        return it->second->createNPC(name, x, y);
    }
    return nullptr;
}