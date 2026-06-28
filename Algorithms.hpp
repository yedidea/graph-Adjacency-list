// Email: yedidea9@gmail.com
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"

namespace graph {

/**
 * Provides graph algorithms that operate on the Graph class.
 *
 * Each algorithm receives an existing graph and returns a new graph that
 * represents the result, such as a traversal tree, a shortest paths tree,
 * or a minimum spanning tree.
 */
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
