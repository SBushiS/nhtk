#include <iostream>
#include <cmath>

using namespace std;

int main() {
	float X, Y;
	scanf("%f", &X);
	scanf("%f", &Y);
	if (((X*X + Y*Y) <= 4) && ((X*X + Y*Y) >= 1)) {
		printf("Yes");
	}
	else {
		printf("No");
	}
	return 0;
}
