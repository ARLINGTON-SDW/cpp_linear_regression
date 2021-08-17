/*
	C++ Multiply Linear Regression Driver File.
	
	Author:		
				James Kent
	Website:	
				https://www.jkent.blog
	Date:		
				2021-08-15

	Comments:	
				Following the advice contained within Ervin Varga's book "Practical Data Science with Python 3",
				Chapter 4 - "Documenting your work", I'm providing a full abstract to this project; please feel
				free to skip to line 70 if you're not interested in reading my rambling.

	Abstract:
				The below code provides second version of the first function in a C++ based machine learning 
				library I'm building with the working title of CLAMP (C++ Language Applied Machine Learning Protocol). This function
				allows for multiple linear regression with two predictor features and a target. This module can
				be imported as a header, and the function called as below:
				
							vector <float> y_pred = linear_regression(predictors, target);
							
				With predictors being a vector of vectors, and target being a vector in isolation, this function
				returns the predicted values as calculated.
				
	Motivation:
				In running forward selection testing of a large dataset in Python, I found the performance to
				be extremely sluggish; given that I'm aware C++ is rumoured to be anywhere up to 500x faster 
				than Python, it seemed obvious that the answer was to being building some of these 
				algorithms in C++, with the intention of providing a Python binding (probably using PyBind11)
				at a later date.
	
	Datasets:
				This code currently doesn't make use of any datasets, see "Future Work" for further details.
	 
	Life Cycle
	Phases:		
				Despite being version 0.000002, this is actually the third iteration of this particular module,
				the first iteration was a simple (i.e. single feature) linear regression calculation that
				provided the idea to continue building out the code, the second iteration was array based, and
				required a lot of manual change to run different queries; this version is much more succinct,
				and does not require a user to change any code, outside of the function call itself.
	
	Drawbacks:
				The code can currently only handle two predictor features; a major limitation for larger
				models.
				
	Conclusion:
				This is quite a nice first module for the CLAMP library, and has been tested on smaller datasets
				and found to be give the correct values by way of response, obviously more work needs to be done,
				as noted below, but all in all a good start.
	
	Future 
	Work:		
				Allowing for calculation based on more than 2 features. In a separate, but vital piece of C++
				development, I am looking at developing easier ways of retrieving, preprocessing and then 
				using this library for calculation; I've looked around online and it seems C++ does not handle
				parsing CSV data into manageable frames very well - that suggests there is room for a new
				module that can improve this. Additionally I would like to build easier to use (API-style)
				support for MySQL and HDF5, before continuing to add new methods of prediction.
				Currently there is no try/catch mechanism built in to this module - I'm particularly interested
				in excluding blanks, infinite values and text values from the data, and ensuring that all
				feature and target vectors are of the same length. Additionally, I'm planning to turn these
				predictors into classes, in a similar style to many Python modules to allow reuse of the 
				trained model.

*/

#include <math.h>
#include <vector>
#include "../../required/mathematical_functions_000002.h"
using namespace std;

vector<float> linear_regression(vector<vector<float> >x, vector<float> y){

	// Number of features
	int n = x.size();
	
	// Size of features
	int q = x[0].size();
	
	// Sum of all values in y array
	float y_sigma = sum(y);
	
	// Empty array to hold sum of all x feature columns
	float x_sigmas[n];
	
	// Empty array to gold sum of all x * y values
	float x_y_sigmas[n];
	for(int i=0; i < n; i++){
	
		// Sum each predictor feature
		x_sigmas[i] = sum(x[i]);
		
		// Multiply each x feature column by y and pass to 
		// x_y_sigmas array
		vector<float> temp_ = multiply_vector_by_vector(x[i], y);
		x_y_sigmas[i] = sum(temp_);
	}
	// Multiply first and second columns together
	vector <float> x1_x2_sigmas_temp = multiply_vector_by_vector(x[0], x[1]);
	
	// Sum multiplied x1 and x2 column
	float x1_x2_sigma = sum(x1_x2_sigmas_temp);	
	
	// Square x1_2 column values
	vector<float> x1_2 = power(x[0], 2);
	
	// Sum squared x1 column
	float x1_2_sigma = sum(x1_2);
	
	// Square x2 column values
	vector <float> x2_2 = power(x[1], 2);
	
	// Sum squared x2 column
	float x2_2_sigma = sum(x2_2);
	
	// Deduct squared x1 column summed value from
	// squared x1 squared element squared summed value
	// and divide by length of x	
	float a = x1_2_sigma - pow(x_sigmas[0],2) / q;
	
	// Deduct squared x2 column summed value from
	// squared x2 squared element squared summed value
	// and divide by length of x	
	float b = x2_2_sigma - pow(x_sigmas[1],2) / q;
	
	// Deduct summed x1 value multiplied by sum of y from
	// sum of x1 * y and divide result by length of x
	float c = x_y_sigmas[0] - (x_sigmas[0] * y_sigma) / q;	

	// Deduct summed x2 value multiplied by sum of y from
	// sum of x2 * y and divide result by length of x
	float d = x_y_sigmas[1] - (x_sigmas[1] * y_sigma) / q;
	
	// Sum of x1 * sum of x2, deducted from sigma of x1 * x2
	float e = x1_x2_sigma - x_sigmas[0] * x_sigmas[1] / q;
	
	// Calculation based on previous 5 variables
	float b1 = (b * c- e * d) / (a * b - pow(e,2));
	
	// As above
	float b2 = (a * d - e * c) / (a * b - pow(e,2));
	
	// Mean of column y
	float y_mean = mean(y);
	
	// Calculate slope
	float b0 = y_mean - b1 * mean(x[0]) - b2 * mean(x[1]);
	
	// Multiply x1 by b1
	vector<float> x1_b1 = multiply_vector_by_float(x[0], b1); 
	
	// Multiply x1_b1 by b0
	vector<float> x1_b1_b0 = add_float_to_vector(x1_b1, b0);
	
	// Multiply x2 by b0
	vector<float> x2_b2 = multiply_vector_by_float(x[1], b2);
	
	// Multiply x1_b1_b0 by x2_b2
	vector <float> y_hat = add_vector_to_vector(x1_b1_b0, x2_b2);	
	
	// Return linear regression calculated values as vector
	return y_hat;
}
