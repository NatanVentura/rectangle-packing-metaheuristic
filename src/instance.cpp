#include <instance.hpp>
#include <DAG.hpp>

Instance::Instance(vector<int64_t> w, vector<int64_t> h) {
    if(this->w.size() != this->h.size()) {
        throw invalid_argument("Invalid instance");
    }
    this->w = move(w);
    this->h = move(h);
}

vector<int> gen_random_perm(int n){
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    random_shuffle(perm.begin(), perm.end());
    return perm;
}

void Instance::gen_random_seq(int seed) {
    int n = this->w.size();
    srand(seed);
    seq = seq_pair(gen_random_perm(n), gen_random_perm(n));
}

pair<const vector<int64_t> &, const vector<int64_t> &> Instance::get_dimensions() const {
    return {w, h};
}

bool Instance::is_permutation(const vector<int> &v) {
    const int n = w.size();
    if(v.size() != n) {
        return false;
    }

    vector<bool> has(n);
    for(auto t : v) {
        has[t] = 1;
    }
    for(auto t : has) {
        if(!t) {
            return false;
        }
    }
    return true;
}

void Instance::set_seq(seq_pair s) {
    assert(is_permutation(s.first) && is_permutation(s.second));
    seq = move(s);
    calculated = false;
}

void Instance::calculate() {
    if(calculated) {
        return;
    }
    calculated = true;
    w_coord = calculate_dimension(seq, w, false);
    h_coord = calculate_dimension(seq, h, true);

    area = w_coord[w.size()] * h_coord[h.size()];
}

int64_t Instance::get_area() {
    calculate();
    return area;
}

pair<const vector<int64_t> &, const vector<int64_t> &> Instance::get_coords() {
    calculate();
    return {w_coord, h_coord};
}

const seq_pair &Instance::get_seq() {
    return seq;
}

void Instance::flip_block(int i) {
    swap(w[i], h[i]);
}