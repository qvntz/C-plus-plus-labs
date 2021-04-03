#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;


vector<string> SplitIntoWords(const string& str) {
    vector<string> result;
    auto str_begin = begin(str);
    
    while (true) {
        
        auto it = find(str_begin, end(str), ' ');
        result.push_back(string(str_begin, it));

        if (it == end(str)) {
            break;
        }
        else {
            str_begin = it + 1;
        }
    }

    return result;
}

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}
