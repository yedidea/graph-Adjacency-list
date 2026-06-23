// Email: yedidea9@gmail.com
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"

namespace graph {

class Algorithms {
private:
    static void dfsVisit(const Graph& input, Graph& result, int vertex, bool* visited);

public:
    static Graph bfs(const Graph& input, int source);
    static Graph dfs(const Graph& input, int start);
    static Graph dijkstra(const Graph& input, int source);
    static Graph prim(const Graph& input);
    static Graph kruskal(const Graph& input);
};

}

#endif
