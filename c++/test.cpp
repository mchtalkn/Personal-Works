// shuffle algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::shuffle
#include <vector>       // std::vector
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

int main ()
{
    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);

    while(true)
    {
      std::vector<int> foo{1,2,3,4,5};

      std::shuffle(foo.begin(), foo.end(), e);

      std::cout << "shuffled elements:";
      for (int& x: foo) std::cout << ' ' << x;
      std::cout << '\n';
    }

    return 0;
}
