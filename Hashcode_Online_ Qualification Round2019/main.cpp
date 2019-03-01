#include <bits/stdc++.h>

using namespace std;

int n, k;
map<string, int> Hash;

//Image data
struct Image {
    int id, pair_id;
    string orientation;
    set<int> tags;
};

//print Image data
ostream &operator<<(ostream &os, const Image &img) {
    os << img.id << endl << img.orientation << endl;
    for (int x : img.tags) {
        os << x << ' ';
    }
    os << endl;
    return os;
}

//size of Difference two sets(|a/b|)
int Difference(set<int> a, set<int> b) {
    for (auto x : b) {
        a.erase(x);
    }
    return int(a.size());
}

//size of intersection two sets(|a/b|)
int Intersection(set<int> a, set<int> b) {
    int ans = 0;
    for (auto x : b) {
        ans += a.count(x);
    }
    return ans;
}

//beauty of two images
int Beauty(Image A, Image B) {
    set<int> a = A.tags, b = B.tags;
    set<int>::iterator it;

    int diff1 = Difference(a, b), diff2 = Difference(b, a), inter = Intersection(a, b);

    return min(min(diff1, diff2), inter);
}

//count total beauty of slide show
int Count(vector<Image> slides) {
    int ans = 0;
    for (int i = 1; i < slides.size(); i++) {
        Image L = slides[i - 1], R = slides[i];
        ans += Beauty(L, R);
    }
    return ans;
}

//input data from file
void Get_data(ifstream &fin, vector<Image> &V_img, vector<Image> &H_img) {
    fin >> n;
    for (int i = 0; i < n; i++) {
        Image img;
        string orientation, tag;
        int cnt;
        fin >> orientation >> cnt;
        img.id = img.pair_id = i;
        img.orientation = orientation;
        for (int j = 1; j <= cnt; j++) {
            fin >> tag;
            if (!Hash.count(tag)) {
                Hash[tag] = ++k;
            }
            img.tags.insert(Hash[tag]);
        }
        if (orientation == "V") {
            V_img.push_back(img);
        } else {
            H_img.push_back(img);
        }
    }
}

//write answer in the file
void Output_data(ostream &fout, vector<Image> &ans) {
    fout << ans.size() << endl;
    for (Image img : ans) {
        if (img.orientation == "H") {
            fout << img.id << endl;
        } else {
            fout << img.id << ' ' << img.pair_id << endl;
        }
    }
}

//merge two vertical images to one horizontal
Image Union_verticals_to_horizontal(Image A, Image B) {
    Image ret;
    ret.id = A.id;
    ret.pair_id = B.id;
    ret.orientation = "V";
    for (int x : A.tags) {
        ret.tags.insert(x);
    }

    for (int x : B.tags) {
        ret.tags.insert(x);
    }

    return ret;
}

//convert vertical images to hoizontal images using pairing
void Verticals_random_pairing(vector<Image> &V_img, vector<Image> &H_img) {
    srand(time(0));
    if (V_img.size() < 2) {
        return;
    }
    random_shuffle(V_img.begin(), V_img.end());
    for (int i = 0; i < V_img.size() - 1; i += 2) {
        H_img.push_back(Union_verticals_to_horizontal(V_img[i], V_img[i + 1]));
    }
}

//convert vertical images to hoizontal images using pairing
void Verticals_pairing(vector<Image> &V_img, vector<Image> &H_img) {
    if (V_img.size() < 2) {
        return;
    }

    vector<bool> used(int(V_img.size()), 0);

    for (int i = 0; i < V_img.size(); i++) {
        if (used[i] == 1) {
            continue;
        }
        used[i] = 1;
        int mx = -1, ind = -1;
        for (int j = 0; j < V_img.size(); j++) {
            if (used[j] == 1) {
                continue;
            }
            int inter = Intersection(V_img[i].tags, V_img[j].tags);
            if (inter > mx) {
                mx = inter;
                ind = j;
            }
        }
        used[ind] = 1;
        H_img.push_back(Union_verticals_to_horizontal(V_img[i], V_img[ind]));
    }
}

//insert image in slide on the best position
int Insert(Image im, vector<Image> &V) {
    int mx = Beauty(im, V[0]), p = 0;
    for (int i = 1; i < V.size() - 1; i++) {
        if (mx < Beauty(im, V[i]) + Beauty(im, V[i - 1]))
            mx = Beauty(im, V[i]) + Beauty(im, V[i - 1]),
                    p = i;
    }
    if (mx < Beauty(im, V[V.size() - 1])) {
        p = V.size();
    }

    if (mx >= 0) {
        V.insert(V.begin() + p, im);
    }
    return mx;
}

vector<Image> Solve(vector<Image> &H_vec) {
    vector<Image> ans;
    int beauty = 0;
    ans.push_back(H_vec[0]);
    for (int i = 1; i < H_vec.size(); i++) {
        beauty += Insert(H_vec[i], ans);
    }

    return ans;
}

int main(int args, char **argv) {
    string input_file = argv[1];
    string output_file = argv[2];
    int bach_size = stoi(argv[3]);

    ifstream fin(input_file);
    ofstream fout(output_file);

    vector<Image> V_img, H_img, ans;

    Get_data(fin, V_img, H_img);

//    Verticals_pairing(V_img, H_img);
    Verticals_random_pairing(V_img, H_img);

    vector<Image> bach, ultimate;

    random_shuffle(H_img.begin(), H_img.end());

    int cnt = 0;
    for (int i = 0; i < H_img.size(); i++) {
        bach.push_back(H_img[i]);
        if (bach.size() == bach_size || i == H_img.size() - 1) {
            ans = Solve(bach);
            for (Image img : ans) {
                ultimate.push_back(img);
            }
            bach.resize(0);
            cnt += Count(ans);
            cout << (i + 1) / bach_size << " ===> " << cnt << endl;
        }
    }

    Output_data(fout, ultimate);
    cout << Count(ultimate) << endl;

    return 0;
}