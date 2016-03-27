#include <iostream>

using namespace std;

double power(double base, int degree){
	// termination condition of recursion
	if (degree > 0){
		degree--;
		return base * power(base, degree);
	}
	else return 1.0;
	// return degree > 0 ? base * power(base, --degree) : 1.0
}

int gcd(unsigned a, unsigned b){
	return b ? gcd(b, a % b) : a;
}

unsigned fibonacci(unsigned number){
	if (number >= 2) return fibonacci(number - 2) + fibonacci(number - 1);
	else return 1;
	//return number >= 2 ? fibonacci(number - 2) + fibonacci(number - 1) : 1;
}

void Hanoi(int disks, unsigned & counter, char A, char B, char C){
	if (disks == 0) return;
	Hanoi(disks - 1, counter, A, C, B);
	cout << counter + 1 << ". " << A << "->" << B << endl;
	counter++;
	Hanoi(disks - 1, counter, C, B, A);
}


int main(){
		
	/*cout << power(2,3) << endl;
	cout << power(2,0) << endl;
	cout << power(2,10) << endl;*/

	cout << gcd(100,0) << endl;

	for (int i = 0; i < 5; i++) cout << "Fibonacci number " << i << " = " << fibonacci(i) << endl;


	unsigned counter = 0;
	cout << "True way for Hanoi tower of 3 disks:" << endl;
	Hanoi(3, counter);
	cout << "moves = " << counter << endl;
	counter = 0;
	cout << "True way for Hanoi tower of 4 disks:" << endl;
	Hanoi(4, counter);
	cout << "moves = " << counter << endl;
	counter = 0;
	cout << "True way for Hanoi tower of 5 disks:" << endl;
	Hanoi(5, counter);
	cout << "moves = " << counter << endl;

	system("pause");

	return 0;
}
