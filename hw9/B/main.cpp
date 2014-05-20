#include <iostream>
#include <string>
#include <set>

using namespace std;
int main(){
    int n_case;
    string cmd;
    int num;
    multiset<int> myset;
    set<int> visited;
    cin >> n_case;
    while (n_case){
        cin >> cmd >> num;
        if(cmd == "add") {
            myset.insert(num);
            visited.insert(num);
            cout << myset.count(num) << endl;
        }
        else if(cmd == "del") {
            cout << myset.count(num) << endl;
            myset.erase(num);
        }
        else if(cmd == "ask") {
            if(visited.count(num)) cout << "1 ";
            else cout << "0 ";
            cout << myset.count(num) << endl;
        }
        --n_case;
    }

}
