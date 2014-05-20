#include <iostream>
#include <string>
#include <queue>
#include <stdio.h>
#include <set>
#include <math.h>
//#define DEBUG
using namespace std;

int CountofPF(int n){//count of prime factor
    set<int> factorset;
    int i,c=0;
#ifdef DEBUG
    cout << "PF of " << n << " is ";
#endif
    for(i=2;i<sqrt(n)+1;++i)
        while(n!=i){
            if(n%i==0){
#ifdef DEBUG
                printf("%d*",i);
#endif
                n/=i;
                c++;
                factorset.insert(i);
            }
            else
                break;
        }
        if(c>0) {
            factorset.insert(n);
            c=factorset.size(); 
#ifdef DEBUG
            printf("%d Total=%d\n",n,c);
#endif
            return factorset.size();
        }
        else {  
#ifdef DEBUG
            printf("   Total=0\n");
#endif
            return 0;
        }
}

struct Mymost{
    bool operator ()(const int num1, const int num2)
    {
        int c1, c2;
        c1 = CountofPF(num1);
        c2 = CountofPF(num2);  
        if ( c1 == c2 )
            return (num1<num2 ? 1 : 0);
        else if( c1 < c2 )
            return 1;
        else
            return 0;
    }
};


struct Myleast{
    bool operator ()(const int num1, const int num2)
    {
        int c1, c2;
        c1 = CountofPF(num1);
        c2 = CountofPF(num2);  
        if (c1 == c2)
            return (num1>num2 ? 1 : 0);
        else if( c1 > c2 )
            return 1;
        else
            return 0;
    }
};

int main(){
    int n_case;
    cin >> n_case;
    int num;
    priority_queue<int,vector<int>,Mymost> mypgm;
    priority_queue<int,vector<int>,Myleast> mypgl;
    while(n_case){
        for(int i=0;i<10;++i){
            cin >> num;
            mypgm.push(num);
            mypgl.push(num);
#ifdef DEBUG
            cout <<"Top is " << mypgm.top() << endl;
#endif
        }
        printf("%d %d\r\n",mypgm.top(),mypgl.top());
        mypgm.pop();
        mypgl.pop();
        --n_case;
    }
    printf("\r\n\r\n\r\n\r\n");
}
