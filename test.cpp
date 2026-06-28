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

/**
 * Tests basic graph edge insertion, removal, and undirected edge behavior.
 */
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

/**
 * Tests that invalid graph inputs throw the expected exceptions.
 */
TEST_CASE("Graph input validation") {
    CHECK_THROWS_AS(Graph(0), std::invalid_argument);

    Graph g(3);
    CHECK_THROWS_AS(g.addEdge(-1, 2, 1), std::out_of_range);
    CHECK_THROWS_AS(g.addEdge(0, 4, 1), std::out_of_range);
    CHECK_THROWS_AS(g.addEdge(0, 1, -5), std::invalid_argument);
    CHECK_THROWS_AS(g.addEdge(1, 1, 2), std::invalid_argument);
    CHECK_THROWS_AS(g.removeEdge(0, 2), std::runtime_error);
}

/**
 * Tests that the graph copy constructor creates an independent deep copy.
 */
TEST_CASE("Graph copy constructor creates deep copy") {
    Graph g(3);
    g.addEdge(0, 1, 5);

    Graph copy = g;
    copy.addEdge(1, 2, 8);

    CHECK(g.edgeExists(0, 1));
    CHECK(!g.edgeExists(1, 2));
    CHECK(copy.edgeExists(1, 2));
}

/**
 * Tests that BFS returns a traversal tree from the source vertex.
 */
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

/**
 * Tests that DFS returns only tree edges and does not include back edges.
 */
TEST_CASE("DFS returns only tree edges") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(0, 3, 1);

    Graph tree = Algorithms::dfs(g, 0);

    CHECK(tree.getEdgeCount() == 3);
}

/**
 * Tests that Dijkstra returns the expected shortest paths tree.
 */
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


/**
 * Tests the total weight and edge count of the MST returned by Prim.
 */
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

/**
 * Tests the total weight and edge count of the MST returned by Kruskal.
 */
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

/**
 * Tests that MST algorithms reject disconnected graphs.
 */
TEST_CASE("Prim and Kruskal throw exceptions on disconnected graph") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 1);

    CHECK_THROWS_AS(Algorithms::prim(g), std::runtime_error);
    CHECK_THROWS_AS(Algorithms::kruskal(g), std::runtime_error);
}

/**
 * Tests basic UnionFind operations: unite and connected.
 */
TEST_CASE("UnionFind basic behavior") {
    UnionFind uf(5);

    CHECK(!uf.connected(0, 1));
    uf.unite(0, 1);
    CHECK(uf.connected(0, 1));

    uf.unite(1, 2);
    CHECK(uf.connected(0, 2));
    CHECK(!uf.connected(0, 3));
}

/**
 * Tests that UnionFind validates invalid indexes.
 */
TEST_CASE("UnionFind invalid indexes throw exceptions") {
    UnionFind uf(4);

    CHECK_THROWS_AS(uf.find(-1), std::out_of_range);
    CHECK_THROWS_AS(uf.find(4), std::out_of_range);

    CHECK_THROWS_AS(uf.unite(0, 4), std::out_of_range);
    CHECK_THROWS_AS(uf.unite(-1, 2), std::out_of_range);

    CHECK_THROWS_AS(uf.connected(0, 5), std::out_of_range);
    CHECK_THROWS_AS(uf.connected(-1, 3), std::out_of_range);
}

/**
 * Tests FIFO behavior and empty-queue exception handling.
 */
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

/**
 * Tests that popMin returns items by increasing priority.
 */
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


/**
 * Tests that decreaseKey lowers the priority of an existing item.
 */
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

/**
 * Tests that decreaseKey does not increase an item priority.
 */
TEST_CASE("PriorityQueue decreaseKey does not increase priority") {
    PriorityQueue pq(3);

    pq.push(1, 10);
    pq.push(2, 20);

    pq.decreaseKey(1, 50);

    PQItem first = pq.popMin();

    CHECK(first.vertex == 1);
    CHECK(first.priority == 10);
}

/**
 * Tests that decreaseKey rejects vertices that are not in the queue.
 */
TEST_CASE("PriorityQueue decreaseKey throws an exception for missing vertex") {
    PriorityQueue pq(3);

    pq.push(1, 20);

    CHECK_THROWS_AS(pq.decreaseKey(2, 5), std::runtime_error);
}

/**
 * Tests that push throws when the priority queue reaches capacity.
 */
TEST_CASE("PriorityQueue throws an exception when full") {
    PriorityQueue pq(2);

    pq.push(0, 5);
    pq.push(1, 3);

    CHECK_THROWS_AS(pq.push(2, 1), std::runtime_error);
}

/**
 * Tests that algorithms reject invalid start/source vertices.
 */
TEST_CASE("Algorithms validate source vertices") {
    Graph g(3);
    g.addEdge(0, 1, 1);

    CHECK_THROWS_AS(Algorithms::bfs(g, -1), std::out_of_range);
    CHECK_THROWS_AS(Algorithms::dfs(g, 3), std::out_of_range);
    CHECK_THROWS_AS(Algorithms::dijkstra(g, 5), std::out_of_range);
}

/**
 * Tests that getWeight throws for a missing edge.
 */
TEST_CASE("Graph getWeight throws an exception when edge does not exist") {
    Graph g(3);
    g.addEdge(0, 1, 4);

    CHECK(g.getWeight(0, 1) == 4);
    CHECK_THROWS_AS(g.getWeight(0, 2), std::runtime_error);
}

/**
 * Tests for invalid capacity for Queue, PriorityQueue, and UnionFind.
 */

TEST_CASE("Queue invalid capacity throws exception") {
    CHECK_THROWS_AS(Queue(0), std::invalid_argument);
}

TEST_CASE("PriorityQueue invalid capacity throws exception") {
    CHECK_THROWS_AS(PriorityQueue(0), std::invalid_argument);
}

TEST_CASE("UnionFind invalid size throws exception") {
    CHECK_THROWS_AS(UnionFind(0), std::invalid_argument);
}


