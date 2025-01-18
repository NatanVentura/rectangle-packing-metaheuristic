#pragma once
#include <util.hpp>

class DAG {
    public:
        DAG(seq_pair s, vector<double> weights, bool is_vertical = false);
        ~DAG() {}
        vector<int> get_neighbors(int u);
        double get_packing_dimension();
        double get_position(int u);

    private:
        int n;
        vector<vector<int>> adj;
        vector<double> weights;
        vector<double> positions;
        bool is_vertical;
        void build_graph(seq_pair s);
        void add_edge(int u, int v);
        void dfs(int u);
};