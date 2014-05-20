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

string line[3];

int CountofOperator(string cmd){
    if(cmd=="copy")  return  3;
    else if(cmd=="add")   return  2;
    else if(cmd=="find")  return  2;
    else if(cmd=="rfind") return  2;
    else if(cmd=="insert")return  3;
    else if(cmd=="reset") return  2;
    else if(cmd=="print") return  1;
    else if(cmd=="printall") return 0;
    else if(cmd=="over")  return -1 ;
}
int GetN(string str){//inline Get Number
    return atoi(str.c_str());
}

string Exc(string cmd,string* opr){
    if(cmd=="copy") {//N X L
        cout << "copy line[" << GetN(opr[0])-1 << "] from " <<  GetN(opr[1]) << " to " << GetN(opr[2])<< endl;
        string tmp;
        cout << "begin"  << endl;
        cout <<line[GetN(opr[0])-1] << endl;
        cout << "end"  << endl;
        tmp= ( line[GetN(opr[0])-1].substr( GetN(opr[1]), GetN(opr[2]) ) );
        cout << "lala"  << endl;
        return tmp; 
    } 
    else if(cmd=="add") {// S1 S2
        return opr[0] + opr[1];
        //if are num TODO
    } 
    else if(cmd=="find") {//S N
        unsigned found=line[GetN(opr[1])-1].find_first_of(opr[0]);
        cout << "Finding " << opr[0] << " from " << line[GetN(opr[1])] << endl;
        cout << "nops is " << string::npos << endl;
        if (found<100000000){
            long tmp = found;
            long double tmp2=tmp;
            cout << "find something" << endl;
            return to_string(tmp2);
        }
        else{
            cout << "nothing" << endl;
            return to_string((long long unsigned int)opr[0].length());
        }
    } 
    else if(cmd=="rfind") {// S N
        unsigned found=line[GetN(opr[1])-1].rfind(opr[0]);
        if (found<100000000){
            long tmp = found;
            long double tmp2=tmp;
            return to_string(tmp2);
        }
        else{
            return to_string((long long unsigned int)opr[0].length());
        }
    } 
    else if(cmd=="insert") {//S N X
        return line[GetN(opr[1])-1].insert(GetN(opr[2]), opr[0]);
    } 
    else if(cmd=="reset") {//S N
         return line[GetN(opr[1])-1].replace(line[GetN(opr[1])].begin(),line[GetN(opr[1])].end(),opr[0]);
    } 
    else if(cmd=="print") {//N
       cout << line[GetN(opr[0])-1] << endl;
       return  line[GetN(opr[0])-1];
    } 
    else if(cmd=="printall"){ 
        for (int i=0;i<3; ++i)
            cout << line[GetN(opr[i])] << endl;
    } 
    else if(cmd=="over")    {  } 

}

int main(){
    string cmdline;
    string word;
    stack<string> myfs;//forward stack
    stack<string> mybs;//backward stack
    int n;
    cin >> n ;
    for(int i=0; i<n; ++i)
        cin >> line[i];
    
    char a,b;
    a='\n';
    cin.unsetf(ios::skipws);
    cin>>b;//'\n'
    while(cin){
        while(!mybs.empty()) mybs.pop();
    for(int i=0; i<3; ++i)
        cout << "========line[" << i << "] is " <<  line[i]<< " ";
    cout << endl;
        cin >> word;
        if(word=="over") break;
        myfs.push(word);
        cout << word <<" ";
        cin >> b;
        if (b =='\n') {//end of line
            cout << "yeah!" << endl;
            while(!myfs.empty()){
                if(myfs.top().length()<3){// an operator
                    mybs.push(myfs.top());
                    cout << myfs.top() << " into mybs" << endl;
                    myfs.pop();
                }
                else{//cmd
                    int n_opr = CountofOperator(myfs.top());
                    cout << myfs.top() << " needs " << n_opr << " operators" << endl;
                    string opr[3];
                    for(int i=0; i<n_opr; ++i){
                        opr[i]=mybs.top();
                        cout<< "opr[" << i << "] is "<< opr[i] << ", " ;
                        mybs.pop();
                    }
                    cout << "with cmd-->" << myfs.top() << endl;
                   
    for(int i=0; i<3; ++i)
        cout << "line[" << i << "] is " <<  line[i]<< " ";
    cout << endl;
                    mybs.push(Exc(myfs.top(),opr));
                    cout << "returnedis " << mybs.top()<< endl;
                    myfs.pop();
                }
            }
        }
    }//end while
    //while(cin=="\n"){
      //  cout << "haha ";
       /* getline(cin,cmdline);
        cout << cmdline << endl;
        MyV myv(100);
        //stack<int> mys;
        istringstream iss(cmdline);
        copy( MyII(iss), MyII(), myv.begin());
        stack<int> mys;
        for(MyVI rit=myv.rbegin(); rit!=myv.rend(); ++rit){
            if (*it.length()<3){// is a operator
                it++;
            }
            else {
                //is a cmd
            }
        */

//    }
}
