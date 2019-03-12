#include <iostream>
#include <Eigen/Dense>
#include <complex>
#include <list>
#include "../lib/matrice.h"

using namespace std;
using namespace Eigen;


int main() {

	MatrixXf m(2,2);
	m(0,0) = 3;
	m(1,0) = 2.5;
	m(0,1) = -1;
	m(1,1) = m(1,0) + m(0,1);
	///cout << m <<endl;

	Matrice *X = new Matrice(m, m.rows(), m.cols());
	//X->ACP();
	//X->printVal();


	return 0;
}
