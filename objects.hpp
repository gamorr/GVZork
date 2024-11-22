/**
 * Authors:   Harrison Waldon, Gavin Morrow, Gavin Cowan
 * Created:   11.7.2024
 **/
#ifndef             __H__OBJECTS__
#define             __H__OBJECTS__

#include <vector>
#include <functional>
#include <string>
#include <map>
#include <iostream>

class NPC {
    public:
        // Constructor
        NPC(const std::string& name, const std::string& description);

        // Setters
        void set_name(const std::string& n);
        void set_description(const std::string& desc);
        void add_message(const std::string& msg);
        // Getters
        std::string get_name() const;
        std::string get_description() const;
        //returns the current message according to the message number. Increments the message number
        std::string get_message();

        // Overloaded stream for output, only outputs the name
        friend std::ostream& operator<<(std::ostream& os, const NPC& npc) {
            os << npc.name; 
            return os;
        }

    private:
        std::string name;
        std::string description;
        //vector of messages that an NPC has. The current message updates whenever the player talks to the NPC
        std::vector<std::string> messages;
        //index of the current message
        int message_number;
};

class Item {
    public: 
        // Constructor
        Item(const std::string &name, const std::string &description, int calories, float weight);

        // Getters
        std::string get_name();
        std::string get_desc();
        int get_calories();
        float get_weight();
    

        // Overloading the stream operator to depict all info contained in a item easily

        friend std::ostream& operator<<(std::ostream& os, const Item& item){
            os << item.name << " (" << item.calories << " calories" << ")" << " - " << item.weight << " lb - " << item.description << std::endl;
            return os;
        }
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
        Location();
                
        // Setters
        void add_location(const std::string& direction, Location* location);
        void add_npc(NPC& npc);
        void add_item(Item& item);
        void set_visited();
        void remove_item(Item&);
        // Getters
        std::string get_name();
        std::string get_desc();
        std::map<std::string, Location*> get_locations();
        std::vector<std::reference_wrapper<NPC> > get_npcs();
        std::vector<std::reference_wrapper<Item> > get_items();
        bool get_visited() const;

        // Overloading the stream operator to depict all info contained in a location
        // in an easy to read manner
        friend std::ostream& operator<<(std::ostream& os, const Location& other) {
            os << other.name << " - " << other.description << std::endl << std::endl;

            if (other.npcs.empty()) { // Different output if there are no npcs
                os << "You are alone." << std::endl << std::endl;
            } else {
                os << "You see the following NPCs:" << std::endl;
                for(auto it = other.npcs.begin(); it != other.npcs.end(); ++it) {
                    os << "\t- " << *it << std::endl;
                }
                os << std::endl;
            }

            if (other.items.empty()) { // Different output if there are no items
                os << "There are no items here." << std::endl << std::endl;
            } else {
                os << "You see the following Items:" << std::endl;
                for(auto it = other.items.begin(); it!=other.items.end(); ++it) {
                    os << "\t- " << *it;
                }
                os << std::endl;
            }

            os << "You can go in the following Directions:" << std::endl;
            for(auto it = other.neighbors.begin(); it!=other.neighbors.end(); ++it) {
                if(!it->second->visited) { // Prints unknown if the location is not visited yet
                    os << it->first << "\t- Unknown";
                } else {
                    os << "\t- " << it->first << " - " << it->second->name << " (Visited)";
                }
                os << std::endl;
            }
            return os;
        }

    private:
        std::string name;
        std::string description;
        std::vector<std::reference_wrapper<NPC> > npcs;
        std::vector<std::reference_wrapper<Item> > items;
        bool visited;
        std::map<std::string, Location*> neighbors; // Couldn't get map working with reference_wrapper so it is a pointer
};

class Game {
    public:
        // Constructor
        Game();
        
        // Backend functions
        void create_world();
        std::map<std::string, std::function<void(std::vector<std::string>)> > setup_commands(); // map of command, function name        
        Location random_location();
        void play();

        // Player commands
        void show_help();
        void talk(std::vector<std::string> target); 
        void meet(std::vector<std::string> target); 
        void take(std::vector<std::string> target);
        void give(std::vector<std::string> target);
        void go(std::vector<std::string> target);
        void show_items(std::vector<std::string> target);
        void look(std::vector<std::string> target);
        void quit(std::vector<std::string> target);
        void teleport(std::vector<std::string> target);
        void dance(std::vector<std::string> target);

    private:
        Location current_location;
        std::map<std::string, std::function<void(*)(std::vector<std::string>)> > commands;
        std::vector<Item> items;
        std::vector<std::reference_wrapper<Location> > locations;
        bool can_teleport;
        int current_calories;
        int needed_calories;
        float current_weight;
        float max_weight;
};


#endif
