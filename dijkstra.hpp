#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

// code from http://rosettacode.org/wiki/Dijkstra%27s_algorithm#C.2B.2B

#include <vector>
#include <string>
#include <list>
#include <limits> // for numeric_limits
#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>

typedef int vertex_t;
typedef double weight_t;

const weight_t max_weight = std::numeric_limits<double>::infinity();

struct neighbor {
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
        : target(arg_target), weight(arg_weight) { }
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;

void DijkstraComputePaths (vertex_t source,
                          const adjacency_list_t &adjacency_list,
                          std::vector<weight_t> &min_distance,
                          std::vector<vertex_t> &previous);

std::list<vertex_t> DijkstraGetShortestPathTo (
                        vertex_t vertex, const std::vector<vertex_t> &previous);

#endif // DIJKSTRA_HPP
