#include <math.h>
#include <iostream>
#include <numeric>
#include "../../models/linear_regression/multiple_linear_regression_000002.h"
using namespace std;

void printvf(vector <float> float_value){
	// Function to print out vector
	for(int i=0;i<float_value.size(); i++){
		cout << float_value[i] << endl;
	}
}

int main(){
	// Create predictor vectors
	// Predictor vector 1
	vector<float> x1 = {1,2,3,4,5};
	// Predictor vector 2
	vector<float> x2 = {3,6,7,15,12};
	
	// Combined vectors into vector of vectors
	vector<vector<float>> predictors = {x1,x2}; 	
    
    // Create vector of target values                     
    vector <float> target = {2,5,8,7,10};
    
    // Calculate linear regression
    vector <float> y_pred = linear_regression(predictors, target);
   	
   	// Print values
   	printvf(y_pred);
   	
}
