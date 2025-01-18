#include <util.hpp>
#include <directed_acyclic_graph.hpp>
#include <instance.hpp>
#include <simulated_annealing.hpp>

int main() {
    vector<double> w = {1, 2, 3, 4, 5,6};
    vector<double> h = {1, 2, 3, 4, 5,6};

    srand(time(NULL));

    random_shuffle(w.begin(), w.end());
    Instance instance(w, h);

    cout << w.size() << endl;

    SimulatedAnnealing sa(instance);
    sa.initialize(100000, 0.99);
    sa.optimize();
    instance = sa.get_best_solution();

    for(auto c : instance.get_dimensions()){
        cout << c.f << " " << c.s << endl;
    }

    for(auto c : instance.get_coords()){
        cout << c.f << " " << c.s << endl;
    }

    //cout << instance.get_area() << endl;
    return 0;
}