#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
class CStudent {
public:
char szName[20];
int nScore;
};

int main()
{
CStudent s;
long location;
ifstream fin("input.txt", ios::in);//ios::app (append)
ofstream fout("output.txt", ios::out);//|ios::binary );
//fstream iofile( “c:\\tmp\\students.dat”, ios::in|ios::out|ios::binary);


//print data in fin
while( fin.read( (char* ) & s, sizeof(s) ) ) {
  int nReadedBytes = fin.gcount(); //看刚才读了多少字节
  cout << s.szName << " " << s.nScore << endl;
}


//import data from console to fout
while( cin >> s.szName >> s.nScore ) {
  if( strcmp(s.szName, "exit" ) == 0) //名字为exit则结束
  break;
  fout.write( (char *) & s, sizeof(s) );
}
fout.write("\nDone\n", strlen("Done.."+1));
//fout.seekp(location);


//import data from fin to fout
location = fin.tellg();//Get location of InPointer
cout << location<< endl;
location = 10L;//Since it is "long", "L" has to be attached after num
fin.close();
fin.open("input.txt", ios::in);//ios::app (append)
cout << location<< endl;
fin.seekg(location, ios::beg );//move to no.10 bytes from beginning; ios::cur ios::end; location can be negative
char c;
while(fin.get(c)) {fout.put(c);}
fout.close();
fin.close();
return 0;
}
