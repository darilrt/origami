#pragma once

#include <string>
#include <random>
#include <sstream>

class UUID
{
public:
    UUID()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 15);

        std::stringstream ss;
        for (int i = 0; i < 32; i++)
        {
            int random = dis(gen);
            if (i == 8 || i == 12 || i == 16 || i == 20)
            {
                ss << '-';
            }
            ss << std::hex << random;
        }

        uuid = ss.str();
    }

    std::string get_uuid() const
    {
        return uuid;
    }

private:
    std::string uuid;
};