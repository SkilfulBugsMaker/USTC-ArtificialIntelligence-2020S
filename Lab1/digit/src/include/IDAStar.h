//
// Created by YxGuo on 4/28/20.
//

#ifndef LAB1_IDASTAR_H
#define LAB1_IDASTAR_H

#include <queue>
#include <vector>
#include <unordered_map>

#include "include.h"
#include "StateManager.h"

struct Info{
    bool in_stack;
    Node *n_his;
};

class IDAStar {

public:
    IDAStar(const char *init_state, const char *dest_state);
    ~IDAStar();
    void graphSearch();
private:
    std::vector<Node *> fringe;
    // std::priority_queue<std::pair<std::pair<int ,int>, Node* > ,std::vector<std::pair<std::pair<int ,int>, Node* > >, std::greater<> > fringe;
    std::vector<Node *> nodes;
    char init_state[DIM*DIM+1];
    char dest_state[DIM*DIM+1];
    bool check(const char* p1, const char *p2);
    int DFS(Node *n, int threshold);
    StateManager *sm;
    const int INF = 100000;
    std::unordered_map<std::string, Info> visited;
};

#endif //LAB1_IDASTAR_H
