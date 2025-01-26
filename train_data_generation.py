import numpy as np

# Number of data points and dimensions
N = 10
D = 2

# Random data generation: 100 data points with 2 dimensions and class labels
np.random.seed(42)

# Randomly generate coordinates for N points
coordinates = np.random.uniform(-100, 100, size=(N, D))

# Randomly assign class labels from three categories: class_A, class_B, class_C
class_labels = np.random.choice(['class_A', 'class_B', 'class_C'], size=N)

# Format the output in the requested format
output = []
output.append(f"{N}             % number of training data points N")
output.append(f"{D}               % number of dimensions D")
output.append("% Below is a list of N data points, each described by D coordinates")

for i in range(N):
    point = " ".join(map(str, coordinates[i])) + f" {class_labels[i]}  % point {i+1}"
    output.append(point)

# Join all lines to output as a single string
train_data = "\n".join(output)
print(train_data)
  # Display the first 1000 characters to confirm the format
