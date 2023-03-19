#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <utility>
#include <bits/stdc++.h>
using namespace std;

class Node {
    public:
        int number;
        list<pair<int,int>> paths;
        
        Node (int number) {
            this->number = number;
        }

        void add(int num, int len) {
            pair<int, int> input;
            input.first = num;
            input.second = len;
            paths.push_back(input);
        }
};

int traverse(vector<Node> forest) {
    vector<int> distance(forest.size());
    vector<int> result(forest.size(), 0);
    result.at(1) = 1;

    bool visited[forest.size()];
    for (int i = 0; i < forest.size(); i++) {
        visited[i] = false;
        distance[i] = INT_MAX;
    }

    distance[1] = 0;
    int current = 1;
    unordered_set<int> breadth;

    while(true) {
        visited[current] = true;
        for (auto path : forest[current].paths) {
            int v = path.first - 1;
            if (visited[v]) {
                if (distance[v] < distance[current]) {
                    result.at(current) += result.at(v);
                }
                continue;
            }
            breadth.insert(v);
            int alt = distance[current] + path.second;
            if (alt < distance[v]) {
                distance[v] = alt;
            }
        }
        breadth.erase(current);
        if (breadth.empty()) {
            return result.at(0);
        }
        int min = INT_MAX;
        int index = 0;
        for (int a : breadth) {
            if (distance[a] < min) {
                min = distance[a];
                index = a;
            }
        }
        current = index;
    }
    return result.at(0);
}

void calculate(string input) {
    istringstream stream(input);
    while (true) {
        int n, m;
        vector<Node> forest;

        stream >> n;
        if (n == 0) break; 
        stream >> m;

        for (int i = 1; i <= n; i++) {
            Node intersection(i);
            forest.push_back(intersection);
        }
        for (int i = 0; i < m; i++) {
            int a, b, d;
            stream >> a >> b >> d;
            forest[a-1].add(b,d);
            forest[b-1].add(a,d);
        }

        cout << traverse(forest) << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    string line;
    string input;

    while (cin >> line) {
        if (line == "0") {
            input += line;
            break;
        }
        input += line + "\n";
    }

    calculate(input);
    return 0;
}