// Classe para representar uma instância do problema de Rectangle Packing
#pragma once
#include <util.hpp>

class Instance {
public:
    Instance(vector<int64_t> w, vector<int64_t> h);
    ~Instance() {}
    int64_t get_area();
    pair<const vector<int64_t> &, const vector<int64_t> &> get_coords();
    const seq_pair &get_seq();
    void flip_block(int i);
    void set_seq(seq_pair s);
    pair<const vector<int64_t> &, const vector<int64_t> &> get_dimensions() const;
    void gen_random_seq(int seed=45);

private:
    bool is_permutation(const vector<int> &v);

    seq_pair seq;
    int64_t area;
    vector<int64_t> w_coord, h_coord;
    vector<int64_t> w, h;
    
    void calculate();
    bool calculated = false;
};