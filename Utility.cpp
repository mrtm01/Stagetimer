#include "Utility.h"
#include <iostream>
#include <string>

void Utility::PrintIP(Uint32 ip)
{
    IPBytes ipbytes;
    ipbytes.wholeIP = ip;
    std::cout << "PrintIP: " <<  (int)ipbytes.bytes[0] << "." << (int)ipbytes.bytes[1] << "." << (int)ipbytes.bytes[2] << "." << (int)ipbytes.bytes[3] << std::endl;
}

std::string Utility::IPToString(Uint32 ip)
{
    IPBytes ipbytes;
    ipbytes.wholeIP = ip;
    std::string retString = std::to_string((int)ipbytes.bytes[0]);
    retString+=".";
    retString += std::to_string((int)ipbytes.bytes[1]);
    retString+=".";
    retString += std::to_string((int)ipbytes.bytes[2]);
    retString+=".";
    retString += std::to_string((int)ipbytes.bytes[3]);

    return retString;
}

std::string Utility::PadToTwo(std::string input)
{
    if (input.length() == 1) return std::string("0") + input;
    else return input;
}