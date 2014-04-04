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
    float morale;
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
      static int end_produce;
  public:
      int M;
      vector<Warriors*> warr_v;
      int n_warriors[5];//={dragon,ninja,iceman,lion,wolf};
      int each_warrior_strength[5]; 
      Headquarters(string armyname_, int num_, int M_);
      ~Headquarters(){
         //for(int i=0; i<5; i++)     delete warr_list_str[i];//strength
      }
      static int NotEnd() { return !end_produce; }
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

Cities::Cities(int city_id_){ 
      city_id = city_id_;
      flag_color=2; 
      warr[0]=warr[1]=NULL;
      city_M=0;
      last_win=2;
      enemy_num=0;
}

void Cities::March(Cities* next_city, int armyname_){
      warr[armyname_] = next_city->warr[armyname_];
      if(warr[armyname_]!=NULL && warr[armyname_]->warriorname==ICEMAN)  {
           ((WIceman*)warr[armyname_])->n_move+=1;
           if(((WIceman*)warr[armyname_])->n_move==2){
              warr[armyname_]->element-=9; warr[armyname_]->force+=20;
              ((WIceman*)warr[armyname_])->n_move=0;
              if(warr[armyname_]->element<=0) warr[armyname_]->element=1;//won't die from walking  
           }
      }
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

int Cities::Occupied()
{
    int e;
    if (city_id==0) e=1;//enemy
    else e=0;
         if( warr[e]!=NULL ){
             if(enemy_num==0){//first enemy arrived
                PrintClock(); cout << army_name_set[warr[e]->armyname] <<" " << warr_name_set[warr[e]->warriorname] <<" "
                                   << warr[e]->id << " reached "<< army_name_set[1-e] <<" headquarter with "
                                   << warr[e]->element << " elements and force "<< warr[e]->force<< endl;
                enemy_num=warr[e]->id;
                return 0;
             }  
             else{
                  if(enemy_num!=warr[e]->id) 
                  {  //second enemy arrived 
                     PrintClock();  cout << army_name_set[warr[e]->armyname] <<" " << warr_name_set[warr[e]->warriorname] <<" "
                                         << warr[e]->id << " reached "<< army_name_set[1-e] <<" headquarter with "
                                         << warr[e]->element << " elements and force "<< warr[e]->force<< endl;
                     PrintClock();  cout << army_name_set[1-e] <<" headquarter was taken"<< endl;
                     return 1;
                  }
                  else { //nothing to do 
                      return 0;
                  }
            }}
         else return 0;
}    

int Cities::Shooting(Cities* next_city, int armyname_) 
{
       PrintClock();
       cout << army_name_set[armyname_] <<" "<< warr_name_set[warr[armyname_]->warriorname] <<" "
            << warr[armyname_]->id << " shot" ; 
       if( ((Arrow*)(warr[armyname_]->arsenal[2]))!=NULL) 
        ((Arrow*)(warr[armyname_]->arsenal[2]))->n_arrow--; 
        if ( ((Arrow*)(warr[armyname_]->arsenal[2]))->n_arrow==0 )
             warr[armyname_]->arsenal[2]=NULL ; 
     //DO:beatee hurted
       if(( next_city->warr[1-armyname_]->element-g_R)<=0) {
          cout << " and killed "<< army_name_set[next_city->warr[1-armyname_]->armyname] <<" " 
               << warr_name_set[next_city->warr[1-armyname_]->warriorname] <<" "
               << next_city->warr[1-armyname_]->id<<endl;
          return 1;//remote kill 
        }
        else{
            next_city->warr[1-armyname_]->element-=g_R;
        }
       cout << endl;
       return 0;     
}

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
Warriors::Warriors(){}
Warriors::Warriors(int warr_name_, int armyname_, int num_total_warrior_){
    //for(int i=0; i<5; i++) n_warriors[i]=0; 
    armyname = armyname_;
    warriorname = warr_name_;
    id = num_total_warrior_;
    arsenal[0]= NULL; 
    arsenal[1]= NULL; 
    arsenal[2]= NULL; 
    PrintClock();
    cout << army_name_set[armyname] << " " << warr_name_set[warriorname] 
         << " " << id << " born" << endl;
}
Warriors::~Warriors(void) { //for(int i=0; i<3; i++)  delete arsenal[i]; 
}


int Warriors::Bombing(Warriors* beater, Warriors* beatee){//1-- beater win ; 0--equal; -1 -- beatee win
   int er=beater->element;
   int ee=beatee->element;
   //cout << "==="<< er << " " << ee << endl;
   //if(ee==0) 
   ee-=beater->force; if(beater->arsenal[0]!=NULL) ee-=beater->arsenal[0]->force;
   if(ee <= 0) {//cout <<"ee dead..." <<endl;
      return 1;}
   else if(beatee->warriorname==NINJA) {//cout << "er no die.." << endl;
     return 0;}
   else { 
     er-=((beatee->force)/2); if(beatee->arsenal[0]!=NULL) er-=(beatee->arsenal[0])->force;
     //cout << "fighting!!"<< endl;
     if(er<=0) return -1;
     else return 0;
  } 
   return 0;

}
int Warriors::Attack(Warriors* beatee, int city_id, int city_M_){ 
    int return_value=0;
    PrintClock();
    cout << army_name_set[armyname] <<" "<< warr_name_set[warriorname] <<" "<< id <<" attacked "
         << army_name_set[beatee->armyname]<<" "<< warr_name_set[beatee->warriorname]<<" "<< beatee->id<<" in city " 
         << city_id <<" with "<< element << " elements and force "<< force << endl;
    if(beatee->Hurted(this,false)) {
       return_value = beatee->Killed(this, city_id, city_M_);
    }//attacker win city_M
    else if(beatee->warriorname==NINJA)  return_value = 0;
    else return_value = beatee->FightBack(this, city_id, city_M_);
    
    if(return_value>0){//killed opponent
       if(this->warriorname==DRAGON) { ((WDragon*)this)->morale+=0.2; this->Yelling(city_id);}
       this->EarnElements( city_id, city_M_ ); 
    }
    else if(return_value==-1){//being killed by "fight back"
       if(beatee->warriorname==DRAGON) { ((WDragon*)beatee)->morale+=0.2;} //beatee->Yelling(city_id);}
        beatee->EarnElements( city_id, city_M_ ); 
    }
    else {//both alive
       if(this->warriorname==DRAGON) { ((WDragon*)this)->morale-=0.2; this->Yelling(city_id);}
       else if(this->warriorname==LION) { ((WLion*)this)->loyalty-=g_K;}
       if(beatee->warriorname==DRAGON) { ((WDragon*)beatee)->morale-=0.2;}//beatee->Yelling(city_id);}
       else if(beatee->warriorname==LION) { ((WLion*)beatee)->loyalty-=g_K;}
    }
    return return_value;
}
void Warriors::Yelling(int city_id){
         if(((WDragon*)this)->morale>0.8){
             PrintClock(); cout << army_name_set[armyname] <<" "<< warr_name_set[warriorname] <<" "<< id <<  " yelled in city " << city_id << endl;
         }
}
int Warriors::Hurted(Warriors* beater,bool fightback){
   int tmp_element=element;
    if(fightback) {tmp_element-=beater->force/2;}
    else tmp_element-=beater->force;
    if (beater->arsenal[0]!=NULL) { //fightback counts? yes
        tmp_element-=beater->arsenal[0]->force; 
        beater->arsenal[0]->force = (beater->arsenal[0]->force*8)/10;//Sword
        if(beater->arsenal[0]->force==0)//lost Sword when it's force down to 0 
           beater->arsenal[0]=NULL;
    }
    if(tmp_element<=0)
      return 1;//been killed
    else
      element=tmp_element;
      return 0;
}
int Warriors::Killed(Warriors* beater, int city_id, int city_M_){
    PrintClock();
        cout << army_name_set[armyname] <<" "<< warr_name_set[warriorname] <<" "<< id <<" was killed in city " 
             << city_id << endl;
        //TODO reward 8 elements to warriors
    beater->PickUp(beater,this);
    return city_M_;
}
void Warriors::PickUp(Warriors* beater, Warriors* beatee){
    if(beater->warriorname==WOLF) for(int i=0; i<3; i++) if(beater->arsenal[i]==NULL&& beatee->arsenal[i]!=NULL) { beater->arsenal[i]=beatee->arsenal[i];beatee->arsenal[i]=NULL;//TODO Shallow copy??
     // cout<< warr_name_set[beater->warriorname]<< "===GOT weapon " << i << endl;
     }
    if (beatee->warriorname==LION) { beater->element+=beatee->element;}//cout<<beatee->element<<"==" <<endl;}
}
int Warriors::FightBack(Warriors* beater, int city_id, int city_M_){
    PrintClock();
        cout << army_name_set[armyname] <<" "<< warr_name_set[warriorname] <<" "<< id <<" fought back against "
             << army_name_set[beater->armyname]<<" "<< warr_name_set[beater->warriorname]<<" "<< beater->id<<" in city " 
             << city_id << endl;
        if(beater->Hurted(this,true)) {
           beater->Killed(this, city_id, city_M_);
           return -1;}
        else  return 0;
}
int Warriors::EarnElements(int city_id, int city_M_){
    PrintClock();
    cout << army_name_set[armyname] <<" "<< warr_name_set[warriorname] <<" "<< id <<" earned "
         << city_M_ <<" elements for his headquarter"<< endl;
    return city_M_;
}

WDragon::WDragon(int armyname_, int num_total_warrior_, int M_):Warriors(0, armyname_, num_total_warrior_){
    element = g_strength[0]; 
    force = g_attack[0];
    morale=((float)M_/(float)element);
    cout << "Its morale is ";
    printf("%.2f", morale);//convert to cout
    cout  << endl;
    switch(num_total_warrior_%3){
        case(0)://
            if((int)force/5) arsenal[0]= new Sword(force/5); break;
        case(1): 
            arsenal[1]= new Bomb(); break;
        case(2):
            arsenal[2]= new Arrow(); break;
    }
}
WNinja::WNinja(int armyname_, int num_total_warrior_, int M_):Warriors(1, armyname_, num_total_warrior_){
    element = g_strength[1]; 
    force = g_attack[1];

    switch(num_total_warrior_%3){
        case(0):
            if((int)force/5)arsenal[0]= new Sword(force/5);
            arsenal[1]= new Bomb();
          break;
        case(1):
            arsenal[1]= new Bomb();
            arsenal[2]= new Arrow();
          break;
        case(2):
            arsenal[2]= new Arrow();
            if((int)force/5) arsenal[0]= new Sword(force/5);
          break;
        default: cout << "ERROR"<< endl; break;
    }
}  
WIceman::WIceman(int armyname_, int num_total_warrior_, int M_):Warriors(2, armyname_, num_total_warrior_){
    element = g_strength[2]; 
    n_move=0;
    force = g_attack[2];
    switch(num_total_warrior_%3){
        case(0):
            if((int)force/5) arsenal[0]= new Sword(force/5); break;
        case(1): 
            arsenal[1]= new Bomb(); break;
        case(2):
            arsenal[2]= new Arrow(); break;
    }
}
WLion::WLion(int armyname_, int num_total_warrior_, int M_):Warriors(3, armyname_, num_total_warrior_){
    element = g_strength[3]; 
    force = g_attack[3];
    loyalty=M_;
    cout << "Its loyalty is " << loyalty << endl;
}  
WWolf::WWolf(int armyname_, int num_total_warrior_, int M_):Warriors(4, armyname_, num_total_warrior_){
    element = g_strength[4]; 
    force =   g_attack[4];
}  

void Decoder(Weapons* arsenal[],int key) {
  switch(key){
    case(9)://have all
        cout << "arrow(" << ((Arrow*)arsenal[2])->n_arrow << "),bomb,sword(" <<  arsenal[0]->force << ")"; break;
    case(7)://arrow and bomb
        cout << "arrow(" << ((Arrow*)arsenal[2])->n_arrow << "),bomb"; break;
    case(6)://arrow and sword
        cout << "arrow(" << ((Arrow*)arsenal[2])->n_arrow << "),sword(" <<  arsenal[0]->force << ")"; break;
    case(5)://bomb and sword
        cout << "bomb,sword(" <<  arsenal[0]->force << ")"; break;
    case(4)://arrow
        cout << "arrow(" << ((Arrow*) arsenal[2])->n_arrow << ")"; break;
    case(3)://bomb
        cout << "bomb"; break;
    case(2)://sword
        cout << "sword(" <<  arsenal[0]->force << ")"; break;
    default:  cout << "no weapon";  
  }  
  cout  << endl;
}

void Warriors::Property(){}

//Class definition====================Dragon
void WDragon::Property(){
  int encoder=0;
  for(int i=0; i < 3; i++) {
    if (arsenal[i]!=NULL){
       encoder+=2+i;
    }
  }
  Decoder(arsenal, encoder);//Consider Authorition management in Linux
}

//Class definition====================Ninja
void  WNinja::Property(){
  int encoder=0;
  for(int i=0; i < 3; i++) {
    if (arsenal[i]!=NULL)
       encoder+=2+i;
  }
  Decoder(arsenal, encoder);
}

//Class definition====================Iceman
void WIceman::Property(){
  int encoder=0;
  for(int i=0; i < 3; i++) {
    if (arsenal[i]!=NULL)
      {// cout << endl<<"+===== " << warr_name_set[warriorname] << " has " << arsenal[i]->weapon_name<< endl;
       encoder+=2+i;}
  }
  Decoder(arsenal, encoder);
}

//Class definition====================Lion
void WLion::Property(){
    cout << "no weapon"  << endl;
}

//Class definition====================Wolf
void WWolf::Property(){
  int encoder=0;
  for(int i=0; i < 3; i++) {
    if (arsenal[i]!=NULL)
       encoder+=2+i;
  }
  Decoder(arsenal, encoder);
}

//Class definition====================Headquarters=======================  
Headquarters::Headquarters(string armyname_, int num_, int M_){ 
    sequence_num = num_; 
    armyname = num_-1;
    M = M_;
    order_counter = n_total_warriors=0;
    warr_v.reserve(60);
    for(int i=0; i<5; i++) n_warriors[i]=0;//number of each kind of warriors 
}

Warriors* Headquarters::Produce() {
  int j=0;
  //cout << "Test... M=" << M << " ORDER=" << ORDER[sequence_num][order_counter] << endl;
  while (( M<g_strength[ORDER[sequence_num][order_counter]] ) && j<5) {  
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
      M=M-g_strength[warr_id];
      //需用工厂模式
      switch(warr_id){
          case(0): warr_v.push_back( new WDragon(armyname, ++n_total_warriors, M)); break; 
          case(1): warr_v.push_back( new WNinja (armyname, ++n_total_warriors, M)); break;
          case(2): { warr_v.push_back( new WIceman(armyname, ++n_total_warriors, M)); 
                    // for (int i=0; i<3; i++) if(warr_v.back()->arsenal[i]!=NULL)
                  //   cout << " ++++ iceman has " << warr_v.back()->arsenal[i]->weapon_name<< endl;  
                   }  break; 
          case(3): warr_v.push_back( new WLion  (armyname, ++n_total_warriors, M)); break; 
          case(4): warr_v.push_back( new WWolf  (armyname, ++n_total_warriors, M)); break;   
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
   if(armyname == 0) {//red
     // for(vector<Warriors*>::iterator it = warr_v.end()-1; it >= warr_v.begin(); --it){
     for(int i=warr_in_hand-1; i>= 0; --i){
          if (warr_v[i]!=NULL){
              PrintClock(); cout << "red " <<  warr_name_set[warr_v[i]->warriorname] << " " << warr_v[i]->id << " has "; warr_v[i]->Property();
          }
      }
   }
   else if(armyname == 1){
     // for(vector<Warriors*>::iterator it = warr_v.begin(); it != warr_v.end(); ++it){
     for(int i=0; i< warr_in_hand; ++i){
          if (warr_v[i]!=NULL){
              PrintClock(); cout << "blue " << warr_name_set[warr_v[i]->warriorname] << " " << warr_v[i]->id << " has "; warr_v[i]->Property();
          }
      }
   } 
   else cout << "Error" << endl;
} 
//Class definition====================Engine============================= 
Engine::Engine() {  }//myclock = NULL; }

void Engine::Init(int M, int T) {
    Headquarters RedArmy ("red", 1, M);
    Headquarters BlueArmy("blue", 2, M);  
    city_v.reserve(n_total_city);
    for(int i = 0; i<= n_total_city + 1; i++){//0 is red headquarter, N+1 is blue headquarter;
        city_v.push_back( new Cities(i) );  //?? vector<Cities>  
    }    
    int dead_loop=T+1; //Prevent dead loop
    int gameover=0;
    while((!gameover)&&(dead_loop--)){
        switch(minute){
		    case(0): {//Warriors Born 
			          city_v[0]->warr[0]=RedArmy.Produce();
                      city_v[n_total_city+1]->warr[1]=BlueArmy.Produce();
 		      break;
		    }
		    case(5): {//lions runaway
			          for (int i=1; i< n_total_city + 1; i++)
			              for (int j=0; j<2; j++)
					 	    if (city_v[i]->warr[j]!=NULL) 
                              if( city_v[i]->warr[j]->warriorname==LION)
                              if (((WLion*)(city_v[i]->warr[j]))->loyalty<=0){
			                     PrintClock(); cout << army_name_set[city_v[i]->warr[j]->armyname]<<" lion "<< city_v[i]->warr[j]->id << " ran away" << endl;
                                 if (j==0) RedArmy.warr_v[city_v[i]->warr[j]->id-1]=NULL;
                                 else BlueArmy.warr_v[city_v[i]->warr[j]->id-1]=NULL;
    							 city_v[i]->warr[j]=NULL;
							  }
 		      break;
		    }
		    case(10): {//Marching
 			          //cout << sizeof(city_v.front())<<" --" << endl;
			          for (int i=n_total_city+1; i > 0; i--)//red
     		                  city_v[i]->March(city_v[i-1],0);
			          for (int i=0; i< n_total_city + 1; i++)//blue
     		                  city_v[i]->March(city_v[i+1],1);
                      if(city_v[0]->Occupied()) gameover=1;
			          for (int i=1; i< n_total_city + 1; i++){
                            city_v[i]->Print_march_log();}
                      if(city_v[n_total_city+1]->Occupied()) gameover=1;
 		      break;
		    }
		    case(20): {//City prosperous
			          for (int i=1; i< n_total_city + 1; i++){
                          city_v[i]->city_M+=10;
                          //cout << "==CITY "<<i << "has " << city_v[i]->city_M<< endl;
  			    }
 		      break;
		    }
		    case(30): {//Collect elements
			         for (int i=1; i< n_total_city + 1; i++){
                         if(city_v[i]->warr[0]!=NULL && city_v[i]->warr[1]==NULL){ 
					         RedArmy.M+=(city_v[i]->city_M); 
				             PrintClock();
					         cout<< "red " << warr_name_set[city_v[i]->warr[0]->warriorname] <<" "<< city_v[i]->warr[0]->id 
                                           << " earned "<< city_v[i]->city_M << " elements for his headquarter" << endl;
  					         city_v[i]->city_M=0; 
				         }
                         if(city_v[i]->warr[1]!=NULL && city_v[i]->warr[0]==NULL){ 
		                     BlueArmy.M+=(city_v[i]->city_M); 
		                     PrintClock();
		                   	 cout<< "blue " << warr_name_set[city_v[i]->warr[1]->warriorname] <<" "<< city_v[i]->warr[1]->id 
                                            << " earned "<< city_v[i]->city_M << " elements for his headquarter"<< endl;
  		                     city_v[i]->city_M=0; 
		                  }
			         }            
 		      break;
		    }
		    case(35): {//Arrow shooting
			        for (int i=1; i < n_total_city; i++){//red
   		                if( city_v[i]->warr[0]!=NULL )//has warroir with arror, and next city has enemy 
                            if( (city_v[i]->warr[0]->arsenal[2]!=NULL) && (city_v[i+1]->warr[1]!=NULL ))
						        if( city_v[i]->Shooting(city_v[i+1],0)==1 ){ city_v[i+1]->warr[1]->element=0; }
                    }
			        for (int i=2; i < n_total_city+1 ; i++){//blue
   		                if( city_v[i]->warr[1]!=NULL ) 
                            if( (city_v[i]->warr[1]->arsenal[2]!=NULL) && (city_v[i-1]->warr[0])!=NULL ) 
                              if( city_v[i]->Shooting(city_v[i-1],1)==1 ) city_v[i-1]->warr[0]->element=0;
                    }
 		      break;
		    }
		    case(38): {//Bombing
                     int earnedM=0;
                     int remove=0;
			         for( int i=1; i< n_total_city + 1; i++ )
                        if((city_v[i]->warr[0]!=NULL &&  city_v[i]->warr[1]!=NULL)) {//has both warriors in a same city
                               remove=0;
                        if((city_v[i]->warr[0]->element>0 && city_v[i]->warr[1]->element >0)) 
                           if((city_v[i]->warr[0]->arsenal[1]!=NULL || city_v[i]->warr[1]->arsenal[1]!=NULL)) {
                              if(( city_v[i]->flag_color==REDFLAG )||( i%2==1 && city_v[i]->flag_color==2 )) {
                                    earnedM = city_v[i]->warr[0] -> Bombing(city_v[i]->warr[0], city_v[i]->warr[1]);//RedArmy first 
									if((earnedM<0)&&(city_v[i]->warr[0]->arsenal[1]!=NULL)) {//attacker lose
									   PrintClock();
  								       cout << "red "<< warr_name_set[city_v[i]->warr[0]->warriorname] <<" "<< city_v[i]->warr[0]->id<<" used a bomb and killed blue "
                                            << warr_name_set[city_v[i]->warr[1]->warriorname]<<" "<< city_v[i]->warr[1]->id<< endl;
                                       remove=1;
 									}
									else if((earnedM>0)&&(city_v[i]->warr[1]->arsenal[1]!=NULL)){
									   PrintClock();
  								       cout << "blue "<< warr_name_set[city_v[i]->warr[1]->warriorname] <<" "<< city_v[i]->warr[1]->id<<" used a bomb and killed red "
                                            << warr_name_set[city_v[i]->warr[0]->warriorname]<<" "<< city_v[i]->warr[0]->id<< endl;
                                       remove=1;
                                    }
							  }
                              else if(( city_v[i]->flag_color==BLUEFLAG )||( i%2==0 && city_v[i]->flag_color==2 )) {
                                    earnedM = city_v[i]->warr[1] -> Bombing( city_v[i]->warr[1], city_v[i]->warr[0]);//BlueArmy first
   
									if((earnedM<0)&&(city_v[i]->warr[1]->arsenal[1]!=NULL)){//attacker lose
									   PrintClock();
  								       cout << "blue "<< warr_name_set[city_v[i]->warr[1]->warriorname] <<" "<< city_v[i]->warr[1]->id<<" used a bomb and killed red "
                                            << warr_name_set[city_v[i]->warr[0]->warriorname]<<" "<< city_v[i]->warr[0]->id<< endl;
                                       remove=1;
  									    
									}
									else if((earnedM>0)&&(city_v[i]->warr[0]->arsenal[1]!=NULL)){
									   PrintClock();
  								       cout << "red "<< warr_name_set[city_v[i]->warr[0]->warriorname] <<" "<< city_v[i]->warr[0]->id<<" used a bomb and killed blue "
                                           << warr_name_set[city_v[i]->warr[1]->warriorname]<<" "<< city_v[i]->warr[1]->id<< endl;
                                       remove=1;
									}
                              }
								    if(remove){
									   RedArmy.warr_v[city_v[i]->warr[0]->id-1]=NULL;
								       BlueArmy.warr_v[city_v[i]->warr[1]->id-1]=NULL;
                                       city_v[i]->warr[0]=NULL; 
                                       city_v[i]->warr[1]=NULL;
									   remove=0;
									} 
                           }
                     }
 		      break;
		    }
		    case(40): {//Attack & Fight_back & Yelling & Earn_elements
                     int earnedM=0;
                     int redearnedM=0;
                     int blueearnedM=0;
                     bool attack_signal; 
                     int winner;
	                 for( int i=1; i< n_total_city + 1; i++ )
                     {
                        attack_signal=true; 
                        winner=-1;
                        for (int j=0; j<2; j++) //clean battle area after arrowing
                         {
                           if(city_v[i]->warr[j]!=NULL && city_v[i]->warr[j]->element==0) 
                              if(city_v[i]->warr[1-j]!=NULL && city_v[i]->warr[1-j]->element>0) {
                                  if(j==0)//red dead
 							      { 
                                    if(( city_v[i]->flag_color==BLUEFLAG )||( i%2==0 && city_v[i]->flag_color==2 )) {
                                       if(city_v[i]->warr[1-j]->warriorname==DRAGON) {
                                          ((WDragon*)(city_v[i]->warr[1-j]))->morale+=0.2;
                                          city_v[i]->warr[1-j]->Yelling(i);}
                                        }
                                    city_v[i]->warr[1-j]->PickUp(city_v[i]->warr[1-j], city_v[i]->warr[j]);
							        RedArmy.warr_v[city_v[i]->warr[0]->id-1]=NULL;
           					        city_v[i]->warr[j]=NULL;                        
							        PrintClock(); cout << army_name_set[city_v[i]->warr[1-j]->armyname]<<" "<< warr_name_set[city_v[i]->warr[1-j]->warriorname]<<" "
                                                       << city_v[i]->warr[1-j]->id<<" earned " << city_v[i]->city_M<<" elements for his headquarter"<< endl;
							        blueearnedM+=city_v[i]->city_M;
							        winner=1;
                                    if (BlueArmy.M >= 8)//Reward 
                                        { BlueArmy.M-=8; city_v[i]->warr[1]->element+=8; }
							        city_v[i]->city_M=0;
							      }
                                  else if(j==1)//blue dead
							      { 
                                    if(( city_v[i]->flag_color==REDFLAG )||( i%2==1 && city_v[i]->flag_color==2 )) {//if red first, red yell
                                       if(city_v[i]->warr[1-j]->warriorname==DRAGON)
                                          ((WDragon*)(city_v[i]->warr[1-j]))->morale+=0.2;
                                          city_v[i]->warr[1-j]->Yelling(i);
                                        }
                                    city_v[i]->warr[1-j]->PickUp(city_v[i]->warr[1-j], city_v[i]->warr[j]);
  							        //cout<<"=========BlueArmy Warr is "<< warr_name_set[BlueArmy.warr_v[city_v[i]->warr[1]->id-1]->warriorname] << " " 
                                    //    <<  BlueArmy.warr_v[city_v[i]->warr[1]->id-1]->id;
                                    //cout <<" " << ", city_v warr is "<< warr_name_set[city_v[i]->warr[j]->warriorname] <<city_v[i]->warr[j]->id << endl;
                             
							        BlueArmy.warr_v[city_v[i]->warr[1]->id-1]=NULL;
           					        city_v[i]->warr[j]=NULL;                        
							        PrintClock(); cout << army_name_set[city_v[i]->warr[1-j]->armyname]<<" "<< warr_name_set[city_v[i]->warr[1-j]->warriorname]<<" "
                                                       << city_v[i]->warr[1-j]->id<<" earned " << city_v[i]->city_M <<" elements for his headquarter"<< endl;
							        redearnedM+=city_v[i]->city_M;
							        winner=0;
                                    if (RedArmy.M >= 8)//Reward 
                                       { RedArmy.M-=8; city_v[i]->warr[0]->element+=8; }
							        city_v[i]->city_M=0;
                                  }
							}
                            else {
                                if(j==0){//red dead
							        RedArmy.warr_v[city_v[i]->warr[0]->id-1]=NULL;
           					        city_v[i]->warr[0]=NULL;  }
                                else{
							        BlueArmy.warr_v[city_v[i]->warr[1]->id-1]=NULL;
           					        city_v[i]->warr[1]=NULL;  }
                            }
                         }

                        if((city_v[i]->warr[0]!=NULL && city_v[i]->warr[1]!=NULL)&&(attack_signal)) {
                          if(( city_v[i]->flag_color==REDFLAG )||( i%2==1 && city_v[i]->flag_color==2 )) {
                                earnedM = city_v[i]->warr[0] -> Attack( city_v[i]->warr[1],city_v[i]->city_id, city_v[i]->city_M );//RedArmy first 
                                if(earnedM==-1){//been killed by "fight back"
                                    blueearnedM += city_v[i]->city_M;
                                    //RedArmy.warr_v.erase(RedArmy.warr_v.begin()+(city_v[i]->warr[0]->id-2));
								    RedArmy.warr_v[city_v[i]->warr[0]->id-1]=NULL;
                                    city_v[i]->warr[0]=NULL;
                                    winner=1;
                                    if (BlueArmy.M >= 8)//Reward 
                                        { BlueArmy.M-=8; city_v[i]->warr[1]->element+=8; }
                                }
                                else if(earnedM > 0) {//killed opponent
                                    redearnedM += earnedM;
                                    //BlueArmy.warr_v.erase(BlueArmy.warr_v.begin()+(city_v[i]->warr[1]->id-2));
								    BlueArmy.warr_v[city_v[i]->warr[1]->id-1]=NULL;
                                    city_v[i]->warr[1]=NULL;
                                    winner=0;
                                    if (RedArmy.M >= 8)//Reward 
                                        { RedArmy.M-=8; city_v[i]->warr[0]->element+=8; }
                               }
                               else{ //no toll
                                   winner=3;
                               }
                          }
                          else if(( city_v[i]->flag_color==BLUEFLAG )||( i%2==0 && city_v[i]->flag_color==2 )) {
                                earnedM = city_v[i]->warr[1] -> Attack( city_v[i]->warr[0],city_v[i]->city_id, city_v[i]->city_M );//BlueArmy first
                                if(earnedM==-1){//be killed by "fight back"
                                   redearnedM += city_v[i]->city_M;
                                   //cout << "erase " << BlueArmy.warr_v[(city_v[i]->warr[1]->id-2) ]->id << endl;
                                   //BlueArmy.warr_v.erase(BlueArmy.warr_v.begin()+(city_v[i]->warr[1]->id-2));
								   BlueArmy.warr_v[city_v[i]->warr[1]->id-1]=NULL;
                                   city_v[i]->warr[1]=NULL;
                                   winner=0;
                                   if (RedArmy.M >= 8)//Reward 
                                      { RedArmy.M-=8; city_v[i]->warr[0]->element+=8; }
                                }
                                else if(earnedM > 0) {//killed opponent
                                    blueearnedM += earnedM;
                                    //RedArmy.warr_v.erase(RedArmy.warr_v.begin()+(city_v[i]->warr[0]->id-2));
								    RedArmy.warr_v[city_v[i]->warr[0]->id-1]=NULL;
                                    city_v[i]->warr[0]=NULL;
                                    winner=1;
                                   if (BlueArmy.M >= 8)//Reward 
                                      { BlueArmy.M-=8; city_v[i]->warr[1]->element+=8; }
                                }
                               else{ //no toll
                                   winner=3;
                               }
                          }
                          if(earnedM!=0) 
                             city_v[i]->city_M=0;
                       }
//cout << "+++++winner is " << winner << ", in city "<< i << " ,last is "<< city_v[i]->last_win << endl;
                       if(city_v[i]->last_win==winner&&city_v[i]->flag_color!=winner){//last_win can only be 0 or 1
		                   PrintClock(); cout << army_name_set[winner] <<" flag raised in city " << i <<endl;
                           city_v[i]->flag_color=winner;
		                }
		                else if(winner==3) city_v[i]->last_win=2;//incontinuous
		                else if(winner<0) ; //equal battle, do nothing
		                else city_v[i]->last_win=winner;
                     }
                     RedArmy.M += redearnedM;
                     BlueArmy.M += blueearnedM;
                    
 		      break;
		    }
            case(61):{
                     int warr_in_hand=BlueArmy.warr_v.size();
                     int armyname=1;
                     if(armyname ==1) {//red
                       // for(vector<Warriors*>::iterator it = warr_v.end()-1; it >= warr_v.begin(); --it){
                       for(int i=warr_in_hand-1; i>= 0; --i){
                            if (RedArmy.warr_v[i]!=NULL){
                                PrintClock(); cout << "=="<<i<<"==" <<" red " << warr_name_set[RedArmy.warr_v[i]->warriorname] << " " << RedArmy.warr_v[i]->id <<  endl;
                            }
                        }
                     }
                     if(armyname == 1){
                       // for(vector<Warriors*>::iterator it = warr_v.begin(); it != warr_v.end(); ++it){
                       for(int i=0; i< warr_in_hand; ++i){
                            if (BlueArmy.warr_v[i]!=NULL){
                                PrintClock(); cout << "=="<<i<<"==" <<" blue " << warr_name_set[BlueArmy.warr_v[i]->warriorname] << " " << BlueArmy.warr_v[i]->id << endl;
                            }
                        }
                     } 
                     else cout << "Error"; 
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
 queue<int> Mvalues, Nvalues, Rvalues, Kvalues, Tvalues;  //Store input data
 queue<int> Wvalues;
 queue<int> Avalues;
 //cout << endl<<endl<<endl;
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
    Engine myengine;
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
   /* cout<<  Mvalues.front() <<" "<< n_total_city <<" "<<g_K<<" "<<g_R<<" "<<Tvalues.front()<<endl;
    for (int i=0;i<5;i++) {
      cout << g_strength[i] <<" ";}
    cout<<endl;
    for (int i=0;i<5;i++) {
      cout << g_attack[i] <<" ";}
    cout<<endl;*/
    Mvalues.pop();
    Nvalues.pop();
    Rvalues.pop();
    Kvalues.pop();
    Tvalues.pop();
    //cout << "TOTAL " << cishu << endl;      
}
// cout << endl<<endl<<endl;
 return 0;
}
