#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>

using namespace std;
int main(){
    int n_case;
    int id, force;
    //cin >> n_case;
    scanf("%d",&n_case);
    map<int, int> mymap;
    mymap.insert( pair<int, int>(1000000000,1) );//force, id
    while(n_case){
        map<int, int>::iterator itlow, itup;
        scanf("%d %d",&id,&force);   //cin >> id >> force;
        mymap.insert( pair<int, int>(force, id) );//force, d
        itlow = mymap.lower_bound(force);
        itup  = mymap.upper_bound(force);
        if (mymap.begin()->second == id) {
            if ( abs(itup->first - force) >= abs((--itlow)->first - force) )
               printf("%d %d\n",id,itlow->second);//cout << id << itup->second << endl;
            else printf("%d %d\n",id,itup->second);//cout << id << itlow->second << endl;
        }
        else {//this is with minimal force
            printf("%d %d\n",id,itup->second);// cout << id << itup->second << endl;
        }
        --n_case;
    }
}
