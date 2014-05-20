#include <iostream>
#include <string.h>
#include <vector> 

using namespace std;

char* Exp(char* r, int n){
        int p, c=0;
        int idx=0;
        char* temp;
        temp = new char(n*strlen(r));
        for(int i=0; i<n; ++i){
            for(int j=strlen(r)-1; j>=0; --j){
                p = ((int)temp[j]*(int)r[j]+c)%10;
                c = ((int)temp[j]*(int)r[j]-p)/10;
                temp[idx++]=p; cout << p << "." ;
            }
            cout << "p= " << temp[0] << endl;
        } 
        return temp;
}


int main() {
    string s;
    int n;
    char* r, *f;
    while(cin >> s >> n){
        unsigned pos = s.find(".");
        r = new char(s.substr(0,pos).length()+1);
        f = new char(s.substr(pos+1).length()+1);
        strcpy(r, (s.substr(0,pos)).c_str());
        strcpy(f, s.substr(pos+1).c_str());
        cout << r << " " << f << " " << n << endl;
        Exp(r,n);
    }
}

