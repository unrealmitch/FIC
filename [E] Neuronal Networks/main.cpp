#include "McCullocha.h"
#include "Perceptron.h"
#include "Association.h"
#include "Gradient.h"
#include "iostream"
using namespace std;

int main() {

	short int choose = 0;

	while (choose != 'q'){
		
		cout << "" << endl;
		cout << "Choose one task:" << endl;
		cout << "(1) Model McCullocha-Pittsa" << endl;
		cout << "(2) Perceptron" << endl;
		cout << "(3) Model association" << endl;
		cout << "(4) Gradient method" << endl;
		cout << "Choose one task [number]:" << endl;
		cin >> choose;

		switch (choose){
		case 1:
			T1();
			break;
		case 2:
			T2();
			break;
		case 3:
			T3();
			break;
		case 4:
			T4();
			break;
		default:
			cout << "Bad Argument" << endl;
			break;
		}
	}
	
    return 0;
}