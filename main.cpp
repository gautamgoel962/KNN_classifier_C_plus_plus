// main.cpp

#include "KNNClassifier.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

/**
 * @brief Prints the usage manual.
 */
void printHelp() {
    std::cout << "Usage: knn_classifier -train <training_file> -test <test_file> -out <output_file> -k <num_neighbors>\n";
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printHelp();
        return 0;
    }

    std::string trainFile, testFile, outFile;
    int k = 3; // Default value

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-train" && i + 1 < argc) {
            trainFile = argv[++i];
        } else if (arg == "-test" && i + 1 < argc) {
            testFile = argv[++i];
        } else if (arg == "-out" && i + 1 < argc) {
            outFile = argv[++i];
        } else if (arg == "-k" && i + 1 < argc) {
            k = std::atoi(argv[++i]);
        }
    }

    if (trainFile.empty() || testFile.empty() || outFile.empty()) {
        printHelp();
        return 1;
    }

    KNNClassifier knn(k);
    if (!knn.loadTrainingData(trainFile)) {
        std::cerr << "Failed to load training data.\n";
        return 1;
    }

    if (!knn.classify(testFile, outFile)) {
        std::cerr << "Failed to classify test data.\n";
        return 1;
    }

    return 0;
}