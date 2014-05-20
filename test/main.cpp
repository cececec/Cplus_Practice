#include <iostream>
#include <string>
using namespace std;


template <class T> 
class CArray3D {

public:

    class OneD{
            public:
            T* array3;
            OneD(T* arrayptr):array3(arrayptr){ 
            cout << "=======IN OneD constructor====" << endl; 
}
            int& operator[](int c){
               return array3[c]; 
            }
             friend ostream& operator<<(ostream& o, OneD&) {  return cout<<"";//??? 
             }
            
    };
        
        
        
    class TwoD{
            public:
             T** array2;
            OneD* first[]; 
            TwoD(T** arrayptr, int b_,int c_):array2(arrayptr){
            cout << "=======IN TwoD constructor====" << endl; 
                for(int i = 0; i < b_; ++i){
                    array2[i] = new T[c_];
                }
                 for(int i = 0; i < c_; ++i){
                    first[i] = new OneD(array2[i]);
                 }
            }
            OneD operator[](int b) {  return *first[b]; }

            friend ostream& operator<<(ostream& o, TwoD&) { return cout<<"";//??? 
            }
    };
               
        TwoD operator[](int a){            
            return *sec[a];
        }




    int a,b,c;//dimensions
    T*** array;
    TwoD* sec[];  
       CArray3D ( T three, T two, T one )  {
            a = three; b = two; c = one;
            array = new T**[a];
            cout << "=======IN CArray3D constructor====" << endl; 
            for(int i = 0; i < a; ++i){
                array[i] = new T*[b];//change to b    
            }
            for(int i = 0; i < b; ++i){
                 sec[i] = new TwoD(array[i],b,c);
            }
       }

       ~CArray3D( ) {       }    
        
        friend ostream& operator<<(ostream& o, CArray3D&) {  return cout<<"";//??? 
        } 


};

int main()

{
        CArray3D<int> a(3,4,5);
        int No = 0;
        
        for( int i = 0; i < 3; ++ i )
         for( int j = 0; j < 4; ++j )
          for( int k = 0; k < 5; ++k )
           //  a[i][j][k] = No ++;
             a[i][j][k] = No ++;
        
        for( int i = 0; i < 3; ++ i )
         for( int j = 0; j < 4; ++j )
           for( int k = 0; k < 5; ++k )
              cout << a[i][j][k] << ",";
    
    return 0;

}
