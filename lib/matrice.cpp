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

MatrixXf Matrice::center(){
	//calculating X-bar(Arithmetic mean)

}

