#include <iostream>
#include <string>
using namespace std;
template <class T>
class CMyistream_iterator
{
    T item;
    public:
// 在此处补充你的代码
    CMyistream_iterator(istream & i){ i >> item; }

   friend T& operator*(CMyistream_iterator& obj){
        return obj.item;
    }
    
    void operator++(int){
        cin>>item;
    }
};
//template<class T>
//void operator++(int){ obj++; }
    

int main()  
{ 
	 
	 int t;
	 cin >> t;
	 while (t--) {
	 	 CMyistream_iterator<int> inputInt(cin);
		 int n1,n2,n3;
		 n1 = * inputInt;
		 int tmp = * inputInt; 
		 cout << tmp << endl;
		 inputInt ++;   
		 n2 = * inputInt; 
		 inputInt ++;   
		 n3 = * inputInt; 
		 cout << n1 << "," << n2<< "," << n3 << ",";
		 CMyistream_iterator<string> inputStr(cin);
		 string s1,s2;
		 s1 = * inputStr; 
		 inputStr ++;     
		 s2 = * inputStr; 
		 cout << s1 << "," << s2 << endl;
	}
	return 0;  
}
