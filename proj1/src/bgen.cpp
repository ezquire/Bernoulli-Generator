#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
using namespace std;

/*************FUNCTION PROTOTYPES************/

void bgen(const char*, int, int, float, int, const char*);

/********************************************/

int main(int argc, char** argv) {

    const char*  mode = argv[1];
    int  N =  atoi(argv[2]);
    int  T = atoi(argv[3]);
    float  P = atof(argv[4]);
    int  G = atoi(argv[5]);
    const char*  filename = argv[6];

   //Error checking for number of arguments
    if (argc > 7) {
      cout << "Eror: You gave me too many arguments. Make sure you have all the arguments needed, there should be 7." << endl;
      exit(0);
    } else if (argc < 7) {
      cout << "Error: You gave me too few arguments. Make sure you have all the arguments needed, there should be 7." << endl;
      exit(0);
    }

    //Error checking for an acceptable number of experiments
    if (N < 1) {
      cout << "Error: I need a value for N that is greater than 0 in order to run an experiment. Try inputting 1 for N." << endl;
      exit(0);
    }

    //Error checking for ability to create uint32_t
    if (N < 2 && T < 32) {
      cout << "Error: I need a product of N*T that is greater than or equal to 32 in order to ouput a number." << endl;
      exit(0);
    }

    //Error checking for correct bias
    if (P < 0.0 || P > 1.0) {
      cout << "Error: You entered an out-of-bounds value for the P argument. Believe me. Trust me. That, I can tell you.";
      exit (0);
    }

    //Error checking for the correct generator
    if (G < 0 || G > 2) {
      cout << "Error: That random number generator is not supported. I can only accept values 0, 1, or 2 for the G argument. Try one of those!" << endl;
      exit(0);
    }

    /*//Error checking for the correct bgen utility mode
    if (mode != "gen") {
      cout << "Sorry, I can only accept one mode for the bgen utility at the moment, please enter gen for the mode and try again. Stat mode is coming soon!" << endl;
      exit(0);
    }*/

    //Error checking for filename have to look this up and add later

	  bgen(mode, N, T, P, G, filename);

}

void bgen(const char* mode, int N, int T, float P, int G, const char* filename) {

    uint32_t trialTracker = 0; // Sets the trialTracker to zero, AKA a bit string of 32 0's
    int Taccumulator = 0;

    int generator = G;

    switch (generator) {

      case 0 : {
        std::random_device minstd;
        std::minstd_rand gen0(minstd());
        std::bernoulli_distribution d(P);

        for(int n=0; n<N; ++n) {
          trialTracker = 0;
          for(int i=0; i<T; ++i){
            bool coinFlipResults = d(gen0);
            if (coinFlipResults == true) {
              trialTracker |= (1 << i);
            }
            ++Taccumulator;
            if(Taccumulator == 32) {
              ofstream outputFile;
              outputFile.open(filename, ios::out | ios::app);

              if (outputFile.is_open()) {
                outputFile << trialTracker << std::endl;
                outputFile.close();
              }
              else {
                cout << "Unable to open the output file.";
              }
              Taccumulator = 0;
            }
          }
        }
        break;
      }

      case 1 : {
          std::random_device knuth;
          std::knuth_b gen1(knuth());
          std::bernoulli_distribution d(P);
          for(int n=0; n<N; ++n) {
            trialTracker = 0;
            for(int i=0; i<T; ++i){
              bool coinFlipResults = d(gen1);
              if (coinFlipResults == true) {
                trialTracker |= (1 << i);
              }
              ++Taccumulator;
              if(Taccumulator == 32) {
                ofstream outputFile;
                outputFile.open(filename, ios::out | ios::app);

                if (outputFile.is_open()) {
                  outputFile << trialTracker << std::endl;
                  outputFile.close();
                }
                else {
                  cout << "Unable to open the output file.";
                }
                Taccumulator = 0;
              }
            }
          }
          break;
        }

      case 2 : {
          std::random_device ranlux;
          std::ranlux24_base gen2(ranlux());
          std::bernoulli_distribution d(P);
          for(int n=0; n<N; ++n) {
            trialTracker = 0;
            for(int i=0; i<T; ++i){
              bool coinFlipResults = d(gen2);
              if (coinFlipResults == true) {
                trialTracker |= (1 << i);
              }
              ++Taccumulator;
              if(Taccumulator == 32) {
                ofstream outputFile;
                outputFile.open(filename, ios::out | ios::app);

                if (outputFile.is_open()) {
                  outputFile << trialTracker << std::endl;
                  outputFile.close();
                }
                else {
                  cout << "Unable to open the output file.";
                }
                Taccumulator = 0;
              }
            }
          }
          break;
        }
      }
    }
