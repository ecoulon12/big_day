#ifndef MAP_H
#define MAP_H

#include <string>
#include <unordered_map>
#include <vector>

// Declare functions
struct Node {
  long long id;
  double lat;
  double lon;

  virtual ~Node() {}
};

struct RoadNode : public Node {};

struct HotSpot : public Node {
  std::string name;
  int numSpecies;
};

class Graph {
 public:
 private:
};

#endif