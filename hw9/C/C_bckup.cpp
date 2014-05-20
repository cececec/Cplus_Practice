#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <stack>
#include <algorithm>
#include <iterator>
#include <sstream>

using namespace std;
typedef vector<string> MyV;
typedef vector<string>::iterator MyVI;
typedef istream_iterator<string> MyII;

int main(){
    string line[3];
    string cmdline;
    int n;
    cin >> n ;
    for(int i=0; i<n; ++i)
        cin >> line[i];

    while(cin){
        getline(cin,cmdline);
        cout << cmdline << endl;
        MyV myv(100);
        //stack<int> mys;
        istringstream iss(cmdline);
        copy( MyII(iss), MyII(), myv.begin());
        //copy( istream_iterator<string>(iss), istream_iterator<string>(), ostream_iterator<string>(cout, " ?"));
        //for(vector<string>::iterator it=myv.begin();it!=myv.end();++it)
        //    cout << *it << " " ;
        //cout << endl;
        stack<int> mys;
        for(MyVI rit=myv.rbegin(); rit!=myv.rend(); ++rit){
            if (*it.length()<3){// is a operator
                it++;
            }
            else {
                //is a cmd
            }
        

    }
}
