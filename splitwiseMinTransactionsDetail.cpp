#include<iostream>
#include<set>
#include<map>
using namespace std;

//Splitwise Algorithm Implementation
class person_compare{
public:
    bool operator()(pair<string, int> p1, pair<string, int> p2){
        return p1.second < p2.second;
    }
};
int main(){

    int no_of_transactions, friends;
    cin>>no_of_transactions>>friends;

    // person x gives amt to person y
    string x,y;
    int amt;
    
    // (person: net amount) hashmap
    map<string, int> net;
    while(no_of_transactions--){
        cin>>x>>y>>amt;
        if (net.count(x)==0){
            net[x]=0;
        }
        if (net.count(y)==0){
            net[y]=0;
        }

        net[x] -= amt;
        net[y] += amt;
    }

    //List of (Person:net amount) sorted wrt net amount
    multiset<pair<string, int>, person_compare> m;

    for (auto p:net){
        string person = p.first;
        int amt = p.second;

        if (net[person]!=0){
            m.insert(make_pair(person, amt));
        }
    }

    // Make Settlements 
    int count=0;
    while(!m.empty()){
        auto low = m.begin();
        auto high = prev(m.end());

        int debit = low->second;
        string debit_person = low->first;

        int credit = high->second;
        string credit_person = high->first;

        m.erase(low);
        m.erase(high);

        int settled_amt = min(-debit, credit);
        count++;
        debit += settled_amt;
        credit -= settled_amt;

        cout<<debit_person<<" will pay "<<settled_amt<<" to "<<credit_person<<endl;

        if(debit!=0){  
            m.insert(make_pair(debit_person, debit));
        }
        if(credit!=0){
            m.insert(make_pair(credit_person, credit));
        }
    }

    cout<<"Minimum Transactions:"<<count;
}
