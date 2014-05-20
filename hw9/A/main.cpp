#include <iostream>
#include <string>
#include <list>
#include <iterator>

using namespace std;

int main (){
   int n_case;
   cin >> n_case;
   string cmd;
   int id1, id2;
   int num1;
   list<int> mylist[10000];
   while(n_case){
       cin >> cmd;
       if(cmd == "new"){ 
           cin >> id1;
           mylist[id1].clear();
       }
       else if(cmd=="add") {
           cin >> id1 >> num1 ;
           mylist[id1].push_back(num1);
       }
       else if(cmd=="merge") {
           cin >> id1 >> id2;
           mylist[id1].merge(mylist[id2]);
           if (id1 != id2) mylist[id2].clear();
       }
       else if(cmd=="unique") {
           cin >> id1;
           mylist[id1].sort();
           mylist[id1].unique();
       }
       else if(cmd=="out") {
           cin >> id1;
           mylist[id1].sort();
           ostream_iterator<int> o(cout," "); copy(mylist[id1].begin(),mylist[id1].end(),o);
           //  for(list<int>::iterator iter=mylist[id1].begin();iter!=mylist[id1].end(); ++iter)
            //     cout << *iter << " " ;
             cout << '\r' << "\n";
       }
       --n_case;
       }
}


