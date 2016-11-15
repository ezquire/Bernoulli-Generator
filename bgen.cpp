#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>

using namespace std;

/***********FUNCTION PROTOTYPES********/

void bgen(const char*, int, int, float, int, const char*);

/***********DECLARED VARIABLES***********/

//Variable for number of tosses the user would like to see.
const char* GEN_MODE = "gen";
const char* STAT_MODE = "stat"
int numberOfExperiments = 0;
int numberOfTrials = 0;
float probabilityBias = 0.0;
int generator = 0;  //Selecting 0, 1, 2 selects from three different random generators
const char* filename = "output.txt"

// Variable for selecting which side of the coin gets more bias
// where 1 > bias and 0 < bias. Bias is initialized to 0.5 to indicated an unbiased coin.
double bias = 0.5;

//Boolean variable for selecting the mode. Default is "0" or "stat mode".

int main() {
    bgen("gen", 100000, 10, 0.1, "output.txt");
}

void bgen(const char* mode, int N, int T, float P, const char* filename)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::bernoulli_distribution d(P);

    std::map<bool, int> hist;
    for(int n=0; n<N; ++n) {
        ++hist[d(gen)];
    }
    for(auto p : hist) {
        std::cout << std::boolalpha << std::setw(5) << p.first
                  << ' ' << std::string(p.second/500, '*') << '\n';
    }
}

int randomizer()
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

bool getGenerator() {
    int mode = 0;
    cout << "Pick one";
    cin >> mode;
    switch(mode) {
        case 1 :
            return 1;
        case 0 :
            return 0;
    }
}
