#include <iostream>
#include <fstream>
using namespace std;

int countDivisors(int number) {
    int count = 0;
    for (int i = 1; i <= number; ++i) {
        if (number % i == 0) {
            ++count;
        }
    }
    return count;
}

bool isPrime(int number) {
    if (number <= 1) {
        return false;
    }
    for (int i = 2; i * i <= number; ++i) {
        if (number % i != 0) {
            return true;
        }
    }
    return false;
}

int main() {
    ofstream outFile("result.txt");
    if (!outFile) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return 1;
    }

    int number;
    int totalPrimes = 0;

    cout << "Введите последовательность целых чисел (0 - конец): " << endl;

    while (true) {
        cin >> number;
        if (number == 0) {
            break;
        }

        int divisors = countDivisors(number);
        outFile << "Число: " << number << ", Количество делителей: " << divisors << endl;

        if (isPrime(number)) {
            ++totalPrimes;
        }
    }

    outFile << "Общее количество простых чисел: " << totalPrimes << endl;

    outFile.close();
    cout << "Результаты записаны в файл result.txt" << endl;

    return 0;
}
