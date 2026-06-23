// Email: yedidea9@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.hpp"
#include "Algorithms.hpp"
#include "Queue.hpp"
#include "PriorityQueue.hpp"
#include "UnionFind.hpp"
#include <stdexcept>

using namespace graph;

TEST_CASE("Graph addEdge and removeEdge") {
    Graph g(4);

    g.addEdge(0, 1, 7);
    g.addEdge(1, 2, 3);

    CHECK(g.edgeExists(0, 1));
    CHECK(g.edgeExists(1, 0));
    CHECK(g.getWeight(0, 1) == 7);
    CHECK(g.getEdgeCount() == 2);

    g.removeEdge(0, 1);
    CHECK(!g.edgeExists(0, 1));
    CHECK(!g.edgeExists(1, 0));
    CHECK(g.getEdgeCount() == 1);
}

TEST_CASE("Graph input validation") {
    CHECK_THROWS_AS(Graph(0), std::invalid_argument);

    Graph g(3);
    CHECK_THROWS_AS(g.addEdge(-1, 2, 1), std::out_of_range);
    CHECK_THROWS_AS(g.addEdge(0, 4, 1), std::out_of_range);
    CHECK_THROWS_AS(g.addEdge(0, 1, -5), std::invalid_argument);
    CHECK_THROWS_AS(g.addEdge(1, 1, 2), std::invalid_argument);
    CHECK_THROWS_AS(g.removeEdge(0, 2), std::runtime_error);
}

TEST_CASE("Graph copy constructor creates deep copy") {
    Graph g(3);
    g.addEdge(0, 1, 5);

    Graph copy = g;
    copy.addEdge(1, 2, 8);

    CHECK(g.edgeExists(0, 1));
    CHECK(!g.edgeExists(1, 2));
    CHECK(copy.edgeExists(1, 2));
}

TEST_CASE("BFS returns a tree from source") {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 4, 1);

    Graph tree = Algorithms::bfs(g, 0);

    CHECK(tree.getEdgeCount() == 4);
    CHECK(tree.edgeExists(0, 1));
    CHECK(tree.edgeExists(0, 2));
    CHECK(tree.edgeExists(1, 3));
    CHECK(tree.edgeExists(2, 4));
}

TEST_CASE("DFS returns only tree edges") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(0, 3, 1);

    Graph tree = Algorithms::dfs(g, 0);

    CHECK(tree.getEdgeCount() == 3);
}

TEST_CASE("Dijkstra shortest paths tree") {
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 3);
    g.addEdge(2, 1, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 8);
    g.addEdge(3, 4, 7);

    Graph tree = Algorithms::dijkstra(g, 0);

    CHECK(tree.edgeExists(0, 2));
    CHECK(tree.edgeExists(2, 1));
    CHECK(tree.edgeExists(1, 3));
    CHECK(tree.edgeExists(3, 4));
    CHECK(tree.getTotalWeight() == 13);
}

TEST_CASE("Prim MST total weight") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 3);

    Graph mst = Algorithms::prim(g);

    CHECK(mst.getEdgeCount() == 3);
    CHECK(mst.getTotalWeight() == 6);
}

TEST_CASE("Kruskal MST total weight") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 3);

    Graph mst = Algorithms::kruskal(g);

    CHECK(mst.getEdgeCount() == 3);
    CHECK(mst.getTotalWeight() == 6);
}

TEST_CASE("Prim and Kruskal throw on disconnected graph") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 1);

    CHECK_THROWS_AS(Algorithms::prim(g), std::runtime_error);
    CHECK_THROWS_AS(Algorithms::kruskal(g), std::runtime_error);
}

TEST_CASE("UnionFind basic behavior") {
    UnionFind uf(5);

    CHECK(!uf.connected(0, 1));
    uf.unite(0, 1);
    CHECK(uf.connected(0, 1));

    uf.unite(1, 2);
    CHECK(uf.connected(0, 2));
    CHECK(!uf.connected(0, 3));
}

TEST_CASE("Queue basic behavior") {
    Queue q(3);

    CHECK(q.isEmpty());

    q.enqueue(10);
    q.enqueue(20);

    CHECK(!q.isEmpty());
    CHECK(q.dequeue() == 10);
    CHECK(q.dequeue() == 20);
    CHECK(q.isEmpty());

    CHECK_THROWS_AS(q.dequeue(), std::runtime_error);
}

TEST_CASE("PriorityQueue returns the smallest priority first") {
    PriorityQueue pq(5);

    CHECK(pq.isEmpty());

    pq.push(1, 50);
    pq.push(2, 10);
    pq.push(3, 30);

    PQItem first = pq.popMin();
    PQItem second = pq.popMin();
    PQItem third = pq.popMin();

    CHECK(first.vertex == 2);
    CHECK(first.priority == 10);
    CHECK(second.vertex == 3);
    CHECK(second.priority == 30);
    CHECK(third.vertex == 1);
    CHECK(third.priority == 50);
    CHECK(pq.isEmpty());

    CHECK_THROWS_AS(pq.popMin(), std::runtime_error);
}


TEST_CASE("PriorityQueue decreaseKey updates an existing item") {
    PriorityQueue pq(4);

    pq.push(1, 50);
    pq.push(2, 30);
    pq.push(3, 40);

    CHECK(pq.contains(1));
    CHECK(!pq.contains(0));

    pq.decreaseKey(1, 10);

    PQItem first = pq.popMin();
    CHECK(first.vertex == 1);
    CHECK(first.priority == 10);

    PQItem second = pq.popMin();
    CHECK(second.vertex == 2);
    CHECK(second.priority == 30);
}

TEST_CASE("PriorityQueue decreaseKey throws for missing vertex") {
    PriorityQueue pq(3);

    pq.push(1, 20);

    CHECK_THROWS_AS(pq.decreaseKey(2, 5), std::runtime_error);
}

TEST_CASE("PriorityQueue throws when full") {
    PriorityQueue pq(2);

    pq.push(0, 5);
    pq.push(1, 3);

    CHECK_THROWS_AS(pq.push(2, 1), std::runtime_error);
}

TEST_CASE("Algorithms validate source vertices") {
    Graph g(3);
    g.addEdge(0, 1, 1);

    CHECK_THROWS_AS(Algorithms::bfs(g, -1), std::out_of_range);
    CHECK_THROWS_AS(Algorithms::dfs(g, 3), std::out_of_range);
    CHECK_THROWS_AS(Algorithms::dijkstra(g, 5), std::out_of_range);
}

TEST_CASE("Graph getWeight throws when edge does not exist") {
    Graph g(3);
    g.addEdge(0, 1, 4);

    CHECK(g.getWeight(0, 1) == 4);
    CHECK_THROWS_AS(g.getWeight(0, 2), std::runtime_error);
}

