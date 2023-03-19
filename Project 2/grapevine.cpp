#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;

int count(string input) {
    int n, m, d;
    unordered_map <string, vector<string>> links;
    unordered_map <string, pair<int, int>> people;           
    string r;
    
    istringstream stream(input);
    stream >> n;
    stream >> m;
    stream >> d;

    for (int i = 0; i < n; i++) {
        string s;
        int t;
        pair<int,int> v;
        stream >> s;
        stream >> t;
        v.first = t;
        v.second = 0;
        people[s] = v;
    }

    for (int i = 0; i < m; i++) {
        string u, v;
        stream >> u;
        stream >> v;
        links[u].push_back(v);
        links[v].push_back(u);
    }
    
    stream >> r;
    people[r].second++;
    vector <string> convinced = {r};
    int count = 0;

    for (int i = 0; i < d; i++) {
        vector <string> new_con = {};
        for (string person : convinced) {
            new_con.push_back(person);
        }
        convinced.clear();
        for (string person : new_con) {
            for (string link : links[person]) {
                people[link].second++;
                if ( people[link].second == people[link].first ) {
                    convinced.push_back(link);
                }
                if (people[link].second == 1) {
                    count++;
                }
            }
        }
    }

    return count;
}

int main() {
    ios::sync_with_stdio(0);

    string input;
    getline(cin, input);
    
    int n, m;
    istringstream stream(input);
    stream >> n;
    stream >> m;

    for (int i = 0; i < n + m + 1; i++) {
        string newline;
        getline(cin, newline);
        input += "\n" + newline;
    }

    cout << count(input) << endl;
}