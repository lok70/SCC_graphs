#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
    int V; // количество вершин
    vector<vector<int>> adj; // список смежности
    vector<vector<int>> sccs; // сильно связанные компоненты

    void SCCUtil(int u, int disc[], int low[], stack<int>& st, bool stackMember[]);

public:
    Graph(int V);
    void addEdge(int v, int w);
    void SCC();
    void printSCCs();
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::SCCUtil(int u, int disc[], int low[], stack<int>& st, bool stackMember[]) {
    static int time = 0;

    disc[u] = low[u] = ++time;
    st.push(u);
    stackMember[u] = true;

    for (int v : adj[u]) {
        if (disc[v] == -1) {
            SCCUtil(v, disc, low, st, stackMember);
            low[u] = min(low[u], low[v]);
        }
        else if (stackMember[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    int w = 0;
    if (low[u] == disc[u]) {
        vector<int> scc;
        while (st.top() != u) {
            w = st.top();
            scc.push_back(w);
            stackMember[w] = false;
            st.pop();
        }
        w = st.top();
        scc.push_back(w);
        stackMember[w] = false;
        st.pop();
        sccs.push_back(scc);
    }
}

void Graph::SCC() {
    int* disc = new int[V];
    int* low = new int[V];
    bool* stackMember = new bool[V];
    stack<int> st;

    for (int i = 0; i < V; i++) {
        disc[i] = -1;
        low[i] = -1;
        stackMember[i] = false;
    }

    for (int i = 0; i < V; i++) {
        if (disc[i] == -1) {
            SCCUtil(i, disc, low, st, stackMember);
        }
    }

    delete[] disc;
    delete[] low;
    delete[] stackMember;
}

void Graph::printSCCs() {
    for (const auto& scc : sccs) {
        for (int v : scc) {
            cout << v << " ";
        }
        cout << endl;
    }
}


