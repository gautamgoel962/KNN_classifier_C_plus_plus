// KNNClassifier.h
#ifndef KNNCLASSIFIER_H
#define KNNCLASSIFIER_H

#include <vector>
#include <string>

/**
 * @brief A class for K-Nearest Neighbors classification.
 */
class KNNClassifier {
public:
    /**
     * @brief Constructs a KNNClassifier with a specified k.
     * @param k The number of nearest neighbors to consider.
     */
    KNNClassifier(int k);

    /**
     * @brief Loads training data from a file.
     * @param filename The path to the training data file.
     * @return True if loading is successful, false otherwise.
     */
    bool loadTrainingData(const std::string& filename);

    /**
     * @brief Classifies test data from a file and writes the output.
     * @param testFile The path to the test data file.
     * @param outputFile The path to the output file.
     * @return True if classification is successful, false otherwise.
     */
    bool classify(const std::string& testFile, const std::string& outputFile);

private:
    int k;
    int dimensions;
    std::vector<std::vector<double>> trainingPoints;
    std::vector<std::string> trainingLabels;

    /**
     * @brief Calculates the Euclidean distance between two points.
     * @param a The first point.
     * @param b The second point.
     * @return The Euclidean distance.
     */
    double distance(const std::vector<double>& a, const std::vector<double>& b);

    /**
     * @brief Determines the majority class among nearest neighbors.
     * @param neighbors The class labels of nearest neighbors.
     * @return The majority class label.
     */
    std::string majorityClass(const std::vector<std::string>& neighbors);
};

#endif // KNNCLASSIFIER_H
