 g++ -std=c++17 -fdiagnostics-color=always -g main.cpp KNNClassifier.cpp -o knn_classifier
 ./knn_classifier -train train_data.txt -test test_data.txt -out output.txt -k 5
