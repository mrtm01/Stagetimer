#include "IPConverter.h"
#include <iostream>
#include <string>

void IPConverter::PrintIP(Uint32 ip)
{
    IPBytes ipbytes;
    ipbytes.wholeIP = ip;
    std::cout << "PrintIP: " <<  (int)ipbytes.bytes[0] << "." << (int)ipbytes.bytes[1] << "." << (int)ipbytes.bytes[2] << "." << (int)ipbytes.bytes[3] << std::endl;
}

std::string IPConverter::IPToString(Uint32 ip)
{
    IPBytes ipbytes;
    ipbytes.wholeIP = ip;
    std::string retString = std::to_string((int)ipbytes.bytes[0]);
    retString += std::to_string((int)ipbytes.bytes[1]);
    retString += std::to_string((int)ipbytes.bytes[2]);
    retString += std::to_string((int)ipbytes.bytes[3]);
    
    return retString;
}