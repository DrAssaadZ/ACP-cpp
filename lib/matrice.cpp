#include <iostream>
#include <Eigen/Dense>
#include <complex>
#include <list>
#include "matrice.h"

using namespace std;
using namespace Eigen;


//Constractor
Matrice::Matrice(MatrixXf m, int r, int c){
	Matrice::matrix.resize(r, c);
	Matrice::matrix= m;
}


//function used to campare eigenvalues, return of this function is used to sort the list of Eigens
bool mycompare(const Eigens& a, const Eigens& b)
      {
      	return a.lambdaVal > b.lambdaVal;
      }


void Matrice::printVal(){
	cout<< Matrice::matrix << endl;
}


//calculate Arithmitic Mean -> vector
VectorXf Matrice::calculateAMean(MatrixXf mat){
	VectorXf vect(mat.cols());
	for (int i = 0; i < mat.cols(); i++){
		vect(i) = mat.col(i).mean();
	}
	return vect;
}

//center the point's cloud
MatrixXf Matrice::center(){
	//calculating X-bar(Arithmetic mean)
	VectorXf xbar(matrix.cols());
	xbar = Matrice::calculateAMean(matrix);


	//calculating the new centered matrix
	MatrixXf centeredMat(matrix.rows(), matrix.cols());
	for (int i = 0; i < matrix.cols(); i++){
		for (int j = 0; j < matrix.rows(); j++){
			centeredMat(j,i) = matrix(j,i) - xbar(i);
		}
	}

	cout<< endl << "Centered matrix : \n" << centeredMat <<endl;
	return centeredMat;
}


//Reduce the matrix(oprional)
MatrixXf Matrice::reduce(MatrixXf centered){
	//calculating (Arithmetic mean) of the centred matrix
		VectorXf centeredAMean(centered.cols());
		centeredAMean = Matrice::calculateAMean(centered);

		//calculating temporary values of the matrix for the variance
		MatrixXf tempVarianceMat(centered.rows(), centered.cols());
		for (int i = 0; i < centered.cols(); i++){
			for (int j = 0; j < centered.rows(); j++){
				tempVarianceMat(j,i) = pow(centered(j,i) - centeredAMean(i),2);
			}
		}

        //variance
		VectorXf variance(centered.cols());
		variance = calculateAMean(tempVarianceMat);

		//calculating Standard diviation (ecart-type)
		for (int i = 0; i < centered.cols(); i++){
			variance(i) = sqrt(variance(i));
		}


		MatrixXf reduced(centered.rows(), centered.cols());
				for (int i = 0; i < centered.cols(); i++){
					for (int j = 0; j < centered.rows(); j++){
						reduced(j,i) = centered(j,i) / variance(i);
					}
				}


		cout << endl << "Cebtred/Reduced Matrix\n" << reduced <<endl;

	return reduced;
}


//calculate eigen vactors associated with eigen values along with the inertie
list<Eigens> Matrice::eigenCalculator(MatrixXf reduced){
	//calculating Z^t.Z
	MatrixXf zMat = reduced.transpose()*reduced;

	cout<< endl << "X^t.X Matrix: \n" << zMat <<endl;
	cout << endl;

	//defining the solver
	EigenSolver<MatrixXf> eigensolver(zMat);

	//getting only the real part from the eigen vectors and values
	MatrixXf eigenVect = eigensolver.eigenvectors().real();
	VectorXf eigenVals = eigensolver.eigenvalues().real();

	//normalize eigen values
	for (int i; i < eigenVals.size(); i++){
		eigenVals(i) = (int)(eigenVals(i)*1000.0)/1000.0;
	}


	//constructing the list
	//sum of all inerties
	float inertieSum = eigenVals.sum();
	list<Eigens> data;
	for (int i=0; i < eigenVect.cols() ; i++){
	  	Eigens eigobj;
	  	eigobj.lambdaVal = eigenVals(i);
	  	eigobj.inertie = eigenVals(i)/inertieSum;
	  	VectorXf tempVect(eigenVect.rows());
	  	for (int j=0;j < eigenVect.rows(); j++){
	  		tempVect(j) = eigenVect(eigenVect.rows()*i+j);
	  	}
	  	eigobj.vectVal = tempVect;
	  	data.push_back(eigobj);
	}

	//sorting the list
	data.sort(mycompare);

	//iterator to iterate through the list
	list<Eigens>::iterator it;

	//printing the list items
	for (it = data.begin(); it != data.end(); it++){
	       std::cout << "EigenValue: " << it->lambdaVal << "\n EigenVector : \n" << it->vectVal << endl;
	}

	return data;
}


//Calculate the result
MatrixXf Matrice::calculateACP(list<Eigens> sortedList, float threshold){
	//Initializing the matrix which conatains the chosen eigenvectors
	MatrixXf PrincipaleComponents (matrix.rows(),0);

	//initial inertie of the plan
	float inertieSum = 0.0;

	list<Eigens>::iterator it;
	for (it = sortedList.begin(); it != sortedList.end(); it++){
	       if(inertieSum>=threshold) {
	    	   break;
	       }

	       inertieSum += it->inertie;

	       //concatinating the EigenVectors
	       PrincipaleComponents.conservativeResize(PrincipaleComponents.rows(), PrincipaleComponents.cols()+1);
	       PrincipaleComponents.col(PrincipaleComponents.cols()-1) = it->vectVal;
	   }

	//Final Matrix
	MatrixXf ACP_result = Matrice::matrix * PrincipaleComponents;

	return ACP_result;
}


//All the process
MatrixXf Matrice::ACP(float threshold, bool doReduce){
	if (doReduce) return calculateACP(eigenCalculator(Matrice::reduce(Matrice::center())), threshold);
	else return calculateACP(eigenCalculator(Matrice::center()), threshold);

}
