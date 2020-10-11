#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <unordered_map>
#include <map>

using namespace std;

unordered_map<char, int> mapper;
map<set<char>, int> newStateMapper;

class details {
	public:
	char state;
	char input;
};

class Node {
	public:
	int num;
	char state;
	details *data;
};

vector<vector<int> > getNewStates(Node *nfa, vector<char> input, set<set<char> > &new_states, queue<set<char> > &q, int n) {
	int num_input = input.size();
	int mapVar = 1;
	vector<vector<int> > relation;
	vector<int> rel;

	while(!q.empty()) {
		set<char> s = q.front();
		q.pop();
		for(int i = 0; i < num_input; i++) {
			set<char> x;
			for(set<char>::iterator j = s.begin(); j != s.end(); j++) {
				Node node = nfa[mapper.at(*j)];
				for(int k = 0; k < node.num; k++) {
					if(node.data[k].input == input[i]) {
						x.insert(node.data[k].state);
					}
				}	
			}
			if(new_states.find(x) == new_states.end()) {
				new_states.insert(x);
				q.push(x);
				newStateMapper[x] = mapVar++;
			}
			rel.push_back(newStateMapper.at(x));
			x.clear();
		}
		relation.push_back(rel);
		rel.clear();
	}
	return relation;
}

void printMapper(map<set<char>, int> mapper) {
	for(map<set<char>, int>::iterator i = mapper.begin(); i != mapper.end(); i++) {
		for(set<char>::iterator j = (i->first).begin(); j != (i->first).end(); j++)
			cout << *j << " ";
		cout << " \t\t--> " << i->second << endl; 
	}
}

void printDFA(vector<vector<int> > ans, vector<char> input) {
	for(int i = 0; i < ans.size(); i++) {
		for(int j = 0; j < input.size(); j++)
			cout << i << " : " << input[j] << " -> " << ans[i][j] << endl;
		cout << endl;
	}
}

int main() {
	int states, num_input;
	set<set<char> > new_states;
	queue<set<char> > q;
	cout << "Enter the number of states: ";
	cin >> states;
	Node nfa[states];

	cout << "Enter the states: ";
	for(int i = 0; i < states; i++) {
		char ch;
		cin >> ch;
		mapper[ch] = i; 
		nfa[i].state = ch;
	}
	set<char> newStates;	
	newStates.insert(nfa[0].state);
	new_states.insert(newStates);
	q.push(newStates);
	newStateMapper[newStates] = 0;

	cout << "Enter the number of alphabets: ";
	cin >> num_input;
	vector<char> input(num_input);
	cout << "Enter the alphabets: ";
	for(int i = 0; i < num_input; i++) {
		cin >> input[i];
	}

	for(int i = 0; i < states; i++) {
		int val;
		printf("Enter the number of transitions from %c: ", nfa[i].state);
		cin >> val;
		nfa[i].num = val;
		nfa[i].data = new details[val];	
        if(val != 0){
            cout << "Enter the <state, input> pair: \n";
            for(int j = 0; j < val; j++) {
                cin >> nfa[i].data[j].state >> nfa[i].data[j].input;
            }
        }
	}	
	vector<vector<int> > ans = getNewStates(nfa, input, new_states, q, states);
	cout << "\n\nThe new states and their mappings\n";
	printMapper(newStateMapper);
	
	cout << "\n\nThe new DFA\n";
	printDFA(ans, input);	
		
	return 0;		
}
