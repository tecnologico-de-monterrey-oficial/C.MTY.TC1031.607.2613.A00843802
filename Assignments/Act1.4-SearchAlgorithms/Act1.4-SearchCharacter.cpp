//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
#include <string>
using namespace std;

//Búsqueda secuencial
char seqSearch(string text, int &comparisons) {

    comparisons = 0;

    for (int i = 0; i < text.size() - 1; i += 2) {

        comparisons++;

        if (text[i] != text[i + 1]) {
            return text[i];
        }
    }

    return text[text.size() - 1];
}


//Búsqueda binaria
char binarySearch(string text, int &comparisons) {

    comparisons = 0;

    int left = 0;
    int right = text.size() - 1;

    while (left < right) {

        int mid = (left + right) / 2;

        comparisons++;

        //Si mid es par
        if (mid % 2 == 0) {

            if (text[mid] != text[mid + 1]) {
                return text[mid];
            } else {
                left = mid + 1;
            }

        //Si mid es impar
        } else {

            if (text[mid] == text[mid - 1]) {
                left = mid + 1;
            } else {
                return text[mid];
            }
        }
    }

    return text[left];
}


int main() {

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {

        string text;
        cin >> text;

        int seqComparisons;
        int binComparisons;

        char seqCharacter = seqSearch(text, seqComparisons);
        char binCharacter = binarySearch(text, binComparisons);

        cout << seqCharacter << " "
             << seqComparisons << " "
             << binCharacter << " "
             << binComparisons << endl;
    }

    return 0;
}