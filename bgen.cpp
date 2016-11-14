#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>

using namespace std;



int bernoulli(int numberOfThrows, double bias)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    // give "true" based on percent bias
    // give "false" based on percent bias
    std::bernoulli_distribution d(bias);

    std::map<bool, int> hist;
    for(int n=0; n<numberOfThrows; ++n) {
        ++hist[d(gen)];
    }
    for(auto p : hist) {
        std::cout << std::boolalpha << std::setw(5) << p.first
                  << ' ' << std::string(p.second/500, '*') << '\n';
    }
}

int main()
{
    // Seed with a real random value, if available
    std::random_device r;

    // Choose a random mean between 1 and 6
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 6);
    int mean = uniform_dist(e1);
    std::cout << "Randomly-chosen mean: " << mean << '\n';

    // Generate a normal distribution around that mean
    std::seed_seq seed2{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 e2(seed2);
    std::normal_distribution<> normal_dist(mean, 2);

    std::map<int, int> hist;
    for (int n = 0; n < 10000; ++n) {
        ++hist[std::round(normal_dist(e2))];
    }
    std::cout << "Normal distribution around " << mean << ":\n";
    for (auto p : hist) {
        std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                  << p.first << ' ' << std::string(p.second/200, '*') << '\n';
    }
}
