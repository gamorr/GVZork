#ifndef __H__NPC__
#define __H__NPC__

#include <string>
#include <vector>

class NPC {
    public:
    
        NPC(const std::string& name, const std::string& description);

        void set_name(const std::string& n);

        void set_description(const std::string& desc);

        void add_message(const std::string& msg);

        std::string get_name() const;

        std::string get_description() const;

        //returns the current message according to the message number. Increments the message number
        std::string get_message();

    private:
        std::string name;

        std::string description;
    
        //vector of messages that an NPC has. The current message updates whenever the player talks to the NPC
        std::vector<std::string> messages;

        //index of the current message
        int message_number;
};

#endif
#pragma once
