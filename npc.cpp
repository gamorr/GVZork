#include "objects.hpp"
#include <string>
#include <vector>
#include <iostream>

// Constructor: Initializes the NPC with a name and description, and sets the message number to start at 0.
NPC::NPC(const std::string& name, const std::string& description) {
    this->name = name;
    this->description = description;
    this->message_number = 0;
    this->messages.push_back("Wassup"); // Default message
}
// Sets a new name for the NPC.
void NPC::set_name(const std::string& n) {
    if (n.empty()){
        throw std::runtime_error("Name cannot be blank");
    }
    this->name = n;
}

// Sets a new description for the NPC.
void NPC::set_description(const std::string& desc) {
    if (desc.empty()){
        throw std::runtime_error("Description cannot be blank");
    }
    this->description = desc;
}

// The NPC class does not instantiate multiple messages so I guess just use this method to add more messages.
void NPC::add_message(const std::string& msg) {
    this->messages.push_back(msg);
}

// Returns the NPC's name.
std::string NPC::get_name() const {
    return this->name;
}

// Returns the NPC's description.
std::string NPC::get_description() const {
    return this->description;
}

// Returns the current message based on the current message_number.
// Increments message_number to the next message, cycling back to 0 if at the end of the messages list.
std::string NPC::get_message() {
    if (this->messages.empty()) {
        return "The NPC has nothing to say.";  // Return a default message if there are no messages.
    }

    // Retrieve the current message.
    std::string current_message = this->messages[this->message_number];

    // Increment message_number, wrapping around to 0 if it exceeds the last index.
    this->message_number = (this->message_number + 1) % this->messages.size();

    return current_message;
}
// Overloaded << operator for NPC: prints only the name of the NPC.
std::ostream& operator<<(std::ostream& os, const NPC& npc) {
    os << npc.get_name();
    return os;
}