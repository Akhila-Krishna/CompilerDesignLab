#include <iostream>
#include <vector>
using namespace std;

class Node {
    public:
        char state;
        char transition;
};

class NFA {
    public:
        int num;
        Node* link;

};

void initializeFalse(bool *visited, int n) {
    for(int i = 0; i < n; i++) {
        visited[i] = false;
    }
}

void epsilonClosure(NFA *node, int original, int present, int state, vector<int> *closure, bool *visited) {
    if(visited[state] == true) {
        return;
    }
    visited[state] = true;
    closure[original].push_back(state);

    for(int i = 0; i < node[present].num; i++) {
        int val = node[present].link[i].state - 'A';

        if(node[present].link[i].transition == 'e') {
            epsilonClosure(node, original, val, val, closure, visited);
        }
    }
}

void printClosure(vector<int> *closure, int n) {
    for(int i = 0; i < n; i++) {
        cout << "\t" << (char)(i + 'A') << " --> { ";
        int j;

        for(j = 0; j < closure[i].size()-1; j++)
            cout << (char)(closure[i][j] + 'A') << ", ";
        cout << (char)(closure[i][j] + 'A') << " }\n";
        
    }
}

int main() {

    int n, num_states;
    int a[3], num;
    cout << "Enter the number of states: ";
    cin >> n;

    cout << "Enter the number of characters: ";
    cin >> num;
    cout << "Enter the characters: ";
    for(int i = 0; i<num; i++)
        cin >> a[i];

    NFA node[n];
    vector<int> closure[n];
    bool *visited = new bool[n];

    for(int i = 0; i< n; i++) {
        printf("Enter the number of transitions from %c: ", 65 + i);
		cin >> num_states;
        node[i].num = num_states;
        node[i].link = new Node[num_states];
		printf("Enter each <state, symbol> pair: \n");

        for(int j = 0; j < num_states; j++) {
            cin >> node[i].link[j].state >> node[i].link[j].transition;
        }
    }

    for(int i = 0; i < n; i++) {
        initializeFalse(visited, n);
        epsilonClosure(node, i, i, i, closure, visited);
    }
    cout << "Epsilon Closure: \n";
    printClosure(closure, n);
    return 0;    
}