#include "objects.hpp"
#include <string>
#include <vector>
#include <map>
#include <iostream>

Location::Location(const std::string& name, const std::string& description) {
    this->name = name;
    this->description = description;
    this->visited = false;
}

void Location::add_location(const std::string& direction, const Location& location) {
    this->neighbors.insert(std::pair{direction, location});
}

void Location::add_npc(NPC npc) {
    this->npcs.push_back(npc);
}

void Location::add_item(Item item) {
    this->items.push_back(item);
}

void Location::set_visited() {
    this->visited = true;
}

std::map<string, Location> Location::get_locations() {
    return this->neighbors;
}

std::vector<NPC> Location::get_npcs() {
    return this->npcs;
}

std::vector<Items> Location::get_items() {
    return this->items;
}

bool Location::get_visited() {
    return this->visited;
}
