#include <iostream>
#include <Eigen/Dense>
#include <complex>
#include <list>
#include "../lib/matrice.h"

using namespace std;
using namespace Eigen;


int main() {

	MatrixXf m(5,5);
	m << 5,4,3,150,4,
		 2,4,7,120,0,
		 1,0,9,88,2,
		 5,5,2,33,4,
		 5,6,7,97,1;

	/*m << 1,1,1,1,1,
	     2,2,2,2,2,
		 3,3,3,3,3,
		 4,4,4,4,4,
		 5,5,5,5,5;*/

	Matrice *X = new Matrice(m, m.rows(), m.cols());
	X->printVal();
	cout << endl << "Final Result: \n" << X->ACP(0.8, true);


	return 0;
}
