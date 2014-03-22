#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

class Student {
private:
  string myname;
  int myage;
  string myid;
  int my1st_grade;
  int my2nd_grade;
  int my3rd_grade;
  int my4th_grade;
  int myaverage;

  public:
  Student() {};

  void record(char *name, int age, char *id, int grade1, int grade2, int  grade3, int grade4){
    myname=name;
    myage=age;
    myid=id;
    my1st_grade=grade1;
    my2nd_grade=grade2;
    my3rd_grade=grade3;
    my4th_grade=grade4;}

  void get_average() {
  //cout <<"Get average of " <<my1st_grade << ","<< my2nd_grade << ","<< my3rd_grade << ","<< my4th_grade <<endl;
  myaverage= ((my1st_grade
               + my2nd_grade
               + my3rd_grade
               + my4th_grade)/4);
    //cout << "Average is " << myaverage << endl;
    }

   void print() {
    //cout << "Printing..." << endl;
    //    //cout << "name is ";
            cout <<myname << "," << myage << "," << myid << "," << myaverage <<  endl;   
               }


};


int main()
{
 
  char *name=new char[20];
  int age;
  char *id=new char[20];
  int grade1;
  int grade2;
  int grade3;
  int grade4;

 // cout << "Please enter name: " << endl;
 
 char c;

cin.getline(name,15,',');//name是指向字符串的指针,15代表了能够读入的输入字符的个 //数包括数组最后的结束符,逗号代表遇到逗号字符时自动停止读入。
  cin >> age >> c;
  cin.getline(id,10,','),
  cin>>grade1>>c>>grade2>>c>>grade3>>c>>grade4;

 // cin >> name; cin.ignore(1,','); 
 //   // cin >> age ; cin.ignore(1,','); 
 //     // cin >> id  ; cin.ignore(1,',');
 //       // cin >> st_grade; cin.ignore(1,'1'); 
 //         // cin >> nd_grade; cin.ignore(1,'1'); 
 //           // cin >> rd_grade; cin.ignore(1,'1'); 
 //             // cin >> th_grade;
 //               // cout << name << "," << age << ","<< id << ", "<<grade1 <<", " << grade2 << ", " << grade3 << ", " << grade4 << " "<<endl;
 
    Student my_student;
    my_student.record(name,age,id,grade1,grade2,grade3,grade4);
    my_student.get_average();
    my_student.print();
    return 0;
}
 
