#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> loadPatternsFromFile(const string& filename) {
    vector<string> patterns;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла шаблонов: " << filename << endl;
        return patterns;
    }
    string pattern;
    while (getline(file, pattern)) {
        patterns.push_back(pattern);
    }
    return patterns;
}

void grep(const vector<string>& patterns, const vector<string>& files, bool ignoreCase, bool invertMatch, bool countMatches, bool listFiles, bool showLineNumbers, bool suppressErrors, bool printFileName, bool onlyMatching) {
    for (const string& file : files) {
        ifstream inputFile(file);
        if (!inputFile.is_open()) {
            if (!suppressErrors) {
                cerr << "Не удалось открыть файл: " << file << endl;
            }
            continue;
        }

        string line;
        int matchCount = 0;
        int lineNumber = 0;

        while (getline(inputFile, line)) {
            ++lineNumber;
            string originalLine = line;

            if (ignoreCase) {
                transform(line.begin(), line.end(), line.begin(), ::tolower);
            }

            bool match = false;
            for (const string& pattern : patterns) {
                string searchPattern = pattern;
                if (ignoreCase) {
                    transform(searchPattern.begin(), searchPattern.end(), searchPattern.begin(), ::tolower);
                }
                if (line.find(searchPattern) != string::npos) {
                    match = true;
                    break;
                }
            }

            if (invertMatch) {
                match = !match;
            }

            if (match) {
                matchCount++;
                if (!countMatches && !listFiles) {
                    if (printFileName && files.size() > 1) {
                        cout << file << ":";
                    }
                    if (showLineNumbers) {
                        cout << lineNumber << ":";
                    }
                    if (onlyMatching) {
                        for (const string& pattern : patterns) {
                            string searchPattern = pattern;
                            if (ignoreCase) {
                                transform(searchPattern.begin(), searchPattern.end(), searchPattern.begin(), ::tolower);
                            }
                            size_t pos = line.find(searchPattern);
                            while (pos != string::npos) {
                                cout << line.substr(pos, pattern.length()) << " ";
                                pos = line.find(searchPattern, pos + 1);
                            }
                        }
                        cout << endl;
                    } else {
                        cout << originalLine << endl;
                    }
                }
            }
        }

        if (countMatches) {
            cout << file << ": " << matchCount << endl;
        }

        if (listFiles && matchCount > 0) {
            cout << file << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    vector<string> patterns;
    vector<string> files;
    bool ignoreCase = false;
    bool invertMatch = false;
    bool countMatches = false;
    bool listFiles = false;
    bool showLineNumbers = false;
    bool suppressErrors = false;
    bool printFileName = true;
    bool onlyMatching = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-e") {
            if (i + 1 < argc) {
                patterns.push_back(argv[++i]);
            } else {
                cerr << "Ошибка: опция -e требует шаблона." << endl;
                return 1;
            }
        } else if (arg == "-i") {
            ignoreCase = true;
        } else if (arg == "-v") {
            invertMatch = true;
        } else if (arg == "-c") {
            countMatches = true;
        } else if (arg == "-l") {
            listFiles = true;
        } else if (arg == "-n") {
            showLineNumbers = true;
        } else if (arg == "-h") {
            printFileName = false;
        } else if (arg == "-s") {
            suppressErrors = true;
        } else if (arg == "-o") {
            onlyMatching = true;
        } else if (arg == "-f") {
            if (i + 1 < argc) {
                vector<string> filePatterns = loadPatternsFromFile(argv[++i]);
                patterns.insert(patterns.end(), filePatterns.begin(), filePatterns.end());
            } else {
                cerr << "Ошибка: опция -f требует имени файла." << endl;
                return 1;
            }
        } else {
            files.push_back(arg);
        }
    }

    if (patterns.empty()) {
        cerr << "Ошибка: шаблон поиска не указан." << endl;
        return 1;
    }

    if (files.empty()) {
        cerr << "Ошибка: файлы для обработки не указаны." << endl;
        return 1;
    }

    grep(patterns, files, ignoreCase, invertMatch, countMatches, listFiles, showLineNumbers, suppressErrors, printFileName, onlyMatching);

    return 0;
}
