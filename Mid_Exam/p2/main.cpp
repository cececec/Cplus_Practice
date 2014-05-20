#include <iostream>
#include <string>
using namespace std;


class A {
    int n;
    public:
    // 在此处补充你的代码
    A(int num){ n=num;}
   // A(A& a){ n=a.n;}
    int operator=(int num){
        n=num;
        return n;
    }
    friend ostream& operator<<(ostream& o, A a){
        return o << a.n ;
    }
    friend A& operator++(A& a){//pre-increment ++a1
        ++a.n;
        return a;
    }
    A operator++(int){//post-increment a1++
        A tmp=*this;
        ++n;
        return tmp;
    }
    
    friend static int Square(A a){
        return a.n*a.n;
    }
};

class B {
    private:
    static int k;
    static int Square(int n)
    {
        cout <<  "k=" << k <<endl;
        return n * n;
    }
    friend int main();
};
int B::k;

int main()
{
    A a1(1),a2(2);
    cout << a1++ << endl;
    (++a1) = 100;
    cout << a1 << endl;
    cout << ++ a1 << endl;
    cout << a1 << endl;
    int n;
    cin >> n;
    while( n --) {
        cin >> B::k;
        A a3(B::k);
        cout << B::Square(a3) << endl;
    }
    return 0;
}
/*1
100
101
101
k=3
9
k=4
16
k=5
25*/
