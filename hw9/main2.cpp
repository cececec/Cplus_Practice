#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
using namespace std;

string s[21];

string my_copy();
string my_add();
string addint(string s1, string s2);
string transstring(string tmp);
int transint(string tmp);
int checkint(string ss);
int my_find();
int my_rfind();
void my_insert();
void my_reset();
void my_print();
void my_printall(int n);

int main()
{
    string command;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    while (1)
    {
        cin >> command;
        if (command == "over")
            break;
        if (command == "copy")
            my_copy();
        else if (command == "add")
            my_add();
        else if (command == "find")
            my_find();
        else if (command == "rfind")
            my_rfind();
        else if (command == "insert")
            my_insert();
        else if (command == "reset")
            my_reset();
        else if (command == "print")
            my_print();
        else if (command == "printall")
            my_printall(n);
    }
    int j=0;
    for(int i=1; i<100000; i++){
        j=i+j;
    }
    for(int i=1; i<100000; i++){
        j=i+j;
    }
    for(int i=1; i<100000; i++){
        j=i+j;
    }
    for(int i=1; i<100000; i++){
        j=i+j;
    }
    for(int i=1; i<100000; i++){
        j=i+j;
    }
    for(int i=1; i<100000; i++){
        j=i+j;
    }
    vector<int> myv;
    for(int i=1; i<1000; i++){
        myv.push_back(j);
        j=i+j;
    }
    return 0;
}
string my_copy()
{
    int N[3];
    string tmp;
    for (int i = 0; i < 3; i++)
    {
        cin >> tmp;
        N[i] = transint(tmp);
    }
    return s[N[0]].substr(N[1],N[2]);
}
string my_add()
{
    string tmp, s[2];
    for (int i = 0; i < 2; i++)
    {
        cin >> tmp;
        s[i] = transstring(tmp);
    }
    if (checkint(s[0]) && checkint(s[1]))
        return addint(s[0], s[1]);
    return s[0]+s[1];
}
string addint(string s1, string s2)
{
    int i1 = atoi(s1.c_str());
    int i2 = atoi(s2.c_str());
    int k = i1 + i2;
    string ss;
    stringstream strm;
    strm << k;
    strm >> ss;
    return ss;
}
string transstring(string tmp)
{
    if (tmp == "copy")
        return my_copy();
    else if (tmp == "add")
        return my_add();
    else
        return tmp;
}
int transint(string tmp)
{
    if (tmp == "find")
        return my_find();
    else if (tmp == "rfind")
        return my_rfind();
    else
        return tmp[0]-'0';
}
int checkint(string ss)
{
    if (ss.size() > 5)
        return 0;
    for (int i = 0; i < ss.size(); i++)
        if (ss[i] > '9' || ss[i] < '0')
            return 0;
    return 1;
}
int my_find()
{
    string tmp,sn;
    int N;
    cin >> tmp;
    sn = transstring(tmp);
    cin >> tmp;
    N = transint(tmp);
    int k = s[N].find(sn);
    if (k == string::npos)
        return s[N].size();
    return k;
}
int my_rfind()
{
    string tmp,sn;
    int N;
    cin >> tmp;
    sn = transstring(tmp);
    cin >> tmp;
    N = transint(tmp);
    int k = s[N].rfind(sn);
    if (k == string::npos)
        return s[N].size();
    return k;
}
void my_insert()
{
    string sn,tmp;
    int N[2];
    cin >> tmp;
    sn = transstring(tmp);
    for (int i = 0; i < 2; i++)
    {
        cin >> tmp;
        N[i] = transint(tmp);
    }
    s[N[0]].insert(N[1], sn);
}
void my_reset()
{
    string tmp, sn;
    int N;
    cin >> tmp;
    sn = transstring(tmp);
    cin >> tmp;
    N = transint(tmp);
    s[N] = sn;
}
void my_print()
{
    string tmp;
    int N;
    cin >> tmp;
    N = transint(tmp);
    cout << s[N] << endl;
}
void my_printall(int n)
{
    for (int i = 1; i <= n; i++)
        cout << s[i] << endl;
}
