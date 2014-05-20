#include <iostream>
#include <string>
#include <queue>
#include <stdio.h>
#include <set>

using namespace std;

int CountofPF(int n){//count of prime factor
    set<int> factorset;
    int i,c=0;
    //cout << "PF of " << n << " is ";
    for(i=2;i<n;++i)
        while(n!=i){
            if(n%i==0){
                //printf("%d*",i);
                n/=i;
                c++;
                factorset.insert(i);
            }
            else
                break;
        }
        if(c>0) {
            factorset.insert(n);
            return factorset.size();
           /* c=factorset.size(); 
            printf("%d Total=%d...",n,c);
            for(set<int>::iterator it=factorset.begin();it!=factorset.end();++it) 
                cout << *it<< " ";factorset.size()+1;cout << endl;*/
        }
        else {  
            //printf("   Total=0\n",c);
            return 0;
        }
}

struct Mymost{
    bool operator ()(const int num1, const int num2)
    {
        if ( CountofPF(num1) == CountofPF(num2) )
            return num1<num2 ? 1 : 0;
        else if( CountofPF(num1) < CountofPF(num2) )
            return 1;
        else
            return 0;
    }
};


struct Myleast{
    bool operator ()(const int num1, const int num2)
    {
        if ( CountofPF(num1) == CountofPF(num2) )
            return num1>num2 ? 1 : 0;
        else if( CountofPF(num1) > CountofPF(num2) )
            return 1;
        else
            return 0;
    }
};

int main(){
    int n_case;
    cin >> n_case;
    int num;
    while(n_case){
        priority_queue<int,vector<int>,Mymost> mypgm;
        priority_queue<int,vector<int>,Myleast> mypgl;
        for(int i=0;i<10;++i){
            cin >> num;
            mypgm.push(num);
            mypgl.push(num);
        }
        cout << mypgm.top() << " " << mypgl.top() << endl;
        --n_case;
    }

}
