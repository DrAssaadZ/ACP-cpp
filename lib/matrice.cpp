#include <iostream>
#include <Eigen/Dense>
#include <complex>
#include <list>
#include "matrice.h"

using namespace std;
using namespace Eigen;

Matrice::Matrice(MatrixXf m, int r, int c){

	Matrice::matrix.resize(r, c);
	Matrice::matrix= m;
}

void Matrice::printVal(){
	cout<< Matrice::matrix << endl;
}

//function that calculates the mean of a mat
VectorXf Matrice::calculateBar(MatrixXf mat){
	VectorXf vect(mat.cols());
	for (int i = 0; i < mat.cols(); i++){
		vect(i) = mat.col(i).mean();
	}
	return vect;
}

MatrixXf Matrice::center(){
	//calculating X-bar(Arithmetic mean)
	VectorXf xbar(matrix.cols());
	xbar = Matrice::calculateBar(matrix);

	cout << "x bar : \n" << xbar <<endl;

	//calculating the new centered mat
	MatrixXf centeredMat(matrix.rows(), matrix.cols());
	for (int i = 0; i < matrix.cols(); i++){
		for (int j = 0; j < matrix.rows(); j++){
			centeredMat(j,i) = matrix(j,i) - xbar(i);
		}
	}

	cout<< "centered mat : \n" << centeredMat <<endl;
	return centeredMat;
}

MatrixXf Matrice::reduce(MatrixXf centered){
	//calculating X-bar(Arithmetic mean)
		VectorXf centeredBar(centered.cols());
		centeredBar = Matrice::calculateBar(centered);

		cout << "centered bar :\m" << centeredBar << endl;

		//calculating the new centered mat
		MatrixXf yMat(centered.rows(), centered.cols());
		for (int i = 0; i < centered.cols(); i++){
			for (int j = 0; j < centered.rows(); j++){
				yMat(j,i) = pow(centered(j,i) - centeredBar(i),2);
			}
		}
		cout << "y mat \n" << yMat <<endl;

		VectorXf variance(centered.cols());
		variance = calculateBar(yMat);
		//calculating ecart-type
		for (int i = 0; i < centered.cols(); i++){
			variance(i) = sqrt(variance(i));
		}
		cout << "variance \n" << variance <<endl;

		MatrixXf zmat(centered.rows(), centered.cols());
				for (int i = 0; i < centered.cols(); i++){
					for (int j = 0; j < centered.rows(); j++){
						zmat(j,i) = centered(j,i) / variance(i);
					}
				}

	return zmat;
}

MatrixXf Matrice::ACP(float threshold, bool doReduce){
	return Matrice::reduce(Matrice::center());

}
