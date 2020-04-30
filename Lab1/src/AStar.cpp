//
// Created by YxGuo on 4/28/20.
//
#include "../include/AStar.h"


AStar::~AStar() {
    for (auto & n : this->nodes) {
        delete n;
    }
    delete this->sm;
}

AStar::AStar(const std::string& init_state, const std::string& dest_state) {
    Node *n = new Node;
    n->state = init_state;
    n->from_parent_movement.first = 0;
    n->from_parent_movement.second = '\0';
    n->depth = 0;
    n->parent = nullptr;
    this->nodes.push_back(n);
    this->init_state = init_state;
    this->dest_state = dest_state;
    this->sm = new StateManager(dest_state);
}

Node *AStar::graphSearch() {
    // TODO: add graph search
    // return the final node.
    Node *n = this->nodes[0];
    int h = this->sm->hFunction(n->state);
    int g = n->depth;
    int f = g + h;
    this->fringe.push(std::make_pair(std::make_pair(f, h), std::make_pair(g, n)));
    int print_count = 0;

    while (!fringe.empty()) {
        auto t = fringe.top();
        fringe.pop();
        f = t.first.first;
        h = t.first.second;
        g = t.second.first;
        n = t.second.second;
        if (print_count == 100000) {
            std::cout << "(" << f << ", " << g << ", "<< h << ")" << std::endl;
            print_count = 0;
        }
        print_count ++;
        if (n->state == this->dest_state) {
            return n;
        }
        auto succeeds = this->sm->getSucceedStates(n->state);
        for (auto &s : succeeds) {
            Node *n_tmp = new Node;
            n_tmp->state = s.second;
            n_tmp->from_parent_movement = s.first;
            n_tmp->depth = n->depth + 1;
            n_tmp->parent = n;
            int n_tmp_g = n_tmp->depth;
            int n_tmp_h = this->sm->hFunction(n_tmp->state);
            int n_tmp_f = n_tmp_g + n_tmp_h;
            fringe.push(std::make_pair(std::make_pair(n_tmp_f, n_tmp_h), std::make_pair(n_tmp_g, n_tmp)));
            this->sm->insertIntoCloseSet(n_tmp->state);
            this->nodes.push_back(n_tmp);
        }
    }
    return nullptr;
}



