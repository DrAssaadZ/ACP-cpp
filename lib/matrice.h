#ifndef LIB_MATRICE_H_
#define LIB_MATRICE_H_
#endif /* LIB_MATRICE_H_ */

#include <iostream>
#include <Eigen/Dense>
#include <complex>
#include <list>

using namespace std;
using namespace Eigen;

//Structure to save and sort eigenVectors and eigenValues by inertie
typedef struct eigens{
	  float lambdaVal;
	  float inertie;
	  VectorXf vectVal;
  } Eigens;

class Matrice{

	//attributes
	MatrixXf matrix;   //Matrix used to store the data


public:
	//methods
	Matrice(MatrixXf m, int r, int c); //constructor
	void printVal(); //print the contetnt of the matrix
	/*0*/VectorXf calculateAMean(MatrixXf mat); // Calculate Arithmetic Mean -> Vector
	/*1*/MatrixXf center(); //Center the point's cloud
	/*2*/MatrixXf reduce(MatrixXf centred); //Reduction of the centred values, calculated using Standard diviation (ecart-type)
	/*3*/list<Eigens> eigenCalculator(MatrixXf reduced); // calculating the eigen vectore associated with the eigen value of Matrix X^t.X
	/*4*/MatrixXf calculateACP(list<Eigens> list, float threshold); //Calculate the final Matrix
	MatrixXf ACP(float threshold, bool doReduce); //call all the previous 4 functions [1->4]
};
