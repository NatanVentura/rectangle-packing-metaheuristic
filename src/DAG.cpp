#include <util.hpp>
#include <directed_acyclic_graph.hpp>

seq_pair copy_seq(seq_pair s) {
    return seq_pair(vector<int>(s.first), vector<int>(s.second));
}


DAG::DAG(seq_pair s, vector<double> weights, bool is_vertical) {
    this->weights = weights;
    this->is_vertical = is_vertical;
    this->n = weights.size();
    this->adj = vector<vector<int>>(n+2);
    this->positions = vector<double>(n+2,0);
    build_graph(s);
    dfs(n);
}

void DAG::build_graph(seq_pair s) {
    if(is_vertical){
        reverse(s.f.begin(), s.f.end());
    }

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
            if(pos_f[i] < pos_f[j] && pos_s[i] < pos_s[j]){
                add_edge(i, j);
            }
        }
    }

    int start = n;
    int end = n+1;

    for(int i = 0; i < n; i++){
        add_edge(start, i);
        add_edge(i, end);
    }

    weights.push_back(0);
    weights.push_back(0);
}

void DAG::add_edge(int u, int v) {
    adj[u].push_back(v);
}

vector<int> DAG::get_neighbors(int u) {
    return adj[u];
}

void DAG::dfs(int u) {
    for(auto v : adj[u]){
        dfs(v);
        positions[u] = max(positions[u], positions[v] + weights[v]);
    }
}

double DAG::get_position(int u) {
    return positions[u];
}

double DAG::get_packing_dimension() {
    return positions[n];
}
