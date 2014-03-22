#include <iostream>
#include <string>
#include <queue>
#include <stdio.h>

using namespace std;
//Const definition===================

const int DRAGON = 0;
const int NINJA  = 1;
const int ICEMAN = 2;
const int LION   = 3;
const int WOLF   = 4;

const int ORDER[3][5] = { {},{ICEMAN,LION,WOLF,NINJA,DRAGON} , {LION,DRAGON,NINJA,ICEMAN,WOLF} };

//Class definition======Myclock======= 
class Myclock {
  int hour;
  
  public:
    Myclock() { hour = 0;}
    void NextClock(void)  { hour++; }
    void PrintClock(void) { printf("%03d ",hour);}
 

};


//Class definition=======Warriors====== 
class Warriors {
  private:
    
  public:
     

};


//Class definition=======Headquarters====== 
class Headquarters {
  private:
    int init_M_;//M life value [1,1000]
    string name; 
    // numbers of warriors respectively
    int n_dragon;
    int n_ninja;
    int n_iceman;
    int n_lion;
    int n_wolf;
   
    int n_warriors;
   
    int order_counter;
    int sequence_num;
    int end_produce;
  public:
    int M;
    int each_warrior_strength[5]; 
    Headquarters(string armyname, int num_){ sequence_num=num_; name=armyname; end_produce=order_counter=n_warriors=n_dragon=n_ninja=n_iceman=n_lion=n_wolf=0;}
    Headquarters(const Headquarters & otherhead ){ sequence_num=otherhead.sequence_num; name=otherhead.name; end_produce=order_counter=n_warriors=n_dragon=n_ninja=n_iceman=n_lion=n_wolf=0;}
    ~Headquarters(){};
    //static void SetM(int Mvalue){ init_M_ = Mvalue;}
    //static int WhatIsM() { return init_M_; }
    void PrintM() { cout << M <<endl; } 
    int NotEnd() { return !end_produce; }

    void Produce() {
      int j=0;
      //cout << "Test... M=" << M << " ORDER=" << ORDER[sequence_num][order_counter] << endl;
      while (( M<each_warrior_strength[ORDER[sequence_num][order_counter]] ) && j<5) {  
       //cout << j << " again... order_counter is "<< order_counter  <<endl;
        order_counter=(order_counter+1)%5;
        j++;
      }
      if ( j==5 ) {
        cout << name << " headquarter stops making warriors" <<endl;
        end_produce=1;
        return;
      }
      else {
        cout << name << " " ;
        switch( ORDER[sequence_num][order_counter]) {
          case(0): cout << "dragon " << ++n_warriors << " born with strength " << each_warrior_strength[0] << "," << ++n_dragon << " dragon "; break ; 
          case(1): cout << "ninja "  << ++n_warriors << " born with strength " << each_warrior_strength[1] << "," << ++n_ninja  << " ninja " ; break ;
          case(2): cout << "iceman " << ++n_warriors << " born with strength " << each_warrior_strength[2] << "," << ++n_iceman << " iceman "; break ;
          case(3): cout << "lion "   << ++n_warriors << " born with strength " << each_warrior_strength[3] << "," << ++n_lion   << " lion "  ; break ;
          case(4): cout << "wolf "   << ++n_warriors << " born with strength " << each_warrior_strength[4] << "," << ++n_wolf   << " wolf "  ; break ;
          default: cout << "Error ";
        }
        cout << "in " << name << " headquarter" << endl; 
        M=M-each_warrior_strength[ORDER[sequence_num][order_counter]];
        order_counter++;
        order_counter=order_counter%5;
        end_produce=0;
      }
    }
};

//static members have to be declared ahead of all 
//int Headquarters::init_M_=0;
//int Headquarters::each_warrior_strength[5]={0,0,0,0,0};


int main() {
 int test_case;
 int round;
 int tmpM,tmpM1,tmpM2,tmpM3,tmpM4,tmpM5;
 queue<int> Mvalues;
 queue<int> Wvalues;
 Myclock *myclock;
 
 cin >> test_case;
//Initiation
  for(round=0;round!=test_case;round++){
      cin >> tmpM; 
      cin >> tmpM1 >> tmpM2 >> tmpM3 >>tmpM4 >>tmpM5; 
      Mvalues.push(tmpM);
      Wvalues.push(tmpM1); Wvalues.push(tmpM2); Wvalues.push(tmpM3); Wvalues.push(tmpM4); Wvalues.push(tmpM5);

  }


  for(round=0;round!=test_case;round++){
    cout << "Case:" << round+1 <<  endl;
    // if(myclock){delete myclock;}
    myclock = new Myclock;    
    tmpM=Mvalues.front();
    //Mvalues.pop();
    //Headquarters::SetM(tmpM);
    
    //Instantiation
    Headquarters RedArmy("red",1), BlueArmy("blue",2);  
    RedArmy.M=BlueArmy.M=Mvalues.front(); Mvalues.pop();//Headquarters::WhatIsM(); 
    for (int i=0;i<5;i++) {
      RedArmy.each_warrior_strength[i]=Wvalues.front();
      BlueArmy.each_warrior_strength[i]=Wvalues.front();
      Wvalues.pop();
      //cout<< Headquarters::each_warrior_strength[i] << endl;
    }


    int dead_loop=1000; //Prevent dead loop


    while((RedArmy.NotEnd()||BlueArmy.NotEnd())&&(dead_loop--)){
      if (RedArmy.NotEnd()) {
        myclock->PrintClock();
        RedArmy.Produce();
      }
      if (BlueArmy.NotEnd()) {
        myclock->PrintClock();
        BlueArmy.Produce();
      } 

      //RedArmy.PrintM();    
      //BlueArmy.PrintM();
      myclock->NextClock();
    }
}
 //cout << "Done...!" << endl;
 return 0;
}
