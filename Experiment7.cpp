#include "bits/stdc++.h"

using namespace std;

void printSet(set<int> arr){
    for(auto it = arr.begin(); it != arr.end(); it++)
        cout<<*it<<" ";
}

int main(){
    int states,sym;
    map<pair<int,int>,int> transition_table;
    vector<char> symbols;
    char c;
    cout<<"Enter the number of states: ";
    cin>>states;
    cout<<"Enter the number of symbols: ";
    cin>>sym;
    cout<<"Enter the symbols: ";
    for(int i = 0; i < sym; i++){
        cin>>c;
        symbols.push_back(c);
    }
    int t;
    for(int i = 0; i < states; i++){
        cout<<"Enter the transitions for state "<<i<<"\n";
        for(int j = 0; j < sym; j++){
            cout<<"\t"<<symbols[j]<<"  ";
            cin>>t;
            transition_table[{i,j}] = t;
        }
    }
    set<int> final;
    map<pair<int,int>, int> min_table;
    int final_size;
    cout<<"Enter the number of final states: ";
    cin>>final_size;
    cout<<"Enter the states: ";
    for(int i = 0; i < final_size; i++){
        cin>>t;
        final.insert(t);
    }
    for(int i = 0; i < states; i++)
            for(int j = i+1; j < states; j++){
                if((final.find(i) != final.end() && final.find(j) != final.end()) || (final.find(i) == final.end() && final.find(j) == final.end()))
                    min_table[{i,j}] = 0;
                else 
                    min_table[{i,j}] = 1;
            }
    bool update = false;
    int a,b,count = 0;
    do{
        update = false;
        for(int i = 0; i < states; i++)
            for(int j = i+1; j < states; j++){
                if(min_table[{i,j}] == 1)
                    continue;
                for(int k = 0; k < sym; k++){
                    a = transition_table[{i,k}];
                    b = transition_table[{j,k}];
                    if(a > b){
                        int t = a;
                        a = b;
                        b = a;
                    }
                    else if(a == b)
                        continue;
                    if(min_table[{a,b}] == 1){
                        update = true;
                        min_table[{i,j}] = 1;
                        break;
                    }
                    
                }
            }
        count++;
    }while(update);
    set<int> unmerged_states;
    vector<set<int> > merged_states;
    for(int i = 0; i < states; i++)
        unmerged_states.insert(i);
    bool found;
    for(auto it = min_table.begin(); it != min_table.end();it++){
        if(it->first.first == it->first.second)
            continue;
        if(it->second == 1)
            continue;
        int a = it->first.first;
        int b = it->first.second;
        found = false;
        if(unmerged_states.find(a) != unmerged_states.end())
            unmerged_states.erase(a);
        if(unmerged_states.find(b) != unmerged_states.end())
            unmerged_states.erase(b);
        for(auto jt = merged_states.begin(); jt != merged_states.end(); jt++){
            if(jt->find(b) != jt->end()){
                jt->insert(a);
                found = true;
                break;
            }
            if(jt->find(a) != jt->end()){
                jt->insert(b);
                found = true;
                break;
            }
        }
        if(!found)
            merged_states.push_back({a,b});
    }
    cout<<"The final minimised states: \n";
    for(auto it = unmerged_states.begin(); it != unmerged_states.end(); it++)
        cout<<*it<<endl;
    for(auto it = merged_states.begin(); it != merged_states.end(); it++){
        for(auto jt = it->begin(); jt != it->end(); jt++)
            cout<<*jt<<" ";
        cout<<endl;
    }
    cout<<"Minimised Transition table: \n";
    for(auto it  = unmerged_states.begin(); it != unmerged_states.end(); it++){
        for(int j = 0; j < sym; j++){
            int end = transition_table[{*it,j}];
            if(unmerged_states.find(end) != unmerged_states.end()){
                cout<<"[ "<<*it<<" ]----"<<symbols[j]<<"---->[ "<<end<<" ]"<<endl;
            }
            else
            {
                for(auto kt = merged_states.begin(); kt != merged_states.end(); kt++){
                    if(kt->find(end) != kt->end()){
                        cout<<"[ "<<*it<<" ]----"<<symbols[j]<<"---->[ ";
                        printSet(*kt);
                        cout<<"]"<<endl;
                    }
                }
            }
            
        }
    }
    for(auto it = merged_states.begin(); it != merged_states.end(); it++){
        for(int j = 0; j < sym; j++){
            int start = *(it->begin());
            int end = transition_table[{start,j}];
            if(unmerged_states.find(end) != unmerged_states.end()){
                cout<<"[ ";
                printSet(*it);
                cout<<"]----"<<symbols[j]<<"----> [ "<<end<<" ]"<<endl;
            }
            else
            {
                for(auto kt = merged_states.begin(); kt != merged_states.end(); kt++){
                    if(kt->find(end) != kt->end()){
                        cout<<"[ ";
                        printSet(*it);
                        cout<<"]--"<<symbols[j]<<"---->[ ";
                        printSet(*kt);
                        cout<<"]"<<endl;
                    }
                }
            }
        }
    }
}