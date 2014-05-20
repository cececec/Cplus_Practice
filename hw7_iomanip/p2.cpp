#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    int num;
    while(cin >> num){
    	cout << hex  <<  num << endl;
	cout << dec << setw(10) << setfill('0')<< right << num << endl;
    
    }

return 0;

}
