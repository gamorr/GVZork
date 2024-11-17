#ifndef             __H__GAME__
#define             __H__GAME__

#include "objects.hpp"
#include <vector>
#include <functional>
#include <string>
#include <map>
#include <iostream>


class Game {
    public:
        Game();
        
        void create_world();
        std::map<std::string, std::function<void(std::vector<std::string>)>> setup_commands(); // map of command, function name        
        void play();
        void show_help();
        void talk(std::vector<std::string> target); 
        void meet(std::vector<std::string> target); 
        void take(std::vector<std::string> target);
        void give(std::vector<std::string> target);
        void go(std::vector<std::string> target);
        void show_items(std::vector<std::string> target);
        void look(std::vector<std::string> target);
        void quit(std::vector<std::string> target);

        Location current_location;
        std::map<std::string, std::function<void(*)(std::vector<std::string>)>> commands;
        std::vector<Item> items;
        std::vector<Location> locations;
        int current_calories;
        int needed_calories;
        float current_weight;
        float max_weight;
};



#endif