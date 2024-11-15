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
    // Constructor 
        Item(const std::string &name, const std::string &description, int calories, float weight);
    // Overloading stream operator to display Item information effectively
        friend std::ostream& operator<<(std::ostream& os, const Item& item){
            os << item.name << " (" << item.calories << " calories" << ")" << " - " << item.weight << " lb " << "- " << item.description << std::endl;
            return os;
        }
    // Data Members
    private: 
        std::string name; 
        std::string description;
        int calories;
        float weight;
};

class Location {
    public:
        // Constructor
        Location(const std::string& name, const std::string& description);
        // Setters
        void add_location(const std::string& direction, const Location& location);
        void add_npc(const NPC& npc);
        void add_item(const Item& item);
        void set_visited();
        // Getters
        std::map<std::string, std::reference_wrapper<Location> > get_locations();
        std::vector<reference_wrapper<NPC> > get_npcs();
        std::vector<reference_wrapper<Item> > get_items();
        bool get_visited();

        // Overloading the stream operator to depict all info contained in a location
        // in an easy to read manner

        friend std::ostream& operator<<(std::ostream& os, const Location& other) {
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
        std::vector<std::reference_wrapper<NPC> > npcs;
        std::vector<std::reference_wrapper<Item> > items;
        bool visited;
        std::map<std::string, std::reference_wrapper<Location> > neighbors;
}




#endif
