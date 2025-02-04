#include <bits/stdc++.h>
#define ll long long

using namespace std;

int B, L, D;

class Book{
public:
    int ID;
    ll score;
    bool operator < (Book B){
        return B.score < this->score;
    }
};

class Library{
public:
    int ID;
    int num_book;
    int signup;
    int scan_per_day;
    vector<Book>books;
    bool operator < (Library L){
        double sm = 0, sm1 = 0;
        ll cnt = 0;
        for(int i=0;i<min(L.books.size(),this->books.size());i++){
            sm += L.books[i].score;
        }

        for(int i=0;min(L.books.size(),this->books.size());i++){
            sm1 += this->books[i].score;
        }

        return sm/L.signup*L.scan_per_day < sm1/this->signup*this->scan_per_day;
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
    int pos = 0, d = 0;

    for(int i=0;i<libraries.size();i++){
        ans.push_back(libraries[i]);
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