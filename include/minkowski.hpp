#include <vector>
#include <set>
#include <utility>
#include <string>

/**
* For Minkowski sums
**/

std::set<std::pair<int,int>> NaiveIteration(std::set<std::pair<int,int>> s, std::set<std::pair<int,int>> init);
std::set<std::pair<int,int>> powering(std::set<std::pair<int,int>> init, int nbIterations);

/**
* Other functions
**/

std::set<std::pair<int,int>> buildCounterExample();
std::set<std::pair<int,int>> readFile(std::string filename);
