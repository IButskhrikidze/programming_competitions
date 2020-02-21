#include <bits/stdc++.h>
#define ll long long

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
    int start_scanning;
    int scan_per_day;
    vector<Book>books;

    bool operator < (Library L){
        return L.signup > this->signup;
    }
};

class Process{
public:
    Library library;
    Book book;
    int remaining_days;
};

vector<Book>books;
vector<Library>libraries;
vector<Library>ans;

void solve(){
    sort(libraries.begin(), libraries.end());

    int day = 0, i=0;

    set <Book> scanned_books;
    set <Book> ::iterator it;

    while(day < D && i < libraries.size()){
        Library lib = libraries[i];

        day += lib.signup;
        lib.start_scanning = day;

        int d = lib.start_scanning, j=lib.num_book-1;
        while(j>=0 && d<D){
            for(int k=0; k<lib.scan_per_day; k++){
                if(j<0){
                    break;
                }
                Book book = lib.books[j];
                if(scanned_books.find(book) != scanned_books.end()){
                    scanned_books.insert(book);
                }
                else{
                    lib.books.erase(lib.books.begin()+j);
                }
                j--;
            }
            d++;
        }

        if(lib.books.empty()){
            day -= lib.signup;
        }
        else{
            ans.push_back(lib);
        }
    }
}

int main(int argv, char **args){
    string input_file = args[1];
    string output_file = args[2];

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
        libraries[i].ID = i;
        for(int j=0;j<libraries[i].num_book;j++){
            int id;
            fin >> id;
            libraries[i].books.push_back(books[id]);
        }
        sort(libraries[i].books.begin(), libraries[i].books.end());
    }

    solve();


    fout << ans.size() << endl;

    for(auto library : ans){
        fout << library.ID << ' ' << library.books.size() << endl;
        for(auto book : library.books){
            fout << book.ID << ' ';
        }
        fout << endl;
    }

    return 0;
}
