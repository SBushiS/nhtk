#include <iostream>
#include <cmath> // для функции abs()
#include <algorithm> // для функции sort()

using namespace std;

int main() {
    const int N = 10;
    int arr[N];
    int R;

    cout << "Введите число R: ";
    cin >> R;
    cout << "Введите массив из 10 элементов: ";
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    int max_diff = 0;
    int elem1 = 0, elem2 = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            int diff = abs((arr[i] - arr[j]) - R);
            if (diff > max_diff) {
                max_diff = diff;
                elem1 = arr[i];
                elem2 = arr[j];
            }
        }
    }

    if (elem1 > elem2) {
        swap(elem1, elem2);
    }

    cout << "Два элемента, разность которых наиболее далека от " << R << ": " << elem1 << " и " << elem2 << endl;

    return 0;
}
