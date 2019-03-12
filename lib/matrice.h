#ifndef LIB_MATRICE_H_
#define LIB_MATRICE_H_
#endif /* LIB_MATRICE_H_ */

#include <iostream>
#include <Eigen/Dense>
#include <complex>
#include <list>

using namespace std;
using namespace Eigen;

typedef struct eigens{
	  float lambdaVal;
	  VectorXf vectVal;
  } Eigens;

class Matrice{
	//attributes
	MatrixXf matrix;
	MatrixXf matrixACP;
	//int rows, columns;

public:
	//methods
	Matrice(MatrixXf m, int r, int c);
	void printVal();
	/*0*/VectorXf calculateBar(MatrixXf mat); // funciton that calculate the bar(mean)
	/*1*/MatrixXf center(); //calculate X-bar / X-X-bar
	/*2*/MatrixXf reduce(MatrixXf centred); //calculate centred-bar / calculate Variance of centred (vector) / calculate ecart-typ (vector) / centred / ecart type
	/*3*/list<Eigens> eigenCalculator(MatrixXf reduced); //X^t.X/ eigenval/vect / create list / sort list
	/*4*/MatrixXf calculateACP(list<Eigens> list, float threshold); //matrice*(concatination des vecteurs propres)
	MatrixXf ACP(float threshold, bool doReduce); //call all the previous 4 functions
};
