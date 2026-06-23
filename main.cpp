// Email: yedidea9@gmail.com
#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>
#include <exception>

using namespace graph;

int main()
{
    try
    {
        Graph g(6);

        g.addEdge(0, 1, 4);
        g.addEdge(0, 2, 2);
        g.addEdge(1, 2, 1);
        g.addEdge(1, 3, 5);
        g.addEdge(2, 3, 8);
        g.addEdge(2, 4, 10);
        g.addEdge(3, 4, 2);
        g.addEdge(3, 5, 6);
        g.addEdge(4, 5, 3);

        g.print_graph("Original Graph");

        Graph bfsTree = Algorithms::bfs(g, 0);
        bfsTree.print_graph("BFS Tree from vertex 0");

        Graph dfsTree = Algorithms::dfs(g, 0);
        dfsTree.print_graph("DFS Tree / Forest from vertex 0");

        Graph shortestPaths = Algorithms::dijkstra(g, 0);
        shortestPaths.print_graph("Dijkstra Shortest Paths Tree from vertex 0");

        Graph primTree = Algorithms::prim(g);
        primTree.print_graph("Prim Minimum Spanning Tree");

        Graph kruskalTree = Algorithms::kruskal(g);
        kruskalTree.print_graph("Kruskal Minimum Spanning Tree");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
