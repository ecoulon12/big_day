// daq.cpp
#include "daq.h"

#include <curl/curl.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
// Include other headers as needed

std::string getUserCityInput() {
  std::string city;
  std::cout << "Enter city name: ";
  std::getline(std::cin, city);
  return buildOSMQuery(city);
}

std::string getUserCoordinates() {
  std::string lat, lon;
  std::cout << "Enter latitude of your starting location: ";
  std::getline(std::cin, lat);
  std::cout << "Enter longitude of your starting location: ";
  std::getline(std::cin, lon);
  return buildEBIRDquery(lat, lon);
}

std::string buildOSMQuery(std::string cityName) {
  std::stringstream query;

  query << "[out:json][timeout:25];\n";
  query << "area[\"name\"=\"" + cityName + "\"][\"admin_level\"=\"8\"]->.a;\n";
  query << "way(area.a)[\"highway\"];\n";
  query << "out body;\n";
  query << ">;\n";
  query << "out skel qt;\n";

  return query.str();
}

std::string buildEBIRDquery(std::string lat, std::string lon) {
  std::stringstream query;

  query << "https://api.ebird.org/v2/ref/hotspot/geo?lat=" + lat +
               "&lng=" + lon + "&fmt=json";

  return query.str();
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

void sendOSMQuery(std::string query_str) {
  CURL* curl;
  CURLcode res;

  std::string query = query_str;
  std::string response;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://overpass-api.de/api/interpreter");

    // Set POST data
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query.c_str());

    // Set callback to capture response
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Perform the request
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res)
                << std::endl;
    else {
      // Save response to file or process it
      std::ofstream outFile("osm_response.json");
      outFile << response;
      outFile.close();
      std::cout << "Query successful, response saved to osm_response.json\n";
    }
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();

  return;
}

// NEED TO CHANGE
void sendEbirdQuery(std::string query_str) {
  CURL* curl;
  CURLcode res;

  std::string response;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://overpass-api.de/api/interpreter");

    // Set POST data
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query_str.c_str());

    // Set callback to capture response
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Perform the request
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res)
                << std::endl;
    else {
      // Save response to file or process it
      std::ofstream outFile("osm_response.json");
      outFile << response;
      outFile.close();
      std::cout << "Query successful, response saved to osm_response.json\n";
    }
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();

  return;
}