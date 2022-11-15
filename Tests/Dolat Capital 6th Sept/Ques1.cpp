#include "bits/stdc++.h"
using namespace std;

int numberOfBooks;
map<string, set<int>> bestPrices;
int temp = 0;

struct Book {
    char Product[5];
    int Price;
    int SeqNum;
};

Book* Load() {

    cin >> numberOfBooks;
    Book* books = new Book;

    for (int curr = 0, j = 0; curr < numberOfBooks; curr++, j = 0) {

        string currentLine;
        while (currentLine.empty()) {
            getline(cin, currentLine);
        }

        while (j < currentLine.size() && currentLine[j] != ',') {
            books[curr].Product[j] = currentLine[j];
            j += 1;
        }

        j += 1;

        while (j < currentLine.size() && currentLine[j] == ' ') {
            j += 1;
        }

        books[curr].Price = 0;
        bool isNegative = false;
        if (j < currentLine.size() && currentLine[j] == '-') {
            isNegative = true;
            j += 1;
        }

        temp = 0;
        while (j < currentLine.size() && currentLine[j] != ',') {
            temp = temp * 10 + (currentLine[j++] - '0');
        }
        books[curr].Price = temp;

        if (isNegative) {
            books[curr].Price = -books[curr].Price;
        }

        j += 1;

        while (j < currentLine.size() && currentLine[j] == ' ') {
            j += 1;
        }

        temp = 0;
        while (j < currentLine.size() && currentLine[j] != ',') {
            temp = temp * 10 + (currentLine[j++] - '0');
        }
        books[curr].SeqNum = temp;
    }

    return books;
}


void Process(const Book* newBook) {

    string output;

    bestPrices[newBook->Product].emplace(newBook->Price);

    auto previous = prev(bestPrices[newBook->Product].end());
    if (bestPrices[newBook->Product].size() > 5) {
        bestPrices[newBook->Product].erase(previous);
    }

    cout << newBook->Product << " || ";

    int count = 0;
    for (auto &it : bestPrices[newBook->Product]) {
        cout << it;
        if (count < 4) {
            cout << ", ";
        }
        else {
            cout << " ";
        }
        count += 1;
    }

    while (count < 5) {
        cout << 0;
        if (count < 4) {
            cout << ", ";
        }
        else {
            cout << " ";
        }
        count += 1;
    }

    cout << "||\n";
}


void solve() {
    Book* books = Load();
    for (int i = 0; i < numberOfBooks; i++) {
        Process(&books[i]);
    }
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        solve();
    }

    return 0;
}