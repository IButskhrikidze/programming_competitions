#include <bits/stdc++.h>
#defin ll long long

using namespace std;

int B, L, D;

class Book{
public:
    int ID;
    ll score;
    bool operator < (Book B){
        return B.score > this->score;
    }
};

class Library{
public:
    int ID;
    int num_book;
    int signup;
    int scan_per_day;
    vector<Book>books;
};

class Process{
public:
    Library library;
    Book book;
    int remaining_days;
};

vector<Book>books;
vector<Library>libraries;

int main(int argv, char **args){
    string input_file = argv[1];
    string output_file = argv[2];

    ifstream fin(input_file);
    ofstream fout(output_file);

    fin >> B >> L >> D;

    books.resize(B);

    for(int i=0;i<B;i++){
        fin >> books[i].score;
        books[i].ID = i;
    }

    libraries.resize(L);

    for(int i=0;i<L;i++){
        fin >> libraries[i].num_book >> libraries[i].signup >> libraries[i].scan_per_day;
        for(int j=0;j<libraries[i].num_book;j++){
            int id;
            fin >> id;
            libraries[i].books.push_back(books[id]);
        }
        sort(libraries[i].books.begin(), libraries[i].books.end());
    }



    return 0;
}
