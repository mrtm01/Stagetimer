#pragma once
#include <SDL2/SDL.h>
#include <string>


class Utility
{
    public:
        static void PrintIP(Uint32 ip);
        static std::string IPToString(Uint32 ip);
        static std::string PadToTwo(std::string input);
    private:
        union IPBytes {
            Uint32 wholeIP;
            Uint8 bytes[4];         
        };


};