#pragma once

#include <string>
#include <random>
#include <sstream>

class UUID
{
public:
    static std::string generate()
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

        return ss.str();
    }
};