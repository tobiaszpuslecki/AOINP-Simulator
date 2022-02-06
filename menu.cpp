#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include "Data.hpp"
#include "Reference.hpp"
#include "Genetic.hpp"
#include <chrono>


Data data;

void appendToResultFileReference(std::string fileName, int optimum)
{
  std::ofstream outfile;

  outfile.open("accumulatedResultsReference.csv", std::ios_base::app);
  outfile << fileName << "," << data.result << "," << optimum
  << "," << std::setprecision(5) << data.result/static_cast<float>(optimum)*100
   << "\n";

   outfile.close();
}

void appendToResultFileGenetic(std::string fileName, int optimum)
{
  std::ofstream outfile;

  outfile.open("accumulatedResultsGenetic.csv", std::ios_base::app);
  outfile << fileName << "," << data.result << "," << optimum << ","
  << data.stopCriteria << "," << data.populationSize << "," << data.mutationFactor << "," <<  data.crossFactor << ","
  << data.crossMethodVariant << "," << data.mutationMethodVariant
   << "\n";

   outfile.close();
}



std::vector<std::pair<std::string, int>> fileNames = {
//  {"f1_l-d_kp_10_269", 295},
//  {"f2_l-d_kp_20_878", 1024},
//   {"f3_l-d_kp_4_20", 35},
  // {"f4_l-d_kp_4_11", 23},
  // {"f6_l-d_kp_10_60", 52},
  // {"f7_l-d_kp_7_50", 107},
  // {"f8_l-d_kp_23_10000", 9767},
  // {"f9_l-d_kp_5_80", 130},
  // {"f10_l-d_kp_20_879", 1025},
   {"knapPI_1_10000_1000_1", 563647},
  // {"knapPI_1_1000_1000_1", 54503},
  // {"knapPI_1_100_1000_1", 9147},
//   {"knapPI_1_2000_1000_1", 110625},
  // {"knapPI_1_200_1000_1", 11238},
//   {"knapPI_1_5000_1000_1", 276457},
  // {"knapPI_1_500_1000_1", 28857},
   {"knapPI_2_10000_1000_1", 90204},
  // {"knapPI_2_1000_1000_1", 9052},
  // {"knapPI_2_100_1000_1", 1514},
//   {"knapPI_2_2000_1000_1", 18051},
  // {"knapPI_2_200_1000_1", 1634},
//   {"knapPI_2_5000_1000_1", 44356},
  // {"knapPI_2_500_1000_1", 4566},
   {"knapPI_3_10000_1000_1", 146919},
  // {"knapPI_3_1000_1000_1", 14390},
  // {"knapPI_3_100_1000_1", 2397},
//   {"knapPI_3_2000_1000_1", 28919},
//   {"knapPI_3_200_1000_1", 2697},
//   {"knapPI_3_5000_1000_1", 72505},
//  {"knapPI_3_500_1000_1", 7117}
};





void readInstanceFrom(std::string filename)
{
  std::ifstream ifs (filename, std::ifstream::in);

  data.profits.clear();
  data.weights.clear();

  ifs >> data.instanceSize;
  ifs >> data.maxCapacity;

  int buff;

  for (size_t i = 0; i < data.instanceSize; i++)
  {
    ifs >> buff;
    data.profits.push_back(buff);
    ifs >> buff;
    data.weights.push_back(buff);
  }

  ifs.close();
}

void calculateReference(std::string filename, int optimum)
{
  readInstanceFrom(filename);
  reference(data);
  appendToResultFileReference(filename, optimum);
  float div = data.result/static_cast<float>(optimum)*100;

  std::cout << "\nR: "<< std::setw(22) << filename << " | "
   // << std::setw(8) << data.result << " | "
  // << std::setw(8) << optimum
  << std::setprecision(5)
  << " (" << div << ")";
}

int idx = 1440;

int calculateGenetic(std::string filename, int optimum, int stopCriteria, int populationSize,
double mutationFactor, double crossFactor, int crossMethodVariant, int mutationMethodVariant)
{
    data.stopCriteria = stopCriteria;
    data.populationSize = populationSize;
    data.mutationFactor = mutationFactor;
    data.crossFactor = crossFactor;
    data.crossMethodVariant = crossMethodVariant;
    data.mutationMethodVariant = mutationMethodVariant;

    
  readInstanceFrom(filename);
  genetic(data);
  appendToResultFileGenetic(filename, optimum);
  float div = data.result/static_cast<float>(optimum)*100;

  std::cout << "\n"<< idx--<< ". G: "<< std::setw(22) << filename << " | "
    << std::setw(8) << data.result << " | "
   << std::setw(8) << optimum
  << std::setprecision(5)
  << " (" << div << ")";
    
    return data.result;
}

int main()
{
//  for(const auto& name : fileNames)
//    calculateReference(name.first, name.second);
//  std::cout << "\n";
//
//    int n = 10;
//    std::vector<int> stopCriteriaVec {5 , 10, 15};
//    std::vector<int> populationSizeVec {100, 1000, 10000};
//    std::vector<double> mutationFactorVec {0.01, 0.05};
//    std::vector<double> crossFactorVec {0.8, 0.9};
//    std::vector<int> crossMethodVariantVec {1, 2};
//    std::vector<int> mutationMethodVariantVec {1, 2};
    
//    int n = 10;
//    std::vector<int> stopCriteriaVec {10};
//    std::vector<int> populationSizeVec {10000};
//    std::vector<double> mutationFactorVec {0.01};
//    std::vector<double> crossFactorVec {0.9};
//    std::vector<int> crossMethodVariantVec {1, 2};
//    std::vector<int> mutationMethodVariantVec {2};
//
//    for(const auto& stopCriteria : stopCriteriaVec)
//        for(const auto& populationSize : populationSizeVec)
//            for(const auto& mutationFactor : mutationFactorVec)
//                for(const auto& crossFactor : crossFactorVec)
//                    for(const auto& crossMethodVariant : crossMethodVariantVec)
//                        for(const auto& mutationMethodVariant : mutationMethodVariantVec)
//                            for(int i=0;i<n;i++)
//                                for(const auto& name : fileNames)
//                                {
//                                    calculateGenetic(name.first, name.second, stopCriteria, populationSize,
//                                                     mutationFactor, crossFactor, crossMethodVariant, mutationMethodVariant);
//                                }

    int testDuration = 60;
    calculateGenetic("knapPI_1_10000_1000_1", 563647, testDuration, 10000,
                     0.05, 0.9, 2, 1);
    calculateGenetic("knapPI_2_10000_1000_1", 90204, testDuration, 10000,
                     0.01, 0.8, 2, 2);
    calculateGenetic("knapPI_3_10000_1000_1", 146919, testDuration, 10000,
                     0.01, 0.9, 2, 1);
    testDuration = 120;
    calculateGenetic("knapPI_1_10000_1000_1", 563647, testDuration, 10000,
                     0.05, 0.9, 2, 1);
    calculateGenetic("knapPI_2_10000_1000_1", 90204, testDuration, 10000,
                     0.01, 0.8, 2, 2);
    calculateGenetic("knapPI_3_10000_1000_1", 146919, testDuration, 10000,
                     0.01, 0.9, 2, 1);
    testDuration = 180;
    calculateGenetic("knapPI_1_10000_1000_1", 563647, testDuration, 10000,
                     0.05, 0.9, 2, 1);
    calculateGenetic("knapPI_2_10000_1000_1", 90204, testDuration, 10000,
                     0.01, 0.8, 2, 2);
    calculateGenetic("knapPI_3_10000_1000_1", 146919, testDuration, 10000,
                     0.01, 0.9, 2, 1);
    testDuration = 360;
    calculateGenetic("knapPI_1_10000_1000_1", 563647, testDuration, 10000,
                     0.05, 0.9, 2, 1);
    calculateGenetic("knapPI_2_10000_1000_1", 90204, testDuration, 10000,
                     0.01, 0.8, 2, 2);
    calculateGenetic("knapPI_3_10000_1000_1", 146919, testDuration, 10000,
                     0.01, 0.9, 2, 1);
    testDuration = 720;
    calculateGenetic("knapPI_1_10000_1000_1", 563647, testDuration, 10000,
                     0.05, 0.9, 2, 1);
    calculateGenetic("knapPI_2_10000_1000_1", 90204, testDuration, 10000,
                     0.01, 0.8, 2, 2);
    calculateGenetic("knapPI_3_10000_1000_1", 146919, testDuration, 10000,
                     0.01, 0.9, 2, 1);

  std::cout << "\n";

}
