#include <iostream>
#include <fstream>
using namespace std;

int main() {
    int p;

    cout << "Введите размер массива p: ";
    cin >> p;

    int* X = new int[p];

    cout << "Введите элементы массива X: ";
    for (int i = 0; i < p; ++i) {
        cin >> X[i];
    }

    int* Y = new int[p];
    int left = 0;
    int right = p - 1;
    int index = 0;

    while (left <= right) {
        if (index % 2 == 0) {
            Y[index] = X[left];
            left++;
        } else {
            Y[index] = X[right];
            right--;
        }
        index++;
    }

    ofstream outFile("output.txt");
    if (!outFile) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        delete[] X;
        delete[] Y;
        return 1;
    }

    for (int i = 0; i < p; ++i) {
        outFile << Y[i] << " ";
    }

    outFile.close();
    cout << "Массив Y записан в файл output.txt" << endl;

    // Освобождение памяти
    delete[] X;
    delete[] Y;

    return 0;
}
