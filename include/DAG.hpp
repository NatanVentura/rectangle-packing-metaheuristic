#pragma once
#include <util.hpp>

vector<int64_t> calculate_dimension(
    seq_pair &s,
    const vector<int64_t> &weights,
    bool is_vertical
);

// class DAG {
// public:
//     DAG(seq_pair &s, vector<int64_t> weights, bool is_vertical = false);
//     ~DAG() {}
    
//     const vector<int> &get_neighbors(int u);
//     int64_t get_packing_dimension();
//     int64_t get_position(int u);

// private:
//     vector<vector<int>> adj;
//     vector<int64_t> weights;
//     vector<int64_t> positions;
//     bool is_vertical;

//     void build_graph(seq_pair &s);
//     void add_edge(int u, int v);
//     void dfs(int u);
// };