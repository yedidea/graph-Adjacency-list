// Email: yedidea9@gmail.com
#include "UnionFind.hpp"
#include <stdexcept>

namespace graph {

/**
 * Creates a UnionFind structure with the given number of elements.
 * At first, every element is its own parent and belongs to its own set.
 */
UnionFind::UnionFind(int size) : parent(0), rank(0), size(size) {
    if (size <= 0) {
        throw std::invalid_argument("UnionFind size must be positive");
    }

    parent = new int[size];
    rank = new int[size];

    for (int i = 0; i < size; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

/**
 * Copy constructor.
 * Copies the parent and rank arrays into new memory.
 */
UnionFind::UnionFind(const UnionFind& other) : parent(0), rank(0), size(other.size) {
    parent = new int[size];
    rank = new int[size];
    for (int i = 0; i < size; i++) {
        parent[i] = other.parent[i];
        rank[i] = other.rank[i];
    }
}

/**
 * Assignment operator.
 * Replaces the current arrays with copies of another UnionFind object.
 */
UnionFind& UnionFind::operator=(const UnionFind& other) {
    if (this != &other) {
        delete[] parent;
        delete[] rank;

        size = other.size;
        parent = new int[size];
        rank = new int[size];

        for (int i = 0; i < size; i++) {
            parent[i] = other.parent[i];
            rank[i] = other.rank[i];
        }
    }
    return *this;
}

/**
 * Releases the dynamic arrays used by UnionFind.
 */
UnionFind::~UnionFind() {
    delete[] parent;
    delete[] rank;
}

/**
 * Checks that an index is inside the valid UnionFind range.
 */
void UnionFind::validate(int x) const {
    if (x < 0 || x >= size) {
        throw std::out_of_range("UnionFind index is out of range");
    }
}

/**
 * Finds and returns the representative of the set that contains x.
 * Path compression is used to shorten future searches.
 */
int UnionFind::find(int x) {
    validate(x);

    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }

    return parent[x];
}

/**
 * Unites the sets that contain x and y.
 * Union by rank is used to keep the trees relatively shallow.
 */
void UnionFind::unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
        return;
    }

    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

/**
 * Returns true if x and y are in the same set.
 */
bool UnionFind::connected(int x, int y) {
    return find(x) == find(y);
}

}
