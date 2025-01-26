// KNNClassifier.cpp

#include "KNNClassifier.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include <algorithm>
#include <iostream>

KNNClassifier::KNNClassifier(int k) : k(k), dimensions(0) {}
// KNNClassifier::KNNClassifier(int k){
//     k = k;
//     dimensions = 0;
// }

bool KNNClassifier::loadTrainingData(const std::string& filename) {

    std::ifstream infile(filename);

    if (!infile){
        std::cerr << "Error: Could not open the file: " << filename << std::endl;
        return false;
    }

    std::string line;

    bool metadataParsed = false;
    int training_data_points = 0, dimensions = 0;
    while (std::getline(infile, line)) {
        if (line.empty() || line[0] == '%') continue;

        std::stringstream ss(line);

        if (!metadataParsed) {
            if (line.find("number of training data points") != std::string::npos) {
                ss >> training_data_points;
                continue;
            } else if (line.find("number of dimensions") != std::string::npos) {
                ss >> dimensions; 
                metadataParsed = true; 
                continue;
            }
        }

        if (metadataParsed) {
            std::vector<double> coordinates;
            double value;
            for (int i = 0; i < dimensions; ++i) {
                ss >> value;
                coordinates.push_back(value);
            }

            std::string classLabel;
            ss >> classLabel;

            trainingPoints.push_back(coordinates);
            trainingLabels.emplace_back(classLabel);
        }
    }

    return true;
}

double KNNClassifier::distance(const std::vector<double>& a, const std::vector<double>& b) {
    double dist = 0.0;
    for (size_t i = 0; i < a.size(); ++i)
        dist += pow(a[i] - b[i], 2);
    return sqrt(dist);
}

std::string KNNClassifier::majorityClass(const std::vector<std::string>& neighbors) {
    std::map<std::string, int> countMap;
    // neighbours: [class_A, class_A, class_B]
    // countMap: {class_A: 2, class_B: 1}

    for (const auto& label : neighbors) {
        countMap[label]++;
    }
    return std::max_element(countMap.begin(), countMap.end(),
                           [](const std::pair<std::string, int>& a,
                              const std::pair<std::string, int>& b) -> bool {
                               return a.second < b.second;
                           })->first;
}

bool KNNClassifier::classify(const std::string& testFile, const std::string& outputFile) {
    std::ifstream infile(testFile);
    if (!infile){
        std::cerr << "Error: Could not open the file: " << testFile << std::endl;
        return false;
    }

    std::ofstream outfile(outputFile);
    if (!outfile){
        std::cerr << "Error: Could not open the file: " << outputFile << std::endl;
        return false;
    }

    int test_data_points = 0, dimensions = 0;
    std::string line;
    bool metadataParsed = false;

    while (std::getline(infile, line)) {

        if (line.empty() || line[0] == '%') {
            continue;
        }

        std::stringstream ss(line);
        if (!metadataParsed) {
            if (line.find("number of test data points") != std::string::npos) {
                ss >> test_data_points; 
                continue;
            } else if (line.find("number of dimensions") != std::string::npos) {
                ss >> dimensions; 
                metadataParsed = true;
                continue;
            }
        }

        if (metadataParsed) {
            std::vector<double> testCoords;
            double value;
            for (int i = 0; i < dimensions; ++i) {
                ss >> value;
                testCoords.push_back(value);
            }

            std::vector<std::pair<double, std::string>> distances;
            // 100 training points
            // we will have 100 distances
            // (1,  "class_A"), (4, "class_A"),....(2, "class_B")
            for (size_t i = 0; i < trainingPoints.size(); ++i) {
                double dist = distance(testCoords, trainingPoints[i]);
                distances.emplace_back(dist, trainingLabels[i]);
            }

            std::sort(distances.begin(), distances.end(),
                    [](const std::pair<double, std::string>& a,
                        const std::pair<double, std::string>& b) -> bool {
                            return a.first < b.first;
                        });

            std::vector<std::string> neighbors;
            for (int i = 0; i < k && i < distances.size(); ++i)
                neighbors.push_back(distances[i].second);

            std::string predicted = majorityClass(neighbors);
            outfile << line << " " << predicted << "\n";
        }
    }

    return true;
}