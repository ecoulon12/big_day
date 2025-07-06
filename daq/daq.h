// daq.h
#ifndef DAQ_H
#define DAQ_H

#include <string>

// Declare functions
std::string getUserCityInput();
std::string getUserCoordinates();
std::string buildOSMQuery(std::string cityName);
std::string buildEBIRDquery(std::string lat, std::string lon);
void sendOSMQuery(std::string query_str);
void sendEbirdQuery(std::string query_str);

#endif
