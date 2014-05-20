#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>//system
#include <libxl.h>

using namespace std;

int main()
{
    libxl::Book* book;
    book= xlCreateBook();
    ifstream indata;
    ofstream outdata;
    outdata.open("spreedsheet.csv", ofstream::out |  ios::app);//??
    outdata << "a1,b1,c1" << endl;
    outdata << "a2,b2,c2" << endl;
    outdata.close();
    indata.open("spreedsheet.csv");//comma seperated values
    string cell1;

    indata >> cell1;
    cout << cell1 << "\n\n";
    indata >> cell1;
    cout << cell1 << endl;

    indata.close();
    system("ls");
    return 0;
}
