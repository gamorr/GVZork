#include "game.h"
#include "objects.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>


Game::Game() {
    // Initialize the commands map using setup_commands
    commands = setup_commands();
    
    // Create the world
    create_world();
    
    // Set default values for variables
    needed_calories = 200;
    current_location = random_location();
}


void Game::create_world() {
    // Create Items
    items.push_back(Item("Banana", "A sharp blade forged with fine steel.", 80, 3.5f));
    items.push_back(Item("Apple", "A fresh, juicy apple.", 80, 3.5f));
    items.push_back(Item("Cookie", "Very chocolate", 80, 3.5f));

    // Create NPCs
    NPC joel("Joel", "An elderly man who knows many things");
    joel.add_message("Hello, traveler! Watch out for the creatures in the forest.");
    joel.add_message("The cave holds secrets, but beware of its dangers!");

    NPC samantha("Samantha", "A knowledgeable woman who is eager to help");
    samantha.add_message("The forest is treacherous, but it's where I hone my skills.");
    samantha.add_message("I saw something strange near the cave entrance yesterday.");


    Location kirkhoff("Kirkhoff", "A bustling village with plenty of folks walking about");
    Location zumberge("Zumberge", "An abandoned city with scarce resources");
    Location haas("Haas", "A pleasant little village with art and music all around");
    Location mackinac("Mackinac", "A city with many hardworking scientists and mathmeticians");
    Location calder("Calder", "A distant village with odd, but friendly locals");
    Location library("Library", "A cozy building with shelves full of books");
    Location padnos("Padnos", "A heavily fortified complex");
    Location blue("Blue", "Filled with shops and cool trinkets");


    // Add NPCs and Items to Locations
    kirkhoff.add_npc(joel);
    zumberge.add_npc(samantha);
    library.add_item(items[0]);
    calder.add_item(items[1]);
    mackinac.add_item(items[2]);

    // Link Locations
    kirkhoff.add_location("north", zumberge);
    kirkhoff.add_location("south", haas);
    zumberge.add_location("east", haas);
    haas.add_location("west", zumberge);

    locations.push_back(kirkhoff);
    locations.push_back(zumberge);
    locations.push_back(haas);
    locations.push_back(blue);
    locations.push_back(mackinac);
    locations.push_back(padnos);
    locations.push_back(library);
    locations.push_back(calder);
}

std::map<std::string, std::function<void(std::vector<std::string>)>> Game::setup_commands() {
    std::map<std::string, std::function<void(std::vector<std::string>)>> command_map;
    command_map["help"] = [this](std::vector<std::string> args) { show_help(); };
    command_map["talk"] = [this](std::vector<std::string> args) { talk(args); };
    command_map["meet"] = [this](std::vector<std::string> args) { meet(args); };
    command_map["take"] = [this](std::vector<std::string> args) { take(args); };
    command_map["give"] = [this](std::vector<std::string> args) { give(args); };
    command_map["go"] = [this](std::vector<std::string> args) { go(args); };
    command_map["items"] = [this](std::vector<std::string> args) { show_items(args); };
    command_map["look"] = [this](std::vector<std::string> args) { look(args); };
    command_map["quit"] = [this](std::vector<std::string> args) { quit(args); };

    return command_map;
}
