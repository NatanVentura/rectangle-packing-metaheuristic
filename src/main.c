#include <util.hpp>
#include <DAG.hpp>
#include <instance.hpp>
#include <simulated_annealing.hpp>
#include <evolutionary_algorithm.hpp>

int main()
{
    vector<double> w = {1, 2.9, 3, 4, 5,6.1,7,8,9,10,1, 2.9, 3, 4, 5,6.1,7,8,9,10,11,1, 2.9, 3, 4, 5,6.1,7,8,9,10,11,1, 2.9, 3, 4, 5,6.1,7,8,9,10,11};
    vector<double> h = {1, 2.9, 3, 4, 5,6.1,7,8,9,10,1, 2.9, 3, 4, 5,6.1,7,8,9,10,11,1, 2.9, 3, 4, 5,6.1,7,8,9,10,11,1, 2.9, 3, 4, 5,6.1,7,8,9,10,11};

    srand(time(NULL));
    
    cout << "START" << endl;


    EvolutionaryAlgorithm ea(w,h,10);
    ea.initialize(27, 100, 0.6, 0.4);

    Instance instance = ea.get_best_solution();

    cout << w.size() << endl;
    cout<<instance.get_area()<<endl;
    SimulatedAnnealing sa(instance,2);
    sa.initialize(100000, 0.99);
    sa.optimize();
    instance = sa.get_best_solution();
    for(auto c : instance.get_dimensions())
    {
        cout << c.f << " " << c.s << endl;
    }
    for(auto c : instance.get_coords())
    {
        cout << c.f << " " << c.s << endl;
    }
    cout << instance.get_area() << endl;
    return 0;
}