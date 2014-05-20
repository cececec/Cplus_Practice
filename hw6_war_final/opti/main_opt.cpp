#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <queue>
using namespace std;
//Const definition
int n_case;
const int REDFLAG  = 0;
const int BLUEFLAG = 1;
const int NOCOLOR  = 1;
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
int g_R;//Arrow force
int g_K;//Lion loyalty impact
int g_strength[5];
int g_attack[5];
////////////////////////////////////////////////////////////////////////////////
////////////////////////////Declaration/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class Engine;

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
    Sword(int force_):Weapons("sword") { force=force_; }
    virtual ~Sword(){}
};

class Bomb:  public Weapons{
  public:
    Bomb():Weapons("bomb"){}
    virtual ~Bomb(){}
};

class Arrow: public Weapons{
  public:
    int n_arrow;
    Arrow( ):Weapons("arrow"){ n_arrow=3; }
    virtual ~Arrow(){}
};


//Class declaration=====================Warriors==========================
class Warriors {
  public:
     //int n_warriors[5];//={dragon,ninja,iceman,lion,wolf};
     int armyname;
     int warriorname;
     int id;
     int element;
     int force;
     Warriors(void);//no use
     Warriors(int warr_name_, int armyname_, int num_total_warrior_);
     Weapons* arsenal[3];//={sword,bomb,arrow};
     //static void SetUp(int* warr_strength_, int* warr_attack_);
     //friend class Engine;
     virtual ~Warriors(void);
     virtual void Property();//int num_total_warrior_, int M_);
     virtual int Attack(Warriors* beatee, int city_id, int city_M_);
     virtual int Hurted(Warriors* beater, bool fightback);
     virtual int Killed(Warriors* beater, int city_id, int city_M_);
     virtual int FightBack(Warriors* beatee, int city_id, int city_M_);
     virtual int EarnElements(int city_id, int city_M_);
     virtual void PickUp(Warriors* beater, Warriors* beatee);
     virtual int Bombing(Warriors* beater, Warriors* beatee);
     virtual void Yelling(int city_id);
};
class WDragon: public Warriors {
  public:
    double morale;
    WDragon(){}//int strength_, int attack_);
    WDragon(int arymname_, int num_total_warrior_, int M_);
    virtual ~WDragon(){}
    virtual void Property();//(int num_total_warrior_, int M_);
};

class WNinja: public Warriors {
  public:
    WNinja(int armyname_, int num_total_warrior_, int M_);//int strength_, int attack_);
    virtual ~WNinja(){}
    virtual void Property();//(int num_total_warrior_, int M_);
};

class WIceman: public Warriors {
  public:
    int n_move;//element and force change every two step made
    WIceman(int armyname_, int num_total_warrior_, int M_);//nt strength_, int attack_);
    virtual ~WIceman(){}
    virtual void Property();//(int num_total_warrior_, int M_);
};

class WLion: public Warriors {
  public:
    int loyalty;
    WLion(int armyname_, int num_total_warrior_, int M_);//int strength_, int attack_);
    virtual ~WLion(){}
    virtual void Property();//(int num_total_warrior_, int M_);
};

class WWolf: public Warriors {
  public:
    WWolf(int armyname_, int num_total_warrior_, int M_);//int strength_, int attack_);
    virtual ~WWolf(){}
    void Property();
};
//Class declaration====================Headquarters====================== 
class Headquarters {
  private:
      int armyname;
      //Warriors*  warr_list_str[5];//={dragon,ninja,iceman,lion,wolf};
      int n_total_warriors;
      int order_counter;
      int sequence_num;
  public:
      int M;
      vector<Warriors*> warr_v;
      int n_warriors[5];//={dragon,ninja,iceman,lion,wolf};
      int each_warrior_strength[5];
      Headquarters(string armyname_, int num_, int M_);
      ~Headquarters(){
         //for(int i=0; i<5; i++)     delete warr_list_str[i];//strength
      }
      Warriors* Produce();
      void ReportWeapons();
      friend class Engine;
};


//Class declaration====================Cities============================ 
class Cities {
  public:
      int city_id;
      int city_M;
      int enemy_num;
      int flag_color;//2 no, 0 red, 1 blue
      Warriors* warr[2];
      int last_win;
      //vector<Warriors*> warr_in_city_v;
      Cities(int city_id_);
      ~Cities(){}
      void March(Cities* next_city, int armyname_);
      void Print_march_log();
      int Occupied();
      int Shooting(Cities* next_city, int armyname_);
};


//Class declaration====================Engine======= 
class Engine{
  public:
      vector<Cities*> city_v;
      Engine();
      void Init(int M, int T);
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////    CLASS   DEFINITION  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//Class definition====================Weapons============================ 

//Class definition====================Warriors=========================== 

//Class definition====================Dragon
//Class definition====================Ninja
//Class definition====================Iceman
//Class definition====================Lion
//Class definition====================Wolf
//Class definition====================Headquarters======================= }
//Class definition====================Engine============================= 

////////////////////////////////////////////////////////////////////////////////
////////////////////////////        MAIN         ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//Static members definition

int main() {
 int n_test_case;
 int round;
 int M_element, N_city, R_arrow_force, K_lion_loyalty_dec, T_time_length;  //First row in one case
 int init_strength;  //Second row in one case
 int A_attack;  //Third row in one case
 queue<int> Mvalues, Nvalues, Rvalues, Kvalues, Tvalues;  //Store input data
 queue<int> Wvalues;
 queue<int> Avalues;
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
//////////////////////OUTPUT//////////////////////// 
  for(round=0;round!=n_test_case;round++){
    Engine myengine;n_case=round+1;
    cout << "Case " << round+1 << ":" << endl;
    for (int i=0;i<5;i++) {
      g_strength[i]=Wvalues.front();
      g_attack[i]=Avalues.front();
      Wvalues.pop();
      Avalues.pop();
    }
    hour=minute=cishu=0;
    n_total_city=Nvalues.front();
    g_R = Rvalues.front();
    g_K = Kvalues.front();

    myengine.Init(Mvalues.front(), Tvalues.front());
    Mvalues.pop();
    Nvalues.pop();
    Rvalues.pop();
    Kvalues.pop();
    Tvalues.pop();
}
 return 0;
}
                                
