/*
 * Function: reorderArray
 * ----------------------
 * Reorders the elements of an input array based on a given index mapping and stores the result in an output array.
 * 
 * Template:
 * - T: The data type of the elements in the arrays (e.g., int, float, byte, char, etc.).
 *
 * Parameters:
 * - inputArray[]: The source array containing the elements to reorder.
 * - outputArray[]: The target array where reordered elements will be stored. Must be pre-allocated and of the same size as inputArray.
 * - indexMapping[]: An array of integers defining how elements in inputArray should be reordered.
 *                   Each value in indexMapping corresponds to the position in outputArray
 *                   where the corresponding element from inputArray will be placed.
 * - size: The total number of elements in the arrays (must be the same for inputArray, outputArray, and indexMapping).
 *
 * Usage:
 * 1. Define your input array and an output array to store the reordered elements.
 * 2. Create an indexMapping array that specifies the new order of the elements.
 *    Example: If indexMapping = {2, 0, 1}, the first element of the output will be inputArray[2],
 *             the second will be inputArray[0], and the third will be inputArray[1].
 * 3. Call the function with the arrays and size.
 *
 * Example:
 *   const int size = 3;
 *   int inputArray[size] = {10, 20, 30};
 *   int outputArray[size];
 *   int indexMapping[size] = {2, 0, 1}; // Reorder to: inputArray[2], inputArray[0], inputArray[1]
 *   reorderArray(inputArray, outputArray, indexMapping, size);
 *   // Result: outputArray = {30, 10, 20}
 *
 * Notes:
 * - Ensure the indexMapping array contains valid indexes within the bounds of inputArray.
 * - The function does not modify the inputArray or indexMapping array.
 */

// Template function to reorder elements in an array based on index mapping
template <typename T>
void reorderArray(const T inputArray[], T outputArray[], const int indexMapping[], int size) {
  // Iterate through each element in the input array
  for (int i = 0; i < size; i++) {
    // Place the value from inputArray[i] into the position specified by indexMapping[i]
    outputArray[indexMapping[i]] = inputArray[i];
  }
}

void setup() {
  // Start Serial communication for debugging and displaying results
  Serial.begin(9600);

  // Define the size of the arrays
  const int size = 5;

  // Input array: The original order of values
  int inputArray[size] = {10, 20, 30, 40, 50};

  // Index mapping: Specifies how to reorder the input array
  // For example, indexMapping[0] = 4 means the first element of outputArray will be inputArray[4].
  int indexMapping[size] = {4, 2, 0, 3, 1}; // Reorder to 50, 30, 10, 40, 20

  // Output array: This will store the reordered elements
  int outputArray[size];

  // Call the reorderArray function to reorder inputArray based on indexMapping
  reorderArray(inputArray, outputArray, indexMapping, size);

  // Print the original array to the Serial Monitor
  Serial.println("Original Array:");
  for (int i = 0; i < size; i++) {
    Serial.print(inputArray[i]);
    Serial.print(" ");
  }
  Serial.println();

  // Print the reordered array to the Serial Monitor
  Serial.println("Reordered Array:");
  for (int i = 0; i < size; i++) {
    Serial.print(outputArray[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void loop() {
  // Nothing to do here, as the functionality is in the setup function
}
