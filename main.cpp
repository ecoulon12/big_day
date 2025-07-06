#include <iostream>
#include <string>

// Placeholder declarations — implement these in their own files/modules
std::string getUserCityInput();
std::string fetchAreaIDFromOverpass(const std::string& cityName);
std::string fetchOSMData(const std::string& areaID);
void parseOSMData(const std::string& osmJson);
void runRouteOptimization();
void displayResults();

int main() {
    // 1. Get city name from user
    std::string cityName = getUserCityInput();

    // 2. Fetch area ID for the city using Overpass area query
    std::string areaID = fetchAreaIDFromOverpass(cityName);
    if (areaID.empty()) {
        std::cerr << "Failed to find area ID for city: " << cityName << std::endl;
        return 1;
    }

    // 3. Fetch OSM data (roads, hotspots) within area
    std::string osmDataJson = fetchOSMData(areaID);
    if (osmDataJson.empty()) {
        std::cerr << "Failed to fetch OSM data for area: " << areaID << std::endl;
        return 1;
    }

    // 4. Parse the OSM JSON data into your graph/data structures
    parseOSMData(osmDataJson);

    // 5. Run your route optimization algorithm
    runRouteOptimization();

    // 6. Display or output the results to the user
    displayResults();

    return 0;
}


std::string getUserCityInput() {
    std::string city;
    std::cout << "Enter city name: ";
    std::getline(std::cin, city);
    return city;
}

std::string fetchAreaIDFromOverpass(const std::string& cityName) {
    // For now, just return a dummy area ID or empty string
    return "3600065601"; // example Overpass area ID for Berkeley
}

std::string fetchOSMData(const std::string& areaID) {
    // TODO: implement HTTP request to Overpass API and return JSON response
    return "";
}

void parseOSMData(const std::string& osmJson) {
    // TODO: parse JSON and build your graph data structures
}

void runRouteOptimization() {
    // TODO: implement path finding or optimization logic
}

void displayResults() {
    // TODO: show route or data to user (console output or GUI later)
}
