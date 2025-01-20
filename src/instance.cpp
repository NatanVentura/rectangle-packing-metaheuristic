#include <instance.hpp>
#include <directed_acyclic_graph.hpp>

Instance::Instance(vector<double> w, vector<double> h) {
    if(this->w.size() != this->h.size()) {
        throw invalid_argument("Invalid instance");
    }
    this->n = w.size();
    this->w = w;
    this->h = h;
    this->coords = vector<coord>(n);
    gen_random_seq();
}

vector<int> gen_random_perm(int n){
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    random_shuffle(perm.begin(), perm.end());
    return perm;
}

void Instance::gen_random_seq(int seed) {
    srand(seed);
    seq = seq_pair(gen_random_perm(n), gen_random_perm(n));
}

vector<coord> Instance::get_dimensions() {
    vector<coord> dimensions;
    for(int i = 0; i < n; i++){
        dimensions.push_back({w[i], h[i]});
    }
    return dimensions;
}

bool Instance::is_permutation(vector<int> v) {
    if(v.size() != n) {
        return false;
    }
    vector<int> aux = vector<int>(v);
    sort(aux.begin(), aux.end());
    for (int i = 0; i < aux.size(); i++) {
        if (aux[i] != i) {
            return false;
        }
    }
    return true;
}

void Instance::set_seq(seq_pair s) {
    if (!is_permutation(s.first) || !is_permutation(s.second)) {
        throw invalid_argument("Invalid permutation");
    }
    seq = s;
    calculated = false;
}

void Instance::calculate() {
    if(calculated) {
        return;
    }
    calculated = true;
    DAG horizontal_graph(seq, w);
    DAG vertical_graph(seq, h, true);
    area = horizontal_graph.get_packing_dimension() * vertical_graph.get_packing_dimension();
    for(int i = 0; i < n; i++){
        coords[i].f = horizontal_graph.get_position(i);
        coords[i].s = vertical_graph.get_position(i);
    }
}

double Instance::get_area() {
    calculate();
    return area;
}

vector<coord> Instance::get_coords() {
    calculate();
    return coords;
}

seq_pair Instance::get_seq() {
    return seq;
}

void Instance::flip_block(int i) {
    swap(w[i], h[i]);
}