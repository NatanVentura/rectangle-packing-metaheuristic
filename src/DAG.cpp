#include <util.hpp>
#include <DAG.hpp>

vector<int64_t> calculate_dimension(
    seq_pair &s,
    const vector<int64_t> &weights,
    bool is_vertical
) {
    const size_t n = weights.size();
    
    if(is_vertical) {
        reverse(s.f.begin(), s.f.end());
    }

    auto g = vector<vector<int>>(n + 2);
    auto pos_f = vector<int>(n);
    auto pos_s = vector<int>(n);

    for(int i = 0; i < n; i++){
        pos_f[s.f[i]] = i;
        pos_s[s.s[i]] = i;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(j == i){
                continue;
            }

            if(pos_f[i] < pos_f[j] && pos_s[i] < pos_s[j]) {
                g[i].push_back(j);
            }
        }
    }

    int start = n;
    int end = n + 1;

    for(int i = 0; i < n; i++) {
        g[start].push_back(i);
        g[i].push_back(end);
    }

    vector<int64_t> positions(n + 2);

    auto dfs = function<void (int)>();
    dfs = [&dfs, &g, &positions, &weights, n](int u) {
        for(auto v : g[u]) {
            dfs(v);
            if(v >= n) {
                positions[u] = max(positions[u], positions[v]);
            } else {
                positions[u] = max(positions[u], positions[v] + weights[v]);
            }
        }
    };

    dfs(n);

    if(is_vertical) {
        reverse(s.f.begin(), s.f.end());
    }

    return positions;
}

// DAG::DAG(seq_pair &s, vector<int64_t> weights, bool is_vertical) {
//     const int n = weights.size();
//     this->weights = move(weights);
//     this->is_vertical = is_vertical;
//     this->adj = vector<vector<int>>(n+2);
//     this->positions = vector<int64_t>(n+2,0);
//     build_graph(s);
//     dfs(n);
// }

// void DAG::build_graph(seq_pair &s) {
//     const int n = weights.size();

//     if(is_vertical){
//         reverse(s.f.begin(), s.f.end());
//     }

//     auto pos_f = vector<int>(n);
//     auto pos_s = vector<int>(n);

//     for(int i = 0; i < n; i++){
//         pos_f[s.f[i]] = i;
//         pos_s[s.s[i]] = i;
//     }

//     for(int i = 0; i < n; i++){
//         for(int j = 0; j < n; j++){
//             if(j == i){
//                 continue;
//             }

//             if(pos_f[i] < pos_f[j] && pos_s[i] < pos_s[j]){
//                 add_edge(i, j);
//             }
//         }
//     }

//     int start = n;
//     int end = n+1;

//     for(int i = 0; i < n; i++){
//         add_edge(start, i);
//         add_edge(i, end);
//     }

//     weights.push_back(0);
//     weights.push_back(0);
// }

// void DAG::add_edge(int u, int v) {
//     adj[u].push_back(v);
// }

// const vector<int> &DAG::get_neighbors(int u) {
//     return adj[u];
// }

// void DAG::dfs(int u) {
//     for(auto v : adj[u]){
//         dfs(v);
//         positions[u] = max(positions[u], positions[v] + weights[v]);
//     }
// }

// double DAG::get_position(int u) {
//     return positions[u];
// }

// double DAG::get_packing_dimension() {
//     const int n = weights.size();
//     return positions[n];
// }
