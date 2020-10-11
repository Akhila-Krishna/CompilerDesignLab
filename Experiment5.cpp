#include "bits/stdc++.h"

using namespace std;

set<int> epsilon_closure(vector<vector<set<int> > > transitions, int start){
        queue<int> answer;
        set<int> res;
        answer.push(start);
        int t;
        while(!answer.empty()){
                t = answer.front();
                cout<<t<<" ";
                if(res.find(t) == res.end())
                    res.insert(t);
                for(auto i = transitions[t][0].begin(); i != transitions[t][0].end(); i++)
                        answer.push(*i);
                answer.pop();
        }
        cout<<endl;
        return res;
}

int main(){

        vector<vector<set<int> > > transitions;
        vector<vector<set<int> > > nfa_transitions;
        int states,symbols;
        vector<string> sym;
        string s;
        cout<<"Enter the number of states: ";
        cin>>states;
        cout<<"Enter the number of symbols: ";
        cin>>symbols;
        cout<<"Enter the symbols: "<<endl;
        sym.push_back("ε");
        for(int i = 1; i < symbols; i++){
                cin>>s;
                sym.push_back(s);
        }
        transitions.resize(states);
        nfa_transitions.resize(states);
        for(int i = 0; i < states; i++){
            transitions[i].resize(symbols);
            nfa_transitions[i].resize(symbols);
        }
        int t;
        int val;
        for(int i = 0; i < states; i++){
            for(int j = 0; j < symbols; j++){
                cout<<"Enter number of transitions for state "<<i<<" and symbol "<<sym[j]<<": ";
                cin>>t;
                if(t!=0){
                    cout<<"Enter transition states: ";
                    while(t--){
                        cin>>val;
                        transitions[i][j].insert(val);
                    }
                }
            }
        }
        vector<set<int> > eClos;
        eClos.resize(states);
        for(int i = 0; i < states; i++){
            cout<<i<<" : ";
            eClos[i] = epsilon_closure(transitions,i);
        }
        for(int i = 0; i < states; i++){
            for(int j = 1; j < symbols; j++){
                for(auto itr = eClos[i].begin(); itr != eClos[i].end(); itr++){
                    for(auto jtr = transitions[*itr][j].begin(); jtr != transitions[*itr][j].end(); jtr++){
                        if(nfa_transitions[i][j].find(*jtr) == nfa_transitions[i][j].end())
                            nfa_transitions[i][j].insert(*jtr);
                    }
                }
            }
        }
        cout<<endl;
        for(int i = 0; i < states; i++){
            for(int j = 1; j < symbols; j++){
                for(auto itr = nfa_transitions[i][j].begin(); itr != nfa_transitions[i][j].end(); itr++){
                    for(auto jtr = eClos[*itr].begin(); jtr != eClos[*itr].end(); jtr++){
                        if(nfa_transitions[i][j].find(*jtr) == nfa_transitions[i][j].end())
                            nfa_transitions[i][j].insert(*jtr);
                    }
                }
            }
        }
        for(int i = 0; i < states; i++){
            for(int j = 1; j < symbols; j++){
                cout<<i<<" -> "<<sym[j]<<" : ";
                for(auto itr = nfa_transitions[i][j].begin(); itr != nfa_transitions[i][j].end(); itr++)
                    cout<<*itr<<" ";
                cout<<endl;
            }
            cout<<endl;
        }
        return 0;
}
