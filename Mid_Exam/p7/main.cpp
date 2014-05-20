#include <iostream>
#include <set>
using namespace std;
// 在此处补充你的代码

template<class PT>
void MyPrint(PT first, PT last){
    PT tmp = first;
    
    while(tmp != last){
        cout << *tmp << " ";
        ++tmp;
    }

}

template<class T, class Prep = less<int> >
class MySet{
  public:
    set<T,Prep> myset;
    MySet(){ }//myset.clear();  }   
    template<class C>//Container type// or just int
    MySet(C first, C last) { C tmp = first; while (tmp != last){ myset.insert(*tmp); ++tmp; } }
   
    class iterator{
        typename set<T>::iterator iter;
        public:
            iterator(){ }
            iterator(typename set<T>::iterator x):iter(x) { }
            void operator=(typename set<T>::iterator x){ iter=x; }
            bool operator!=(iterator sec){ return iter!=sec.iter; }
            const T operator*() {return *iter;}
            iterator& operator++() {++iter;return *this;}
            
        
    };
    
    iterator upper_bound(double w) { return myset.upper_bound(w);}
    
    pair<iterator,iterator> FindInterval(T low, T top)
    {
        iterator ilow, itop;
        ilow = myset.upper_bound(low);
        itop = myset.lower_bound(top)--;
        pair<iterator, iterator> tmp(ilow,itop);
        return (tmp);
    }
    
    void insert(T val){
        myset.insert(val);
        //MyPrint(myset.begin(), myset.end());
    }
    
    iterator begin(){ return myset.begin(); }   //copy-constructor                                                                                                                 
    iterator end(){ return myset.end(); }
};



int main()
{
    int t;
    cin >> t;
    MySet<int> stInt;
    int a[100];
    while(t--) {
        int n;
        cin >> n;
        for(int i = 0;i < n; ++i )
            cin >> a[i];
        MySet<int> stInt(a,a+n);
        MyPrint(stInt.begin(),stInt.end()); //输出全部内容
        cout << endl;
        int s,e;
        cin >> s >> e; // 后面要输出位于 s 和 e 之间的元素
        pair<MySet<int>::iterator, MySet<int>::iterator> p;
        p  = stInt.FindInterval(s,e);
        if( p.first != p.second) {
            MyPrint(p.first,p.second);
            cout << endl;
        }
        else
            cout << "Interval Not Found" << endl;
        cin >> n;
        MySet<double,greater<double> > stDouble;
        for( int i = 0;i < n; ++i)  {
            double d;
            cin >> d;
            stDouble.insert(d);
        }
        MyPrint(stDouble.begin(),stDouble.end());
        cout << endl;
        double w;
        cin >> w;
        cout << * stDouble.upper_bound(w) << endl;
    }
}
