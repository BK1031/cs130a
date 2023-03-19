#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <utility>
#include <limits>
#include <algorithm> 
#include <bits/stdc++.h>

using namespace std;

class Node {
public:
    int number;
    vector<pair<int,int>> children;

    Node() {
        this->number = -1;
    }
    Node (int number) {
        this->number = number;
    }
    Node (const Node& other) {
        this->number = other.number;
        for (auto child : other.children) {
            this->add(child.first, child.second);
        }
    }

    void add(int num, int len) {
        pair<int, int> input;
        input.first = num;
        input.second = len;
        children.push_back(input);
    }
};

vector<int> traversalDistance(const vector<Node>& city, int s, vector<int>& path) {
    vector<int> distances(city.size());
    bool visited[city.size()];

    for (int i = 0; i < city.size(); i++) {
        visited[i] = false;
        path[i] = -1;
        distances[i] = INT_MAX;
    }

    distances[s] = 0;
    path[s] = -1;
    int current = s;

    unordered_set<int> int_set;
    while (true) {
        visited[current] = true;
        for (auto child : city[current].children) {
            int v = child.first;
            if (visited[v]) continue;
            int_set.insert(v);
            int alt = distances[current] + child.second;
            if (alt < distances[v]) {
                distances[v] = alt;
                path[v] = current;
            }
        }
        int_set.erase(current);
        if (int_set.empty()) {
            break;
        }
        int min = INT_MAX;
        int index = 0;
        for (int a : int_set) {
            if (distances[a] < min) {
                min = distances[a];
                index = a;
            }
        }
        current = index;
    }

    return distances;
}

bool isValidPath(int i, int s, int g, int h, vector<int> path) {
    if (i > s) {
        if (path[i] == -1) {
            return false;
        } else if (path[i] == h && path[h] == g) {
            return true;
        } else if (path[i] == g && path[g] == h) {
            return true;
        }
    } else {
        return false;
    }
    return isValidPath(path[i], s, g, h, path);
}

bool checkEdgeCase(int i, int s, int g, int h, vector<Node> city, vector<int> dist) {
    vector<int> path(city.size());
    vector<int> hdist = traversalDistance(city, h, path);
    vector<int> gdist = traversalDistance(city, g, path);
    
    int gtoh, htog;
    
    for (auto child : city[g].children) {
        if (child.first == h) {
            gtoh = child.second;
        }
    }    
    for (auto child : city[h].children) {
        if (child.first == g) {
            htog = child.second;
        }
    }
    if ((dist[i] == dist[h] + htog + gdist[i]) || (dist[i] == dist[g] + gtoh + hdist[i])) {
        return true;
    }
    return false;
}

void calculate(const string& input) {
    int num;
    std::istringstream stream(input);
    stream >> num;
    
    for (int i = 0; i < num; i++) {
        int n, m, t, s, g, h;
        stream >> n >> m >> t >> s >> g >> h;

        s--;
        g--;
        h--;

        std::vector<Node> city(n);
        std::vector<int> destinations;

        for (int j = 0; j < n; j++) {
            Node intersection(j);
            city[j] = intersection;
        }
        for (int j = 0; j < m; j++) {
            int a, b, d;
            stream >> a >> b >> d;
            a--;
            b--;
            city[a].add(b,d);
            city[b].add(a,d);
        }
        for (int j = 0; j < t; j++) {
            int x;
            stream >> x;
            x--;
            destinations.push_back(x);
        }

        std::vector<int> path(city.size());
        std::vector<int> distance = traversalDistance(city, s, path);
        sort(destinations.begin(), destinations.end());

        for (int destination : destinations) {
            if(isValidPath(destination, s, g, h, path)) {
                std::cout << destination + 1 << " ";
            }
            else if(checkEdgeCase(destination, s, g, h, city, distance)) {
                std::cout << destination + 1 << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    string input;
    getline(cin, input);

    int num;
    istringstream stream(input);
    stream >> num;

    for (int i = 0; i < num; i++) {
        string line;
        int n, m, t;
        getline(cin, line);
        input += "\n";
        input += line;
        istringstream newstream(line);
        newstream >> n >> m >> t;

        getline(cin, line);
        input += "\n";
        input += line;

        for (int j = 0; j < m; j++) {
            getline(cin, line);
            input += "\n";
            input += line;
        }

        for (int j = 0; j < t; j++) {
            getline(cin, line);
            input += "\n";
            input += line;
        }

    }
    calculate(input);
}