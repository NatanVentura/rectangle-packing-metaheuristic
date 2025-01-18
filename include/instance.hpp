// Classe para representar uma instância do problema de Rectangle Packing
#pragma once
#include <util.hpp>

class Instance {
    public:
        Instance(vector<double> w, vector<double> h);
        ~Instance() {}
        int get_area();
        vector<coord> get_coords();
        seq_pair get_seq();
        void flip_block(int i);
        void set_seq(seq_pair s);
        vector<coord> get_dimensions();

    private:
        int n;
        seq_pair seq;
        double area;
        vector<coord> coords;
        vector<double> w, h;
        void gen_random_seq(int seed=45);
        bool is_permutation(vector<int> v);
        void calculate();
        bool calculated = false;
};