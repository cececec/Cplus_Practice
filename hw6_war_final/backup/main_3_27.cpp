#include <iostream>
#include <string>
#include <queue>
#include <stdio.h>

using namespace std;
//Const definition===================

const int RED    = 0;
const int BLUE   = 1;
const int DRAGON = 0;
const int NINJA  = 1;
const int ICEMAN = 2;
const int LION   = 3;
const int WOLF   = 4;
const int ORDER[3][5] = { {},{ICEMAN,LION,WOLF,NINJA,DRAGON} , {LION,DRAGON,NINJA,ICEMAN,WOLF} };
const int SWORD= 0;
const int BOMB = 1;
const int ARROW= 2;
const int WEAPON[3] = { SWORD,BOMB,ARROW };

////////////////////////////////////////////////////////////////////////////////
////////////////////////////Declaration/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class Engine;
//Class declaration======Myclock======= 
class Myclock {
  int hour, minute;
  public:
    Myclock() { hour = 0; minute=0; }
    ~Myclock() { }
    void NextClock(void);
    void PrintClock(void);
    friend class Engine;//::Init();
};

//Class declaration======Weapons=======
class Weapons {
  public:
    string weapon_name;
    Weapons(){}
    Weapons(string name):weapon_name(name){}
    virtual ~Weapons(){}
};

class Sword: public Weapons{
  public:
    Sword():Weapons("sword") {}
    virtual ~Sword(){}
    
};

class Bomb:  public Weapons{
  public:
    Bomb():Weapons("bomb"){}
    virtual ~Bomb(){}

};

class Arrow: public Weapons{
  public:
    Arrow():Weapons("arrow"){}
    virtual ~Arrow(){}

};

//Class declaration=======Warriors=====
class Warriors {
  public:
     string warrior_name;
     int n_warriors;
     int warrior_strength;
     Warriors();
     //Warriors(const Warriors&){ n_warriors=0; }
     virtual ~Warriors(){ 
         for(int i=0; i<3; i++)  delete weapon_list_str[i];
     }
     Weapons*  weapon_list_str[3];//={sword,bomb,arrow};
     void set_strength(int strength_) { warrior_strength=strength_;}
     void Born(string armyname_,int num_total_warrior_); 
     virtual void Property(int num_total_warrior_, int M);
     //friend Engine;
};



class WDragon: public Warriors {
  public:
    //float morale;
    WDragon(int strength_){warrior_name="dragon";warrior_strength=strength_;}
    virtual ~WDragon(){}
    //void Born(){ }
    virtual void Property(int num_total_warrior_, int M){
      cout << "It has a " << weapon_list_str[num_total_warrior_%3]->weapon_name << ",and it's morale is ";
      printf("%.2f",((float)M/(float)warrior_strength));
      cout  << endl;
    }
}; 

class WNinja: public Warriors {
  public:
    WNinja(int strength_){warrior_name="ninja";warrior_strength=strength_;}
    virtual ~WNinja(){}
    //void Born(){ }
    virtual void Property(int num_total_warrior_, int M){
      cout << "It has a " << weapon_list_str[num_total_warrior_%3]->weapon_name << " and a " << weapon_list_str[(num_total_warrior_+1)%3]->weapon_name << endl;
    }
};

class WIceman: public Warriors {
  public: 
    WIceman(int strength_){warrior_name="iceman";warrior_strength=strength_;}
    virtual ~WIceman(){}
    //void Born(){}
    virtual void Property(int num_total_warrior_, int M){
      cout << "It has a " << weapon_list_str[num_total_warrior_%3]->weapon_name  << endl;
    }
}; 

class WLion: public Warriors {
  public:
    WLion(int strength_){warrior_name="lion";warrior_strength=strength_;}
    virtual ~WLion(){}
    //void Born(){}
    virtual void Property(int num_total_warrior_, int M){
      cout << "It's loyalty is " << M << endl;
    }
}; 

class WWolf: public Warriors {
  public:
    WWolf(int strength_){warrior_name="wolf";warrior_strength=strength_;}
    virtual ~WWolf(){}
    //void Born(){}
}; 

//Class definition======Headquarters======= 
class Headquarters {
  private:
    int init_M_;//M life value [1,1000]
    string headquarter_name; 
    Warriors*  warr_list_str[5];//={dragon,ninja,iceman,lion,wolf};
    int n_total_warriors;
    int *strength;
    int order_counter;
    int sequence_num;
    static int end_produce;
  public:
    int M;
    int each_warrior_strength[5]; 
    Headquarters(string armyname_, int num_, int strength_[5]);
    //Headquarters(const Headquarters & otherhead ){ sequence_num=otherhead.sequence_num; headquarter_name=otherhead.headquarter_name; end_produce=order_counter=0;}
    ~Headquarters(){
       for(int i=0; i<5; i++)
           delete warr_list_str[i];
    }
    static int NotEnd() { return !end_produce; }
    void Produce(); 
    friend class Engined;
};

//Class definition======Myclock======= 
class Engine{
    public:
        //Myclock clock;
        Engine(){}
        void Init(int M, int N, int R, int K, int T, int warr_strength[], int warr_attack[]); 

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////MYCLOCK DEFINITION BEGIN////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Myclock::NextClock(void)  { 
       hour++;
 }

void Myclock::PrintClock(void) { 
    printf("%03d:%02d ",hour,minute);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////WEAPONS DEFINITION BEGIN///////////////////////////
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////WARRIORS DEFINITION BEGIN///////////////////////////
///////////////////////////////////////////////////////////////////////////////
Warriors::Warriors(){
   n_warriors=0; 
   weapon_list_str[0]= new Sword ();
   weapon_list_str[1]= new Bomb ();
   weapon_list_str[2]= new Arrow ();
}

void Warriors::Born(string armyname_,int num_total_warrior_){ 
  n_warriors++;
  cout << armyname_ << " " << warrior_name << " " << num_total_warrior_ 
       << " born" << endl;
       //<< " born with strength " << warrior_strength << "," << n_warriors 
       //<< " " << warrior_name << " in " << armyname_<< " headquarter" << endl; 
}
    
void Warriors::Property(int num_total_warrior_, int M){
  //cout << "error"<< endl;

} 

////////////////////////////////////////////////////////////////////////////////
////////////////////////////HEADQUARTERS DEFINITION BEGIN///////////////////////
////////////////////////////////////////////////////////////////////////////////

Headquarters::Headquarters(string armyname_, int num_, int strength_[5]){ 
   sequence_num=num_; headquarter_name=armyname_;
   warr_list_str[0]= new WDragon(strength_[0]);
   //cout << "Memory location " << warr_list_str << " in file " << __FILE__ << " line " << __LINE__
   //     << " @ " <<  __TIMESTAMP__<< endl;//__TIME__ << __DATE__ << __STDC__    
   warr_list_str[1]= new WNinja (strength_[1]);
   warr_list_str[2]= new WIceman(strength_[2]);
   warr_list_str[3]= new WLion  (strength_[3]);
   warr_list_str[4]= new WWolf  (strength_[4]);
   strength=strength_;
   order_counter=n_total_warriors=0;
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
    //cout << headquarter_name << " headquarter stops making warriors" <<endl;
    end_produce=1;
  }
  else {
    //cout << "Watcher 7 " << ORDER[sequence_num][order_counter] <<endl;
        warr_list_str[ ORDER[sequence_num][order_counter] ] -> Born(headquarter_name, ++n_total_warriors);  
        M=M-strength[ORDER[sequence_num][order_counter]];
        warr_list_str[ ORDER[sequence_num][order_counter] ] -> Property(n_total_warriors,M);  
    
    order_counter=(++order_counter)%5;
  }
}

void Engine::Init(int M, int N, int R, int K, int T, int warr_strength[], int warr_attack[]) { 
    //if(myclock!=NULL){delete myclock;}
    Myclock* myclock = new Myclock;    
    Headquarters RedArmy("red",1,warr_strength);
    Headquarters BlueArmy("blue",2,warr_strength);  
    RedArmy.M = BlueArmy.M = M;

    int dead_loop=10000; //Prevent dead loop
    //while((RedArmy.NotEnd()||BlueArmy.NotEnd())&&(dead_loop--)){
    while((Headquarters::NotEnd())&&(dead_loop--)){
        myclock->PrintClock();
        RedArmy.Produce();
        myclock->PrintClock();
        BlueArmy.Produce();
        
        myclock->NextClock();
    }
    delete myclock;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////        MAIN         ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//Static members definition
int Headquarters::end_produce=0;

int main() {
 int n_test_case;
 int round;
 int M_element, N_city, R_arrow_force, K_lion_loyalty_dec, T_time_length;  //First row in one case
 int init_strength;  //Second row in one case
 int A_attack;  //Third row in one case
 int warrior_strength[5]; 
 int warrior_attack[5]; 
 queue<int> Mvalues, Nvalues, Rvalues, Kvalues, Tvalues;  //Store input data
 queue<int> Wvalues;
 queue<int> Avalues;
 //Myclock *myclock=NULL;
//////////////////////SAVING INPUT//////////////////////// 
  cin >> n_test_case;
  for(round=0; round!=n_test_case; round++){
      cin >> M_element >> N_city >> R_arrow_force >> K_lion_loyalty_dec >> T_time_length;; 
      Mvalues.push(M_element);
      Nvalues.push(N_city);
      Rvalues.push(R_arrow_force);
      Kvalues.push(K_lion_loyalty_dec);
      Tvalues.push(T_time_length);
      for(int i=0; i<5; i++) {
          cin >> init_strength ;
          Wvalues.push(init_strength); 
      }
      for(int i=0; i<5; i++) {
          cin >> A_attack ;
          Avalues.push(A_attack); 
      }
  }
  Engine myengine;
//////////////////////OUTPUT//////////////////////// 
  for(round=0;round!=n_test_case;round++){
    cout << "Case:" << round+1 <<  endl;
    for (int i=0;i<5;i++) {
      warrior_strength[i]=Wvalues.front();
      warrior_attack[i]=Avalues.front();
      Wvalues.pop();
      Avalues.pop();
    }

    myengine.Init(Mvalues.front(), Nvalues.front(), Rvalues.front(), Kvalues.front(), Tvalues.front(), warrior_strength, warrior_attack);

    Mvalues.pop();
    Nvalues.pop();
    Rvalues.pop();
    Kvalues.pop();
    Tvalues.pop();
      
}
 //delete myclock;
 return 0;
}
