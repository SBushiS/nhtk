#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int n;
	float S, y, E;
	cin >> E;
	y = (1+5)/(2+2);
	S = y;
	n = 1;
	while (y > E) {
		n = n + 1;
		y = (n+5)/(pow(2, n)+2);
		S = S + y;
	}
	printf("%f", S);
	return 0;
}
