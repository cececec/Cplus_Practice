#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

using namespace std;


int main(){
     
    int num_case;
    int in_n;
    int in_i;
    int in_j;
    int k[15];//only need 0~13

    cin >> num_case;
    while (num_case--){
        cin >> in_n >> in_i >> in_j;
        for(int i=0;i<15;i++) { k[i]=0;}

        int tmpi=in_i;
        int tmpj=in_j;
        int n=in_n;
        int k_bit;
        while(tmpi--){
            k_bit=n%2;
            n=(n-n%2)/2;
            //cout << k_bit << endl;
        }
        k[in_i]=n%2;
        n=in_n;
        while(tmpj--){
            k_bit=n%2;
            n=(n-n%2)/2;
            //cout << k_bit << endl;
        }
        k[in_j]=1-n%2;

        int final=0;
        int weight=1;
        for(int z=0;z<15;++z)  {
            final = k[z]*weight+final;
        //    cout << "K[" <<z << "] is " << k[z] << " weight is " << weight << " sum is "<< final<< " "<< endl;
            weight=weight*2;
        }
            cout << final<< endl;
         //cout << "end"  << endl;
    }
    return 0;
}
