#pragma once
#include <SDL2/SDL.h>
#include <string>


class IPConverter
{
    public:
        static void PrintIP(Uint32 ip);
        static std::string IPToString(Uint32 ip);
    private:
        union IPBytes {
            Uint32 wholeIP;
            Uint8 bytes[4];         
        };


};