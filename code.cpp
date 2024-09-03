#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

unordered_map<string, vector<pair<string, int>>> graph = {
    {"Arad", {{"Zerind", 75}, {"Timisoara", 118}, {"Sibiu", 140}}},
    {"Zerind", {{"Arad", 75}, {"Oradea", 71}}},
    {"Timisoara", {{"Arad", 118}, {"Lugoj", 111}}},
    {"Sibiu", {{"Arad", 140}, {"Oradea", 151}, {"Fagaras", 99}, {"Rimnicu Vilcea", 80}}},
    {"Oradea", {{"Zerind", 71}, {"Sibiu", 151}}},
    {"Lugoj", {{"Timisoara", 111}, {"Mehadia", 70}}},
    {"Fagaras", {{"Sibiu", 99}, {"Bucharest", 211}}},
    {"Rimnicu Vilcea", {{"Sibiu", 80}, {"Pitesti", 97}, {"Craiova", 146}}},
    {"Mehadia", {{"Lugoj", 70}, {"Drobeta", 75}}},
    {"Drobeta", {{"Mehadia", 75}, {"Craiova", 120}}},
    {"Craiova", {{"Drobeta", 120}, {"Rimnicu Vilcea", 146}, {"Pitesti", 138}}},
    {"Pitesti", {{"Rimnicu Vilcea", 97}, {"Craiova", 138}, {"Bucharest", 101}}},
    {"Bucharest", {{"Fagaras", 211}, {"Pitesti", 101}, {"Giurgiu", 90}, {"Urziceni", 85}}},
    {"Giurgiu", {{"Bucharest", 90}}},
    {"Urziceni", {{"Bucharest", 85}, {"Hirsova", 98}, {"Vaslui", 142}}},
    {"Hirsova", {{"Urziceni", 98}, {"Eforie", 86}}},
    {"Eforie", {{"Hirsova", 86}}},
    {"Vaslui", {{"Urziceni", 142}, {"Iasi", 92}}},
    {"Iasi", {{"Vaslui", 92}, {"Neamt", 87}}},
    {"Neamt", {{"Iasi", 87}}}
};

class Node{
public:
    string city;
    int cost;
    Node* parent;

    Node(string city, int cost, Node* parent){
        this->city = city;
        this->cost = cost;
        this->parent = parent;
    }
};

class Compare{
public:
    bool operator()(Node* a, Node* b){
        if(a->cost > b->cost){
            return true;
        }else{
            return false;
        }
    }
};

vector<string> a_star_search(Node* startingNode, Node* destinationNode){
    vector<string> path;
    priority_queue<Node*, vector<Node*>, Compare> pathList;
    set<string> visited;
    pathList.push(startingNode);

    while(!pathList.empty()){
        Node* currentNode = pathList.top();
        pathList.pop();

        if(currentNode->city == destinationNode->city){
            while(currentNode){
                path.push_back(currentNode->city);
                currentNode = currentNode->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        visited.insert(currentNode->city);

        for(auto &x : graph[currentNode->city]){
            if(visited.find(x.first) == visited.end()){
                int newCost = currentNode->cost + x.second; 
                Node* newNode = new Node(x.first, newCost, currentNode);
                pathList.push(newNode);
            }
        }
    }

    return path;
}

int main(){
    string startingCity, destinationCity;
    cout << "Masukkan kota awal: ";
    cin >> startingCity;
    cout << "Masukkan kota tujuan: ";
    cin >> destinationCity;

    Node* startingNode = new Node(startingCity, 0, NULL);
    Node* destinationNode = new Node(destinationCity, 0, NULL);
    vector<string> path = a_star_search(startingNode, destinationNode);

    if(!path.empty()){
        cout << "Berikut adalah jalur yang paling efisien dari " << startingCity << " ke " << destinationCity << "." << endl;
        for(int i = 0; i < path.size(); i++){
            if(i != path.size() - 1){
                cout << path[i] << "->";
            }else{
                cout << path[i];
            }
        }
        cout << endl;
    }else{
        cout << "Jalur tidak ditemukan." << endl;
    }
    
    return 0;
}