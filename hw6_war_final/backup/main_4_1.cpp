#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <stdio.h>

using namespace std;
/*Useful tips
cout << "Memory location " << warr_list_str << " in file " << __FILE__ << " line " << __LINE__
     << " @ " <<  __TIMESTAMP__<< endl;//__TIME__ << __DATE__ << __STDC__  */
//Const definition

const int REDFLAG  = 0;
const int BLUEFLAG = 1;
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
const char* warr_name_set[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};//Use map
const char* army_name_set[2] = {"red","blue"};

int hour, minute,cishu;
int n_total_city;

void PrintClock(void) { 
    printf("%03d:%02d ",hour,minute);
    cishu++;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////Declaration/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class Engine;
/*Class declaration====================Myclock============================ 
class Myclock {
  int hour, minute;
  public:
    Myclock() { hour = 0; minute=0; }
    ~Myclock() { }
    void NextClock(void);
    void PrintClock(void);
    friend class Engine;//::Init();
};*/


//Class declaration====================Weapons============================
class Weapons {
  public:
    string weapon_name;
    int force;
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


//Class declaration=====================Warriors==========================
class Warriors {
  public:
     //int n_warriors[5];//={dragon,ninja,iceman,lion,wolf};
     int armyname;
     int warrior_name;
     int warriorname;
     int id;
     int element;
     int force;
     Warriors(void);//no use
     Warriors(int warr_name_, int armyname_, int num_total_warrior_);
     Weapons weapon_list_str[2];//={sword,bomb,arrow};
	 
     //Warriors(const Warriors&){ n_warriors=0; }
     static void SetUp(int* warr_strength_, int* warr_attack_);
     virtual ~Warriors(void);
     virtual void Born(string armyname_,int num_total_warrior_, int M_)=0; 
     virtual void Property();//int num_total_warrior_, int M_);
     virtual int WhatsMyName()=0;
     //friend Engine;
};

class WDragon: public Warriors {
  public:
    int warrior_name;
    static int warrior_strength;
    static int warrior_attack;
    float morale;
    WDragon(){}//int strength_, int attack_);
    WDragon(int arymname_, int num_total_warrior_, int M_);
    virtual ~WDragon(){}
    virtual void Born(string armyname_,int num_total_warrior_, int M_);
    virtual void Property();//(int num_total_warrior_, int M_);
    virtual int WhatsMyName(){ return warrior_name; }
}; 

class WNinja: public Warriors {
  public:
    static int warrior_name;
    static int warrior_strength;
    static int warrior_attack;
    WNinja(int armyname_, int num_total_warrior_, int M_);//int strength_, int attack_);
    virtual ~WNinja(){}
    virtual void Born(string armyname_,int num_total_warrior_, int M_);
    virtual void Property();//(int num_total_warrior_, int M_);
     virtual int WhatsMyName(){ return warrior_name; }
};

class WIceman: public Warriors {
  public: 
    static int warrior_name;
    static int warrior_strength;
    static int warrior_attack;
    WIceman(int armyname_, int num_total_warrior_, int M_);//nt strength_, int attack_);
    virtual ~WIceman(){}
    virtual void Born(string armyname_,int num_total_warrior_, int M_);
    virtual void Property();//(int num_total_warrior_, int M_);
     virtual int WhatsMyName(){ return warrior_name; }
}; 

class WLion: public Warriors {
  public:
    int loyalty;
    static int warrior_name;
    static int warrior_strength;
    static int warrior_attack;
    WLion(int armyname_, int num_total_warrior_, int M_);//int strength_, int attack_);
    virtual ~WLion(){}
    virtual void Born(string armyname_,int num_total_warrior_, int M_);
    virtual void Property();//(int num_total_warrior_, int M_);
     virtual int WhatsMyName(){ return warrior_name; }
}; 

class WWolf: public Warriors {
  public:
    static int warrior_name;
    static int warrior_strength;
    static int warrior_attack;
    WWolf(int armyname_, int num_total_warrior_, int M_);//int strength_, int attack_);
    virtual ~WWolf(){}
    virtual void Born(string armyname_,int num_total_warrior_, int M_);
	//virtual void Property(int num_total_warrior_, int M_){}
     virtual int WhatsMyName(){ return warrior_name; }
}; 

int WDragon::warrior_strength = 1;  
int WNinja::warrior_strength  = 1;
int WIceman::warrior_strength = 1;
int WLion::warrior_strength = 1;
int WWolf::warrior_strength = 1;  
int WDragon::warrior_attack = 1;  
int WNinja::warrior_attack  = 1;
int WIceman::warrior_attack = 1;
int WLion::warrior_attack = 1;
int WWolf::warrior_attack = 1;  
int WDragon::warrior_name = 0;// "dragon";
int WNinja::warrior_name  = 1;//"ninja";
int WIceman::warrior_name = 2;//"iceman";
int WLion::warrior_name = 3;//"lion";
int WWolf::warrior_name = 4;//"wolf";

//Class declaration====================Headquarters====================== 
class Headquarters {
  private:
      int head_name; 
      //Warriors*  warr_list_str[5];//={dragon,ninja,iceman,lion,wolf};
      int n_total_warriors;
      int *strength;
      int order_counter;
      int sequence_num;
      static int end_produce;
  public:
      int M;
      vector<Warriors*> warr_v;
      int n_warriors[5];//={dragon,ninja,iceman,lion,wolf};
      int each_warrior_strength[5]; 
      Headquarters(string armyname_, int num_, int M_, int* strength_);
      ~Headquarters(){
         //for(int i=0; i<5; i++)     delete warr_list_str[i];//strength
      }
      static int NotEnd() { return !end_produce; }
      Warriors* Produce(); 
      //void EarnM(int M_); 
      void ReportWeapons();
      friend class Engine;
};


//Class declaration====================Cities============================ 
class Cities {
  public:
      int city_id;
      int city_M;
      int flag_color;//2 no, 0 red, 1 blue
      Warriors* warr[2];
      int last_win; 
      //vector<Warriors*> warr_in_city_v;
      Cities(int city_id_);
      ~Cities(){}
      void March(Cities* next_city, int army_){
          warr[army_] = next_city->warr[army_];
      }
      void Print_march_log() ;
};

Cities::Cities(int city_id_){ 
    city_id = city_id_;
    flag_color=2; 
    warr[0]=warr[1]=NULL;
    city_M=0;
}

void Cities::Print_march_log() {
  for(int i=0; i < 2; i++) {
     if(warr[i]!=NULL) {
           PrintClock();
           cout << army_name_set[warr[i]->armyname] << " " << warr_name_set[warr[i]->warriorname] << " " << warr[i]->id
                << " marched to city " << city_id << " with " <<  warr[i]->element << " elements and force " << warr[i]->force << endl;
     }
  } 
}

//Class declaration====================Engine======= 
class Engine{
  public:
      vector<Cities*> city_v;    
      Engine();
      void Init(int M, int R, int K, int T, int* warr_strength_, int* warr_attack); 
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////    CLASS   DEFINITION  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//Class definition====================Weapons============================ 

//Class definition====================Warriors=========================== 
Warriors::Warriors(){}
Warriors::Warriors(int warrior_name_, int armyname_, int num_total_warrior_){
    //for(int i=0; i<5; i++) n_warriors[i]=0; 
    armyname = armyname_;
    warriorname = warrior_name_;
    id = num_total_warrior_;
    weapon_list_str[0]= new Sword ();
    weapon_list_str[1]= new Bomb ();
    weapon_list_str[2]= new Arrow ();
    PrintClock();
    cout << army_name_set[armyname] << " " << warr_name_set[warriorname] 
         << " " << id << " born" << endl;
}
Warriors::~Warriors(void) { //for(int i=0; i<3; i++)  delete weapon_list_str[i]; 
}

void Warriors::SetUp(int* warr_strength_, int* warr_attack_) {
    WDragon::warrior_strength= warr_strength_[0];
    WNinja::warrior_strength = warr_strength_[1]; 
    WIceman::warrior_strength= warr_strength_[2];   
    WLion::warrior_strength  = warr_strength_[3];     
    WWolf::warrior_strength  = warr_strength_[4];  
    WDragon::warrior_attack  = warr_attack_[0];
    WNinja::warrior_attack   = warr_attack_[1]; 
    WIceman::warrior_attack  = warr_attack_[2];   
    WLion::warrior_attack    = warr_attack_[3];     
    WWolf::warrior_attack    = warr_attack_[4];  
}

WDragon::WDragon(int armyname_, int num_total_warrior_, int M_):Warriors(warrior_name, armyname_, num_total_warrior_){
    element = warrior_strength; 
    force = warrior_attack;
    morale=((float)M_/(float)WDragon::warrior_strength);
    cout << "Its morale is ";
    printf("%.2f", morale);//convert to cout
    cout  << endl;
}
WNinja::WNinja(int armyname_, int num_total_warrior_, int M_):Warriors(warrior_name,armyname_, num_total_warrior_){
    element = warrior_strength; 
    force = warrior_attack;
}  
WIceman::WIceman(int armyname_, int num_total_warrior_, int M_):Warriors(warrior_name,armyname_, num_total_warrior_){
    element = warrior_strength; 
    force = warrior_attack;
}
WLion::WLion(int armyname_, int num_total_warrior_, int M_):Warriors(warrior_name,armyname_, num_total_warrior_){
    element = warrior_strength; 
    force = warrior_attack;
    loyalty=M_;
    cout << "Its loyalty is " << loyalty << endl;
}  
WWolf::WWolf(int armyname_, int num_total_warrior_, int M_):Warriors(warrior_name,armyname_, num_total_warrior_){
    element = warrior_strength; 
    force = warrior_attack;
}  



void Warriors::Property(){}//(int num_total_warrior_, int M_){} 

//Class definition====================Dragon
void WDragon::Property(){//(int num_total_warrior_, int M_){
      cout << weapon_list_str[id%3]->weapon_name << endl;
     // printf("%.2f",((float)M_/(float)WDragon::warrior_strength));
}

//如何实现virtual的扩展功能？可以统统在基类n_warriors++
void WDragon::Born(string armyname_,int num_total_warrior_, int M_){}
void WNinja::Born(string armyname_,int num_total_warrior_, int M_){}
void WIceman::Born(string armyname_,int num_total_warrior_, int M_){}
void WLion::Born(string armyname_,int num_total_warrior_, int M_){}
void WWolf::Born(string armyname_,int num_total_warrior_, int M_){}
//Class definition====================Ninja
void  WNinja::Property(){//(int num_total_warrior_, int M_){
      cout <<  weapon_list_str[id%3]->weapon_name << endl;
	 // << " and a " << weapon_list_str[(num_total_warrior_+1)%3]->weapon_name << endl;
    }

//Class definition====================Iceman
void WIceman::Property(){//int num_total_warrior_, int M_){
    cout << weapon_list_str[id%3]->weapon_name  << endl;
}

//Class definition====================Lion
void WLion::Property(){//int num_total_warrior_, int M_){
    cout << "no weapon"  << endl;
}

//Class definition====================Wolf

//Class definition====================Headquarters=======================  
Headquarters::Headquarters(string armyname_, int num_, int M_, int* strength_){ 
    sequence_num = num_; 
    head_name = num_-1;
    M = M_;
    strength = strength_;
    order_counter = n_total_warriors=0;
    warr_v.reserve(20);
    for(int i=0; i<5; i++) n_warriors[i]=0; 
   //warr_list_str[0]= new WDragon();  
   //warr_list_str[1]= new WNinja ();
   //warr_list_str[2]= new WIceman();
   //warr_list_str[3]= new WLion  ();
   //warr_list_str[4]= new WWolf  ();
}

Warriors* Headquarters::Produce() {
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
      int warr_id=ORDER[sequence_num][order_counter];
      M=M-strength[warr_id];
      //需用工厂模式
      switch(warr_id){
          case(0): warr_v.push_back( new WDragon(head_name, ++n_total_warriors, M)); break; 
          case(1): warr_v.push_back( new WNinja (head_name, ++n_total_warriors, M)); break;
          case(2): warr_v.push_back( new WIceman(head_name, ++n_total_warriors, M)); break; 
          case(3): warr_v.push_back( new WLion  (head_name, ++n_total_warriors, M)); break; 
          case(4): warr_v.push_back( new WWolf  (head_name, ++n_total_warriors, M)); break;   
          default: cout << "Error Warrior Name" << endl;
      }
      n_warriors[warr_id]++;//each warrior group
      order_counter=(++order_counter)%5;
      return warr_v.back();
  }
}

void Headquarters::ReportWeapons() {
   // for(vector<Warriors*>::iterator it = warr_v.begin(); it != warr_v.end(); ++it){
   int warr_in_hand=warr_v.size();
   if(head_name == 0) {
      for(vector<Warriors*>::iterator it = warr_v.begin(); it != warr_v.end(); ++it){
          PrintClock(); cout << "red " << warr_name_set[(*it)->WhatsMyName()] << " " << (*it)->id << " has "; (*it)->Property();
      }
   }
   else if(head_name == 1){
      for(vector<Warriors*>::iterator it = warr_v.end()-1; it >= warr_v.begin(); --it){
          PrintClock(); cout << "blue " << warr_name_set[(*it)->WhatsMyName()] << " " << (*it)->id << " has "; (*it)->Property();
      }
   } 
   else cout << "Error" << endl;
} 
//Class definition====================Engine============================= 
Engine::Engine() {  }//myclock = NULL; }

void Engine::Init(int M, int R, int K, int T, int* warr_strength_, int* warr_attack_) { 
    Headquarters RedArmy ("red", 1, M, warr_strength_);
    Headquarters BlueArmy("blue", 2, M, warr_strength_);  
    Warriors::SetUp(warr_strength_, warr_attack_);
    city_v.reserve(n_total_city);
    for(int i = 0; i<= n_total_city + 1; i++){//0 is red headquarter, N+1 is blue headquarter;
        city_v.push_back( new Cities(i) );    
    }    
    int dead_loop=T; //Prevent dead loop
    //while((RedArmy.NotEnd()||BlueArmy.NotEnd())&&(dead_loop--)){
    while((Headquarters::NotEnd())&&(dead_loop--)){
        switch(minute){
		    case(0): {//Warriors Born 
			    city_v[0]->warr[0]=RedArmy.Produce();
                            city_v[n_total_city+1]->warr[1]=BlueArmy.Produce();
 		      break;
		    }
		    case(5): {//lions runaway
			    //cout << 
 		      break;
		    }
		    case(10): {//Marching
 			    //cout << sizeof(city_v.front())<<" --" << endl;
			    //for (vector<Cities*>::iterator it = city_v.begin(); it != city_v.end(); ++it)
			    for (int i=n_total_city+1; i > 0; i--)//red
     			        city_v[i]->March(city_v[i-1],0);
			    for (int i=0; i< n_total_city + 1; i++)//blue
     			        city_v[i]->March(city_v[i+1],1);
			    for (int i=1; i< n_total_city + 1; i++)
                                city_v[i]->Print_march_log();
 		      break;
		    }
		    case(20): {//City prosperous
			    for (int i=1; i< n_total_city + 1; i++)
                                city_v[i]->city_M+=10;
 		      break;
		    }
		    case(30): {//Earn elements
			    for (int i=1; i< n_total_city + 1; i++){
                                if(city_v[i]->warr[0]!=NULL && city_v[i]->warr[1]==NULL){ 
					RedArmy.M+=(city_v[i]->city_M); 
					PrintClock();
					cout<< "red " << warr_name_set[city_v[i]->warr[0]->warriorname] <<" "<< city_v[i]->warr[0]->id 
                                            << " earned "<< city_v[i]->city_M << " elements for his headquarter" << endl;
				 }
                                if(city_v[i]->warr[1]!=NULL && city_v[i]->warr[0]==NULL){ 
					BlueArmy.M+=(city_v[i]->city_M); 
					PrintClock();
					cout<< "blue " << warr_name_set[city_v[i]->warr[1]->warriorname] <<" "<< city_v[i]->warr[1]->id 
                                            << " earned "<< city_v[i]->city_M << " elements for his headquarter"<< endl;
				}
			    }           
 		      break;
		    }
		    case(35): {//Arrow shooting
 		      break;
		    }
		    case(38): {//Bombing
 		      break;
		    }
		    case(40): {//Attack & Fight_back & Yelling & Earn_elements
 		      break;
		    }
		    case(50): {//Report Headquarters M
			    PrintClock(); cout<< RedArmy.M << " elements in red headquarter" << endl; 
			    PrintClock(); cout<< BlueArmy.M << " elements in blue headquarter" << endl; 
 		      break;
		    }
	            case(55): {//Report Weapons utilization
 			    RedArmy.ReportWeapons();
 			    BlueArmy.ReportWeapons();
 		      break;
		    }
		    default: {//
 		      break;
		    }
        }
        minute++;
        if(minute==60) { hour++; minute=0;}
    }
    //delete myclock;
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
 int warr_strength[5]; 
 int warr_attack[5]; 
 queue<int> Mvalues, Nvalues, Rvalues, Kvalues, Tvalues;  //Store input data
 queue<int> Wvalues;
 queue<int> Avalues;
 cout << endl<<endl<<endl;
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
    cout << "Case " << round+1 << ":" << endl;
    for (int i=0;i<5;i++) {
      warr_strength[i]=Wvalues.front();
      warr_attack[i]=Avalues.front();
      Wvalues.pop();
      Avalues.pop();
    }
    hour=minute=cishu=0;
    n_total_city=Nvalues.front();
    myengine.Init(Mvalues.front(), Rvalues.front(), Kvalues.front(), Tvalues.front(), warr_strength, warr_attack);

    Mvalues.pop();
    Nvalues.pop();
    Rvalues.pop();
    Kvalues.pop();
    Tvalues.pop();
    cout << "TOTAL " << cishu << endl;      
}
 cout << endl<<endl<<endl;
 return 0;
}
