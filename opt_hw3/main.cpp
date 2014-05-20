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

////////////////////////////////////////////////////////////////////////////////
////////////////////////////WARRIORS DEFINITION BEGIN///////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Warriors {
  public:
  string name;
  int n_warriors;
  int warrior_strength;
     Warriors(){ n_warriors=0; }
     Warriors(const Warriors&){ n_warriors=0; }
     virtual ~Warriors(){}
     void set_strength(int strength_) { warrior_strength=strength_;}
     void born(string armyname_,int num_total_warrior_); 
};

void Warriors::born(string armyname_,int num_total_warrior_){ 
  n_warriors++;
  cout << armyname_ << " " << name << " " << num_total_warrior_ << " born with strength " << warrior_strength << "," << n_warriors << " " << name << " in " << armyname_<< " headquarter" << endl;; 
}
    
class WDragon: public Warriors {
  public:
    WDragon(){name="dragon";}
    //~WDragon(){}
    //void born(){ }
}; 

class WNinja: public Warriors {
  public:
    WNinja(){name="ninja";}
    //~WNinja(){}
    //void born(){ }
};

class WIceman: public Warriors {
  public: 
    WIceman(){name="iceman";}
    //~WIceman(){}
    //void born(){}
}; 

class WLion: public Warriors {
  public:
    WLion(){name="lion";}
    //~WLion(){}
    //void born(){}
}; 

class WWolf: public Warriors {
  public:
    WWolf(){name="wolf";}
    //~WWolf(){}
    //void born(){}
}; 

////////////////////////////////////////////////////////////////////////////////
////////////////////////////WARRIORS DEFINITION END/////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////////////////////////////HEADQUARTERS DEFINITION BEGIN///////////////////////
////////////////////////////////////////////////////////////////////////////////
class Headquarters {
  private:
    int init_M_;//M life value [1,1000]
    string name; 
    Warriors*  warr_list_stri[5];//={dragon,ninja,iceman,lion,wolf};
    int n_total_warriors;
    int *strength;
    int order_counter;
    int sequence_num;
    int end_produce;
  public:
    int M;
    int each_warrior_strength[5]; 
    Headquarters(string armyname, int num_, int strength_[5]);
    //Headquarters(const Headquarters & otherhead ){ sequence_num=otherhead.sequence_num; name=otherhead.name; end_produce=order_counter=0;}
    ~Headquarters(){};
    int NotEnd() { return !end_produce; }
    void Produce(); 
};

Headquarters::Headquarters(string armyname, int num_, int strength_[5]){ 
   sequence_num=num_; name=armyname;
   warr_list_stri[0]= new WDragon();
   warr_list_stri[1]= new WNinja ();
   warr_list_stri[2]= new WIceman();
   warr_list_stri[3]= new WLion  ();
   warr_list_stri[4]= new WWolf  ();
   strength=strength_;
   for(int i=0;i<5;i++){
     warr_list_stri[i]->set_strength(strength[i]);
   }
   end_produce=order_counter=n_total_warriors=0;
}

void Headquarters::Produce() {
  int j=0;
  //cout << "Test... M=" << M << " ORDER=" << ORDER[sequence_num][order_counter] << endl;
  while (( M<strength[ORDER[sequence_num][order_counter]] ) && j<5) {  
    //cout << j << " again... order_counter is "<< order_counter  <<endl;
    order_counter=(order_counter+1)%5;
    j++;
  }
  if ( j==5 ) {
    cout << name << " headquarter stops making warriors" <<endl;
    end_produce=1;
  }
  else {
    //cout << "Watcher 7 " << ORDER[sequence_num][order_counter] <<endl;
    warr_list_stri[ ORDER[sequence_num][order_counter] ] -> born(name, ++n_total_warriors);  
    M=M-strength[ORDER[sequence_num][order_counter]];
    order_counter=(++order_counter)%5;
    end_produce=0;
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////HEADQUARTERS DEFINITION END/////////////////////////
////////////////////////////////////////////////////////////////////////////////


int main() {
 int n_test_case;
 int round;
 int tmpM,in_strength;
 queue<int> Mvalues, Wvalues;  //Store input data
 Myclock *myclock;
 int warrior_strength[5]; 
//////////////////////INPUT//////////////////////// 
 cin >> n_test_case;
  for(round=0;round!=n_test_case;round++){
      cin >> tmpM; 
      Mvalues.push(tmpM);
      for(int i=0;i<5;i++){
      cin >> in_strength ;
      Wvalues.push(in_strength); 
      }
  }

//////////////////////OUTPUT//////////////////////// 
  for(round=0;round!=n_test_case;round++){
    cout << "Case:" << round+1 <<  endl;
    //if(myclock){delete myclock;}
    myclock = new Myclock;    
    
//////////////////////Instantiation//////////////////////// 
    for (int i=0;i<5;i++) {
      warrior_strength[i]=Wvalues.front();
      Wvalues.pop();
    }
    Headquarters RedArmy("red",1,warrior_strength), BlueArmy("blue",2,warrior_strength);  
    RedArmy.M=BlueArmy.M=Mvalues.front();Mvalues.pop();
      


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

      myclock->NextClock();
    }
}
 return 0;
}
