/**
 * Authors:   Harrison Waldon, Gavin Morrow, Gavin Cowan
 * Created:   11.16.2024
 **/

#include "objects.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <random> 


Game::Game() {

    // Create the world
    create_world();

    // Set default values for player calories and weight
    this->needed_calories = 200;
    this->current_calories = 0;
    this->current_weight = 0;
    this->max_weight = 30;
    this->can_teleport = true;

    this->current_location = this->random_location(); // player starts in random location
    this->current_location.set_visited(); // Makes the start location visited
    play();
    
}

// Play the game, automatically sets up commands upon playing and prints an introduction
// Then waits for user input 
void Game::play(){
    std::map<std::string, std::function<void (std::vector<std::string>)> > commands = setup_commands();
    // Introduction 
    std::cout << "Hello Traveler, and welcome to the enchanting world of Grand Valley State University!\nQuite an exciting and charming place.\nHowever, theres this elf in the ravines that needs some food and if he does not get it he will destroy the place. \nCan you help us out?" << std::endl;
    std::cout << "You are currently in " << current_location;
    while(needed_calories > current_calories){
        std::cout << "You currently have " << current_calories << "calories out of " << needed_calories << "." << std::endl << std::endl;

        std::cout << "What would you like to do? (Type help for a list of commands)\n" << std::endl;

        std::string user_response;
        std::cin >> user_response;
        std::vector<std::string> tokens;
        std::string delimiter = " ";
        size_t pos = 0;
        std::string token;
        // splits the words in user_respose into individual tokens, which are inserted into the vector 'tokens'
        while ((pos = user_response.find(delimiter)) != std::string::npos) {
            token = user_response.substr(0, pos);
            tokens.push_back(token);
            user_response.erase(0, pos + delimiter.length());
        }

        std::string command = tokens[0];
        //removes the command from the vector of tokens
        tokens.erase(tokens.begin());
        commands[command](tokens);
    
    }
}

// Create the game world including all the items, locations, npcs and places them in the world
void Game::create_world() {
    // Create Items  // DEVNOTE - we need 5 more items, probably more that don't have a calorie count
    items.push_back(Item("Banana", "Lots of potassium", 40, 3.5f));
    items.push_back(Item("Apple", "A fresh, juicy apple.", 20, 3.5f));
    items.push_back(Item("Cookie", "Very chocolate", 100, 3.5f));
    items.push_back(Item("Pumpkin", "I guess the elf would be fine with it?", 30, 15.5f));
    items.push_back(Item("Orb of True Knowledge", "Contains the answer to life, the universe, and everything.", 42, 7.8f));
    items.push_back(Item("Peanut", "Contains the answer to life, the universe, and everything", 0, 2.0f));

    // Create NPCs
    NPC elf("Elf", "A mystical elf that is really hungry");
    elf.add_message("Hello, traveler! Fancy running into you here.. do you have anything to eat, by chance? Im starving.");
    elf.add_message("Can you fetch me some food! Bad things will happen if you don't.");

    NPC joel("Joel", "An elderly man who knows many things");
    joel.add_message("I like this place. I'm not sure if there's much to eat here, I suppose you can have that pumpkin over there.");
    joel.add_message("I'm a pumpkin farmer, you see. I used to be a professor but I got kind of tired of that. No, I will not share wisdom with you.");

    NPC samantha("Samantha", "A knowledgeable woman who is eager to help");
    samantha.add_message("Hi! Do you need help getting around? Try typing 'help'!");
    samantha.add_message("I don't eat, actually, so I never keep food around here.");

    NPC felix("Felix", "He's busy doing linear algebra homework.");
    felix.add_message("...");
    felix.add_message("What? You need something?");
    felix.add_message("Unless you know how to find the eigenvectors of a matrix, I'm not interested in talking to you.");
    felix.add_message("I don't have any food, if that's what you want. I guess there's this peanut on the ground, you can have that.");

    NPC walker("Walker", "He really likes to sing, and loudly too.");
    walker.add_message("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    walker.add_message("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
    walker.add_message("EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");


    Location kirkhoff("Kirkhoff", "A bustling village with plenty of folks walking about");
    Location zumberge("Zumberge", "An abandoned city with scarce resources");
    Location haas("Haas", "A pleasant little village with art and music all around");
    Location mackinac("Mackinac", "A city with many hardworking scientists and mathmeticians");
    Location calder("Calder", "A distant village with odd, but friendly locals");
    Location library("Library", "A cozy building with shelves full of books");
    Location padnos("Padnos", "A chemistry lab with many safety protocols.");
    Location ravines("Ravines", "A dense forest within a winding system of ravines");

    this->locations.push_back(kirkhoff);
    this->locations.push_back(zumberge);
    this->locations.push_back(haas);
    this->locations.push_back(mackinac);
    this->locations.push_back(calder);
    this->locations.push_back(library);
    this->locations.push_back(padnos);
    this->locations.push_back(ravines);

    // Add NPCs and Items to Locations
    // DEVNOTE - probably should randomly assign things to locations using the random_location function other than the elf
    ravines.add_npc(elf);
    this->random_location().add_npc(joel);
    this->random_location().add_npc(samantha);
    this->random_location().add_npc(felix);
    this->random_location().add_npc(walker);

    this->random_location().add_item(items[4]);
    this->random_location().add_item(items[1]);
    this->random_location().add_item(items[2]);
    this->random_location().add_item(items[3]);
    this->random_location().add_item(items[5]);
    this->random_location().add_item(items[0]);

    // Link Locations
    ravines.add_location("north", &mackinac);
    ravines.add_location("south", &calder);
    ravines.add_location("west", &zumberge);
    zumberge.add_location("west", &kirkhoff);
    zumberge.add_location("north", &padnos);
    zumberge.add_location("south", &haas);
    zumberge.add_location("east", &ravines);
    kirkhoff.add_location("east", &zumberge);
    kirkhoff.add_location("west", &library);
    library.add_location("east", &kirkhoff);
    padnos.add_location("south", &zumberge);
    padnos.add_location("east", &mackinac);
    haas.add_location("north", &zumberge);
    haas.add_location("east", &calder);
    calder.add_location("north", &ravines);
    calder.add_location("west", &haas);
    mackinac.add_location("south", &ravines);
    mackinac.add_location("west", &padnos);
}

// Sets up all commands
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

// Selects a random location from the locations in the game
Location Game::random_location() {
    std::random_device rd; // Seed generator
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<> dist(0, locations.size() - 1);

    // return random location
    int randomIndex = dist(gen);
    return locations[randomIndex];
}

// Displays all commands, how to use them and what they do
void Game::show_help() {
    std::cout << "Available commands:\n";
    std::cout << "  talk <NPC> - Talk to an NPC in the current location.\n";
    std::cout << "  meet <NPC> - Get a brief description of an NPC.\n";
    std::cout << "  take <item> - Take an item from the current location.\n";
    std::cout << "  give <item> - Give an item to the NPC in need.\n";
    std::cout << "  go <location> - Travel to a neighboring location.\n";
    std::cout << "  items - Show items in your inventory.\n";
    std::cout << "  look - Get information on your current location.\n";
    std::cout << "  quit - Exit the game.\n";
    std::cout << "  teleport - Teleport to a location.\n";
    std::cout << "  dance - Start dancing on the spot\n";
}

// Talks to the specified NPC. If none is specified, a different message will send
void Game::talk(std::vector<std::string> args) {
    if (args.empty()) {
        std::cout << "You need to specify an NPC to talk to.\n";
        return;
    }

    std::string npc_name = args[0];
    NPC* target_npc;
    std::vector<std::reference_wrapper<NPC> > npcs = current_location.get_npcs();

    for(auto it = npcs.begin(); it!= npcs.end(); it++){
        if (it->get().get_name() == npc_name){
            target_npc = &(it->get());
            break;
        }
    }

    if (target_npc) {
        std::cout << target_npc->get_message() << "\n";
    } else {
        std::cout << "There is no one named " << npc_name << " here to talk to.\n";
    }
}

// See all NPCs and who they are in the current location
void Game::meet(std::vector<std::string> args) {
    std::vector<std::reference_wrapper<NPC> > npcs = current_location.get_npcs();

    if (npcs.empty()) {
        std::cout << "There are no NPCs in this location to meet.\n";
        return;
    }

    std::cout << "You see the following NPCs in this location:\n";

    for (const auto& npc : npcs) {
        std::cout << "- " << npc.get().get_name() << ": " << npc.get().get_description() << "\n";
    }
}

// Grab an item from the current location if not too heavy
void Game::take(std::vector<std::string> target) {
    if (target.empty()) {
        std::cout << "You need to specify an item to take.\n";
        return;
    }

    std::string item_name = target[0];
    std::vector<std::reference_wrapper<Item> > items_in_room = current_location.get_items(); // Get all items in the location
    Item* item_to_take;

    // Search for the item in the room
    for (auto item : items_in_room) {
        if (item.get().get_name() == item_name) {
            item_to_take = &(item.get());
            break;
        }
    }

    if (!item_to_take) {
        std::cout << "There is no item named '" << item_name << "' here to take.\n";
        return;
    }

    // Check if adding the item exceeds the player's carry weight limit (optional logic)
    float new_weight = current_weight + item_to_take->get_weight();
    if (new_weight > max_weight) {
        std::cout << "You cannot carry the '" << item_name << "', it is too heavy!\n";
        return;
    }

    // Update inventories
    items.push_back(*item_to_take); // Add to player's inventory
    current_weight += item_to_take->get_weight();

    current_location.remove_item(*item_to_take);

    std::cout << "You picked up '" << item_name << "'.\n";
}

// Uses an item from the player's inventory to try to give it to another 
void Game::give(std::vector<std::string> target) {
    if (target.empty()) {
        std::cout << "You need to specify an item to give.\n";
        return;
    }

    std::string item_name = target[0];
    Item* item_to_give = nullptr;

    // Search for the item in the player's inventory
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->get_name() == item_name) {
            item_to_give = &(*it);

             // Remove the item from the inventory and update the current calories and weight
            current_weight -= item_to_give->get_weight();
            current_calories += item_to_give->get_calories();
            items.erase(it);

            // if the item is not edible, the player will be sent to a random location
            if (item_to_give->get_calories() == 0){
                std::cout << "Blah! This is not edible! I banish thee!" << std::endl;
                current_location = this->random_location();
            }

            break;
        }
    }

    if (!item_to_give) {
        std::cout << "You do not have an item named '" << item_name << "' to give.\n";
        return;
    }

}

// Moves the player to the specified direction then sets the new location to visited
void Game::go(std::vector<std::string> target) {
    if (target.empty()) {
        std::cout << "You need to specify a direction to go.\n";
        return;
    }

    std::string direction = target[0];

    // Mark the current location as visited
    current_location.set_visited(); // Set the current location's visited status to true
    // Check if the direction exists in the neighbors map
    if (current_location.get_locations()[direction] != nullptr) {
        current_location = *(current_location.get_locations()[direction]); // Update the current location
         // std::cout << "You move " << direction << " to " << current_location.get_name() << ".\n"; // provide a get_name function so that we can access the location's name
    } else {
        std::cout << "You can't go " << direction << " from here.\n";
    }
}

// Shows the items that the character is holding
void Game::show_items(std::vector<std::string> target) {
    if (!target.empty()) { //check if target has arguments or not
        std::cout << "no args required to view inventory!\n";
        return;
    }

    std::cout << "Inventory: \n";
    for (auto it = items.begin(); it != items.end(); ++it) { //search for items in player's inventory  
        std::cout << it->get_name() << it->get_weight() << " lbs\n"; //print name and weight
    }
}

// Gives info about the current location the player is in
void Game::look(std::vector<std::string> target) {
    std::cout << "You are currently in " << current_location;
}

// Quits the game when chosen
void Game::quit(std::vector<std::string> target) {
    std::cout << "You decided that someone else could save GV. Later, the Elf destroyed GV.\n\nYou Lose." << std::endl;
    std::exit(0);
}

void Game::teleport(std::vector<std::string> target) {
    if (target.empty()) {
        std::cout << "You need to specify a direction to go.\n";
        return;
    }

    std::string direction = target[0];

    // Check if the location exists in the locations vector
    if (can_teleport){ 
        for(auto it = locations.begin(); it != locations.end(); ++it) { // finds the location in the vector of locations.
            if(it->get().get_name() == direction) {
                can_teleport = false;
                current_location = it->get();
                std::cout << "You are now in " << current_location.get_name();
                return;
            }
        }
        std::cout << "There is no" << direction << "here.\n";
    }
    else {
        std::cout << "You cannot teleport anymore!" << std::endl;
    }
}

// Have the character start doing a random dance from a list of 8 dances
// If there are NPC's around, will output a different message
void Game::dance(std::vector<std::string> target) {
    // Initialize values
    std::vector<std::string> Dances = {"Griddy", "Tap Dance", "Moonwalk", "Floss", "Dab", "Nae Nae", "Wobble", "Dougie"};
    std::srand(std::time(nullptr));
    int dance = std::rand() / Dances.size();

    std::cout << "You start hitting the " << Dances[dance] << "." << std::endl;
    if (!current_location.get_npcs().empty()) {
        std::cout << "The people in the area approve." << std::endl;
    }
}