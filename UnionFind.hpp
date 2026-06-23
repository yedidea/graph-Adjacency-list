// Email: yedidea9@gmail.com
#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

namespace graph {

class UnionFind {
private:
    int* parent;
    int* rank;
    int size;

    void validate(int x) const;

public:
    UnionFind(int size);
    UnionFind(const UnionFind& other);
    UnionFind& operator=(const UnionFind& other);
    ~UnionFind();

    int find(int x);
    void unite(int x, int y);
    bool connected(int x, int y);
};

}

#endif
