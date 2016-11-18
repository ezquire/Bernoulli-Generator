#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

/*************FUNCTION PROTOTYPES************/

void bgen(char*, int, int, float, int, char*);

/********************************************/

int main(int argc, char** argv) {
  char* mode;
  int N;
  int T;
  float P;
  int G;
  char* filename;
  if (argc < 0) {
    std:cout << "You didn't give me any arguments.";
      mode = "gen";
      N =  10;
      T = 32;
      P = 0.5;
      G = 0;
      filename = "output.txt";
  } else {
      mode = argv[1];
      N =  atoi(argv[2]);
      T = atoi(argv[3]);
      P = atof(argv[4]);
      G = atoi(argv[5]);
      filename = argv[6];
   }

      //add error checking here

    if (P < 0.0 || P > 1.0) {
      cout << "You entered an out-of-bounds value for the P argument. Believe me. Trust me. That, I can tell you.";
      exit (0);
    }

    if (T != 32) {
      cout << "I am expecting a 32 bit integer. Enter 32 for T.";
      exit (0);
    }

	  bgen(mode, N, T, P, G, filename);
}

void bgen(char* mode, int N, int T, float P, int G, char* filename)
{
    std::cout << "This is where the function starts." << std::endl;

    if (G == 0) {
      std::random_device minstd;
      std::minstd_rand gen0(minstd());
      std::bernoulli_distribution d(P);
      std::map<bool, int> hist;
      for(int n=0; n<N; ++n) {
          ++hist[d(gen0)];
      } for(auto p : hist) {
          std::cout << std::boolalpha << std::setw(5) << p.first
            << ' ' << std::string(p.second/500, '*') << '\n';
      }

    } else if (G == 1) {
      std::random_device knuth;
      std::knuth_b gen1(knuth());
      std::bernoulli_distribution d(P);
        std::map<bool, int> hist;
        for(int n=0; n<N; ++n) {
          ++hist[d(gen1)];
    } for(auto p : hist) {
          std::cout << std::boolalpha << std::setw(5) << p.first
              << ' ' << std::string(p.second/500, '*') << '\n';
        }
    } else if (G == 2) {
      std::random_device ranlux;
      std::ranlux24_base gen2(ranlux());
      std::bernoulli_distribution d(P);
        std::map<bool, int> hist;
        for(int n=0; n<N; ++n) {
          ++hist[d(gen2)];
        } for(auto p : hist) {
            std::cout << std::boolalpha << std::setw(5) << p.first
              << ' ' << std::string(p.second/500, '*') << '\n';
        }
    }
}
