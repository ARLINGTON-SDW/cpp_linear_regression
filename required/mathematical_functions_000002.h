/*
	C++ Required Mathematical Functions for Calculating Multiple Linear Regression
	from Vectors.
	
	Author:		
				James Kent
	Website:	
				https://www.jkent.blog
	Date:		
				2021-08-15
	
	Functions:
		mean:						
									Returns the mean (average) value of a vector as a float
		sum:						
									Returns the sum of all values in a vector as a float
		multiply_vector_by_float: 	
									Loops through vector, multiplying each individual float within vector
									by the specified float value, returning new values as vector
		multiply_vector_by_array:	
									Loops through vector, multiplying each float within vector by
									float in corresponding location with the other vector, returns new
									values as vector
		sum_vectors:				
									Loops through vector, adding float in first vector to corresponding value
									in second vector, returns new values as vector
		power:						
									Loops through vector, calculating each float in vector to the power of
									float value specified, returns new values as vector
		correlation_coefficient:	
									Identifies the correlation co-efficient of two vectors, returning co-efficient
									as a float, inspiration for this function came from here:
									https://www.geeksforgeeks.org/program-find-correlation-coefficient/
		add_float_to_vector:
									Loops through vector and adds specified float value to each float value
									in vector, returns new vector containing new values
		add_vector_to_vector:		
									Loops through two vectors, adding together the float values in each at
									the current point in the loop, returns new values as a vector

*/

#include <iostream>
#include <vector>
#include <iterator>
#include <math.h>
using std::vector;


float mean(vector<float> &arr){
	// Function to calculate the mean value of a vector

	float total = 0;
	auto size = arr.size();
	for(int i=0; i < size; i++){
		total = total + arr[i];
	}
	float mean_value = total /size;
	return mean_value;	
}

float sum(vector<float> &arr){
	// Function to sum all values in vector
	
	float total = 0;
	auto size = arr.size();
	for(int i=0; i < size; i++){
		total = total + arr[i];
	}
	return total;	
}

vector<float> multiply_vector_by_float(vector<float> &arr, float f){
	// Function to multiply all floats in vector by
	// specified float value
	
    vector<float> mult;
    mult.reserve(arr.size());
    for (const auto &i : arr) {
        mult.push_back(i * f);
    }
    return mult;
}

vector<float> multiply_vector_by_vector(vector<float> &arr, vector<float> &arr2){
	// Function to multiply each float in vector
	// by float in corresponding position in second vector
	
    vector<float> mult;
    mult.reserve(arr.size());
    for(int i=0; i < arr.size(); i++){
        mult.push_back(arr[i] * arr2[i]);
    }
    return mult;
}
vector<float> sum_vectors(vector<float> &arr, vector<float> &arr2){
	// Function to add each float in vector
	// to float in corresponding position in second vector
	
    vector<float> mult;
    mult.reserve(arr.size());
    for(int i=0; i < arr.size(); i++){
        mult.push_back(arr[i] + arr2[i]);
    }
    return mult;
}

vector<float> power(vector<float> &arr, float y){
	// Function to calculate each float in vector
	// to a specified power.
	
    vector<float> mult;
    mult.reserve(arr.size());
    for(int i=0; i < arr.size(); i++){
        mult.push_back(pow(arr[i], y));
    }
    return mult;
}

float correlation_coefficient(vector<float> &x, vector<float> &y){
	// Function to calculate correlation between
	// two vectors.
	
	vector<float> summed_sx = multiply_vector_by_vector(x, y);
	float sum_x = sum(x);
	float sum_y = sum(y);
	int n = x.size();
	float sum_xy= sum(summed_sx);
	vector<float> square_x = power(x, 2);
	vector<float> square_y = power(y, 2);
	float square_sum_x = sum(square_x);
	float square_sum_y = sum(square_y);
	float corr = (float)(n * sum_xy - sum_x * sum_y)
				/ sqrt((n * square_sum_x - sum_x * sum_x)
					* (n * square_sum_y - sum_y * sum_y));
	return corr;
}
vector <float> add_float_to_vector(vector<float> arr, float y){

	// Function to add float to each float in vector
	vector<float> mult;
    mult.reserve(arr.size());
    for(int i=0; i < arr.size(); i++){
        mult.push_back(arr[i] + y);
    }
    return mult;
}
vector <float> add_vector_to_vector(vector<float> arr, vector<float> arr1){
	// Function to loop through two vectors, adding together the 
	// float values at each point
	
	vector<float> mult;
    mult.reserve(arr.size());
    for(int i=0; i < arr.size(); i++){
        mult.push_back(arr[i] + arr1[i]);
    }
    return mult;

}
