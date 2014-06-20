//
// Bucket.h
// Data Structures Homework #5
//
// Created by Andrea Borghi on 6/3/14.
// Copyright (c) 2014 Andrea Borghi. All rights reserved.
//

#include <iostream>

using namespace std;

const int BUCKET_SIZE = 4;

class Bucket {
private:
	Star * duplicateList[BUCKET_SIZE]; // To store the synonym keys
	int bucketKey; // To store the key of the bucket
	int numElements; // To store the amount of elements in the bucket
	bool full; // To store wether the bucket is full

public:
	// Constructor
	Bucket(int bucketK) : bucketKey(bucketK), numElements(0), full(false){
        for (int i = 0; i < BUCKET_SIZE; ++i) duplicateList[i] = NULL;
    };

	// Public methods
	bool insertValue(Star * value);
	bool eraseValue(Star * value);
	int size() { return BUCKET_SIZE; }
	bool isFull() { return full; }
	int getNumElements() const { return numElements; }
	int getBucketKey() const { return bucketKey; }
	bool containsValue(string& value, int& index);
	Star * getValueAtIndex(int i);
	void printBucketElements(ostream& os);
	void printBucketStructure(ostream& os);
};

/**~*~*
The insertValue function tries to insert the parameter
value in the bucket and returns wether the operation was
successful or not
*~**/
bool Bucket::insertValue(Star * value)
{
	// If the bucket is full, return false
	if (full) return false;

	// Loop to iterate through the bucket
	for (int i = 0; i < BUCKET_SIZE; ++i) {
		// If the current position of the bucket is not allocated,
		// store the paramenter value there
		if (duplicateList[i] == NULL) {
			duplicateList[i] = value;

			// Increase the number of elements
			++numElements;

			// If the number of current elements identical to the
			// bucket size, set the full flag to true
			if (numElements == BUCKET_SIZE) full = true;
			return true;
		}
	}

	return false;
}

/**~*~*
The eraseValue function tries to delete the parameter
value in the bucket and returns wether the operation was
successful or not
*~**/
bool Bucket::eraseValue(Star * value)
{
	// Loop to iterate through the bucket
	for (int i = 0; i < BUCKET_SIZE; ++i) {
		// If the element at current position of the bucket is
		// identical to the paramenter value, delete it
		if (duplicateList[i] == value) {
			duplicateList[i] = NULL;

			// Decrease the number of elements
			--numElements;

			// If the full flag was set to true, change it to false
			if (full) { full = false; }

			return true;
		}
	}

	return false;
}

/**~*~*
The containsValue function tries to find the parameter
value in the bucket through its string representation.
It returns wether the value was found or not and the position
in the list through the index reference parameter
*~**/
bool Bucket::containsValue(string& value, int& index)
{
	stringstream stream; // To store the string representation

	// Loop to iterate through the bucket
	for (int i = 0; i < BUCKET_SIZE; ++i) {
		// If the current element in the list is not allocated, break
		// the loop as there are not more elements left
		if (duplicateList[i] == NULL) break;

		// Convert the current value to its string representation
		stream << *duplicateList[i];
		string objectToString = stream.str();

		// If the string representation of the current object corresponds
		// to the string paramenter, set the index parameter to the current
		// index and return true
		if (objectToString == value) {
			index = i;

			return true;
		}
	}

	// If not found, set the index paramenter to -1;
	index = -1;

	return false;
}

/**~*~*
The getValueAtIndex function tries to retrieve the object
in the bucket stored at the position specified by the paramenter
and returns it if found, null if not found
*~**/
Star * Bucket::getValueAtIndex(int i)
{
	return duplicateList[i];
}

/**~*~*
The printBucketElements function prints the contents
in the bucket in an ordinate fashion to the
output stream
*~**/
void Bucket::printBucketElements(ostream& os)
{
    for (int i = 0; i < BUCKET_SIZE; ++i) {
		if (duplicateList[i] != NULL) os << "\t" << *duplicateList[i] << endl;
	}
}

/**~*~*
The printBucketStructure function prints the contents
in the bucket to the output stream highlighting
their position in the list, including elements which
are not allocated
*~**/
void Bucket::printBucketStructure(ostream& os)
{
	os << "Bucket key: " << bucketKey << ". Elements in bucket: " << endl;

	for (int i = 0; i < BUCKET_SIZE; ++i) {
		(duplicateList[i] != NULL) ? os << "\t" << i << ". " << *duplicateList[i] << endl : os << "\t" << i << ". [Empty slot]" << endl;
	}
}
