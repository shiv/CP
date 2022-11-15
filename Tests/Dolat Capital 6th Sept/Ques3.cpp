#include<bits/stdc++.h>
#define int int64_t
using namespace std;

struct Book {
    char Product[5];
    int Price;
    int SeqNum;
};

bool comp(Book* a, Book* b) {
    return a->Price > b->Price;
}

struct Cmp{
    bool operator()(Book a,Book b){
        return a.Price < b.Price;
    }
};

set<Book, Cmp> s;

Book* Load() {
    struct Book* newBook = new Book;
    string s;
    cin>>s;
    string x = s.substr(0, s.size()-1);
    strcpy(newBook->Product, &(*x.begin()));
    cin>>s;
    x = s.substr(0, s.size()-1);
    newBook->Price = stoi(x);
    cin>>s;
    newBook->SeqNum = stoi(s);
    return newBook;
}

void Process(const Book* newBook) {
    s.insert(*newBook);
    int cnt = 0;
    auto itr = s.begin();
    while(itr != s.end() && cnt < 5) {
        cout << itr->Price << (cnt == 4 ? " " : ", ");
        itr++;
        cnt++;
    }
    while(cnt < 5) {
        cout << 0 << (cnt == 4 ? " " : ", ");
        cnt++;
    }
    cout << "||" << endl;
}

signed main()
{
    while(true) {
        struct Book* newBook = Load();
        cout << newBook->SeqNum << ": " << newBook->Product << " || ";
        Process(newBook);
    }
    return 0;
}
