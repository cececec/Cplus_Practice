#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum colors_t {w,y};

colors_t paint[17][17];
int puzzle[17][17];

int totnum;

bool guess(){

}

void enumbegin(int n){
    int r, c, i, j, k;
    totnum = 400;
    for ( c = 1; c <= n; ++c ){
       scanf("%d", &paint[1][c]);
       


    }


}

int main(){
    int t;//number of cases
    scanf("%d",&t);
    while(t--){
        int n;//size <=15
        scanf("%d",&n);
        for( r = 0; r <= 16; ++r )
            for ( c = 0; c <= 16; ++c )
                paint[r][c] = w;
        for ( r = 1; r <= n; ++r ){
            for ( c = 1; c <= n; ++c )
                scanf("%d", &paint[r][c]);
        enumbegin(n);         
    }

}
