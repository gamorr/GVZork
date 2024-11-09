#ifndef             __H__OBJECTS__
#define             __H__OBJECTS__

#include <vector>
#include <functional>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>


class Item {
    public: 
        std::string name;
        std::string description;
        int calories;
        float weight;
        Item(const std::string &name, const std::string &description, int calories, float weight);
        friend std::ostream& operator<<(std::ostream& os, const Item& item){
            os << item.name << " (" << item.calories << " calories" << ")" << " - " << item.weight << " lb " << "- " << item.description << std::endl;
            return os;
        }
};

class Location {
    public:
        Location(const std::string& name, const std::string& description);
        std::map<string, Location> get_locations();
        void add_location(const std::string& direction, const Location& location);
        void add_npc(NPC npc);
        std::vector<NPC> get_npcs();
        void add_item(Item item);
        std::vector<Item> get_items();
        void set_visited();
        bool get_visited();

        friend std::ostream& operator<<(std::ostream& os, const Locatoin& other) {
            os << other.name << " - " << other. description << std::endl;
            os << std::endl << "You see the following NPCs:" << std::endl;
            for(auto it = other.npcs.begin(); it!=other.npcs.end(); ++it) {
                os << "\t- " << *it << std::endl;
            }
            os << std::endl << "You see the following Items:" << std::endl;
            for(auto it = other.items.begin(); it!=other.items.end(); ++it) {
                os << "\t- " << *it << std::endl;
            }
            os << std::endl << "You can go in the following Directions:" << std::endl;
            for(auto it = other.neighbors.begin(); it!=other.neighbors.end(); ++it) {
                os << "\t- " << it->first << " - " << it->second;
                if(it->second.get_visited()) {
                    os << " (Visited)";
                }
                os << std::endl;
            }
        }

    private:
        std::string name;
        std::string description;
        std::vector<NPC> npcs;
        std::vector<Item> items;
        bool visited;
        std::map<string, Location> neighbors;



#endif
