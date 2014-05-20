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
const int SWORD= 0;
const int BOMB = 1;
const int ARROW= 2;
const int WEAPON[3] = { SWORD,BOMB,ARROW };

//Class definition======Myclock======= 
class Myclock {
  int hour;
  public:
    Myclock() { hour = 0;}
    ~Myclock() { }
    void NextClock(void)  { hour++; }
    void PrintClock(void) { printf("%03d ",hour);}
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////WEAPONS DEFINITION BEGIN///////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Weapons {
  public:
    string weapon_name;
    Weapons(){}
    Weapons(string name):weapon_name(name){}
    virtual ~Weapons(){}
};

class Sword: virtual public Weapons{
  public:
    Sword():Weapons("sword") {}
    ~Sword(){}
    
};

class Bomb:  public Weapons{
  public:
    Bomb():Weapons("bomb"){}
    ~Bomb(){}

};

class Arrow: public Weapons{
  public:
    Arrow():Weapons("arrow"){}
    ~Arrow(){}

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////WARRIORS DEFINITION BEGIN///////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Warriors {
  public:
  string warrior_name;
  int n_warriors;
  int warrior_strength;
     Warriors();
     //Warriors(const Warriors&){ n_warriors=0; }
     virtual ~Warriors(){ 
         for(int i=0; i<3; i++)
             delete weapon_list_str[i];
        //cout << "Warriors deleted"<< endl;
     }
     Weapons*  weapon_list_str[3];//={sword,bomb,arrow};
     void set_strength(int strength_) { warrior_strength=strength_;}
     void Born(string armyname_,int num_total_warrior_); 
     virtual void Property(int num_total_warrior_, int M);
};

Warriors::Warriors(){
   n_warriors=0; 
   weapon_list_str[0]= new Sword ();
   weapon_list_str[1]= new Bomb ();
   weapon_list_str[2]= new Arrow ();
}

void Warriors::Born(string armyname_,int num_total_warrior_){ 
  n_warriors++;
  cout << armyname_ << " " << warrior_name << " " << num_total_warrior_ << " born with strength " << warrior_strength << "," << n_warriors << " " << warrior_name << " in " << armyname_<< " headquarter" << endl; 
}
    
void Warriors::Property(int num_total_warrior_, int M){
  //cout << "error"<< endl;

} 



class WDragon: public Warriors {
  public:
    //float morale;
    WDragon(int strength_){warrior_name="dragon";warrior_strength=strength_;}
    ~WDragon(){}
    //void Born(){ }
    void Property(int num_total_warrior_, int M){
      cout << "It has a " << weapon_list_str[num_total_warrior_%3]->weapon_name << ",and it's morale is ";
      printf("%.2f",((float)M/(float)warrior_strength));
      cout  << endl;
    }
}; 

class WNinja: public Warriors {
  public:
    WNinja(int strength_){warrior_name="ninja";warrior_strength=strength_;}
    ~WNinja(){}
    //void Born(){ }
    void Property(int num_total_warrior_, int M){
      cout << "It has a " << weapon_list_str[num_total_warrior_%3]->weapon_name << " and a " << weapon_list_str[(num_total_warrior_+1)%3]->weapon_name << endl;
    }
};

class WIceman: public Warriors {
  public: 
    WIceman(int strength_){warrior_name="iceman";warrior_strength=strength_;}
    ~WIceman(){}
    //void Born(){}
    void Property(int num_total_warrior_, int M){
      cout << "It has a " << weapon_list_str[num_total_warrior_%3]->weapon_name  << endl;
    }
}; 

class WLion: public Warriors {
  public:
    WLion(int strength_){warrior_name="lion";warrior_strength=strength_;}
    ~WLion(){}
    //void Born(){}
    void Property(int num_total_warrior_, int M){
      cout << "It's loyalty is " << M << endl;
    }
}; 

class WWolf: public Warriors {
  public:
    WWolf(int strength_){warrior_name="wolf";warrior_strength=strength_;}
    ~WWolf(){}
    //void Born(){}
}; 

////////////////////////////////////////////////////////////////////////////////
////////////////////////////HEADQUARTERS DEFINITION BEGIN///////////////////////
////////////////////////////////////////////////////////////////////////////////
class Headquarters {
  private:
    int init_M_;//M life value [1,1000]
    string headquarter_name; 
    Warriors*  warr_list_str[5];//={dragon,ninja,iceman,lion,wolf};
    int n_total_warriors;
    int *strength;
    int order_counter;
    int sequence_num;
    int end_produce;
  public:
    int M;
    int each_warrior_strength[5]; 
    Headquarters(string armyname, int num_, int strength_[5]);
    //Headquarters(const Headquarters & otherhead ){ sequence_num=otherhead.sequence_num; headquarter_name=otherhead.headquarter_name; end_produce=order_counter=0;}
    ~Headquarters(){
       for(int i=0; i<5; i++)
           delete warr_list_str[i];
    }
    int NotEnd() { return !end_produce; }
    void Produce(); 
};

Headquarters::Headquarters(string armyname, int num_, int strength_[5]){ 
   sequence_num=num_; headquarter_name=armyname;
   warr_list_str[0]= new WDragon(strength_[0]);
   //cout << "Memory location " << warr_list_str << " in file " << __FILE__ << " line " << __LINE__
   //     << " @ " <<  __TIMESTAMP__<< endl;//__TIME__ << __DATE__ << __STDC__    
   warr_list_str[1]= new WNinja (strength_[1]);
   warr_list_str[2]= new WIceman(strength_[2]);
   warr_list_str[3]= new WLion  (strength_[3]);
   warr_list_str[4]= new WWolf  (strength_[4]);
   strength=strength_;
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
    cout << headquarter_name << " headquarter stops making warriors" <<endl;
    end_produce=1;
  }
  else {
    //cout << "Watcher 7 " << ORDER[sequence_num][order_counter] <<endl;
    warr_list_str[ ORDER[sequence_num][order_counter] ] -> Born(headquarter_name, ++n_total_warriors);  
    
    M=M-strength[ORDER[sequence_num][order_counter]];
    warr_list_str[ ORDER[sequence_num][order_counter] ] -> Property(n_total_warriors,M);  
    
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
 int warrior_strength[5]; 
 queue<int> Mvalues, Wvalues;  //Store input data
 Myclock *myclock=NULL;
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
    if(myclock!=NULL){delete myclock;}
    myclock = new Myclock;    
    
//////////////////////Instantiation//////////////////////// 
    for (int i=0;i<5;i++) {
      warrior_strength[i]=Wvalues.front();
      Wvalues.pop();
    }
    Headquarters RedArmy("red",1,warrior_strength);
    Headquarters BlueArmy("blue",2,warrior_strength);  

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
 delete myclock;
 return 0;
}
