#include <iostream>
#include <cmath>

using namespace std;

int main() {
	float a, b, F;
	cout << "Write a\n";
	cin >> a;
	cout << "Write b\n";
	cin >> b;
	F = (8,15*pow(b, 1/3)*log(a))/(24,38*cos(b)*(exp(a)-pow(a,a)));
	cout << F;
	return 0;
}
