#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

#define DRAGON 0
#define NINJIA 1
#define ICEMAN 2
#define LION 3
#define WOLF 4

class worriors
{
public:
	worriors() {}
	worriors(int newcolor,int newid,int newtype);
	void get_hp(int);
	static void init(int input);
	static int total[2];
	virtual void twice() {}
	virtual void happy(int) {}
	friend class city;
protected:
	int type;
	int id;
	int hp;
	int time;
	int color;
	int attack;
	int kill;
};
class dragon: public worriors
{
private:
public:
	dragon() {}
	dragon(int newcolor,int newid,int newtype);
	void happy(int);
};
class ninjia: public worriors
{
private:
public:
	ninjia() {}
	ninjia(int newcolor,int newid,int newtype);
};
class iceman: public worriors
{
private:
public:
	iceman() {}
	iceman(int newcolor,int newid,int newtype);
};
class lion: public worriors
{
private:
public:
	lion() {}
	lion(int newcolor,int newid,int newtype);
	~lion() {};
	void escape();
};
class wolf: public worriors
{
private:
public:
	wolf() {}
	wolf(int newcolor,int newid,int newtype);
	void twice();
};
class city
{
private:
	int id;
	int color;
	int hp;
	int last_beat_win;
public:
	worriors* data[2];
	~city()
	{
		for (int i=0;i<=1;i++)
		if (data[i]!=NULL)
		{
			delete data[i];
			data[i]=NULL;
		}
	}
	int just_beat_win;
	void creat(int);
	void input_hp();
	void output_hp();
	void beat_win(int);
	void beat();
	void go(city*,int);
	bool reach_headquater(int);
	void print_last_go();
};

int worriors::total[2]={0};
int need[5],order[2],number[2],_attack[5],worriors_temp[2],now_time;
int now_order[2][5]={{2,3,4,1,0},{3,0,1,2,4}};
bool head_num[2],game_over;
city citys[22];
int city_sum;

//FILE *savefile,*readfile;

const char* s[2]={"red","blue"};
const char* ss[5]={"dragon","ninja","iceman","lion","wolf"};

void worriors::init(int input)
{
	total[0]=total[1]=input;
}
worriors::worriors(int newcolor,int newid,int newtype)
{
	printf("%.3d:00 %s %s %d born\n",now_time,s[newcolor],ss[newtype],newid);
	total[newcolor]-=need[newtype];
	id=newid;
	time=now_time;
	color=newcolor;
	type=newtype;
	hp=need[newtype];
	attack=_attack[newtype];
	kill=0;
}
void worriors::get_hp(int a)
{
	hp+=a;
}
dragon::dragon(int newcolor,int newid,int newtype):worriors(newcolor,newid,newtype)
{

}
void dragon::happy(int _id)
{
	printf("%.3d:40 %s dragon %d yelled in city %d\n",now_time,s[color],id,_id);
}
ninjia::ninjia(int newcolor,int newid,int newtype):worriors(newcolor,newid,newtype)
{

}
iceman::iceman(int newcolor,int newid,int newtype):worriors(newcolor,newid,newtype)
{

}
lion::lion(int newcolor,int newid,int newtype):worriors(newcolor,newid,newtype)
{

}
wolf::wolf(int newcolor,int newid,int newtype):worriors(newcolor,newid,newtype)
{

}
void wolf::twice()
{
	if (kill>0 && kill%2==0)
	{
		hp*=2;
		attack*=2;
	}
}
void city::creat(int _id)
{
	data[0]=data[1]=NULL;
	id=_id;
	last_beat_win=-1;
	just_beat_win=-1;
	color=-1;
	hp=0;
}
void city::beat_win(int _color)
{
	just_beat_win=_color;
	if (color!=_color && last_beat_win==_color)
	{
		color=_color;
		printf("%.3d:40 %s flag raised in city %d\n",now_time,s[_color],id);
	}
	last_beat_win=_color;
}
void city::input_hp()
{
	hp+=10;
}
void city::output_hp()
{
	int turn=-1;
	if (data[0]!=NULL && data[1]==NULL) turn=0;
	if (data[1]!=NULL && data[0]==NULL) turn=1;
	if (turn!=-1)
	{
		printf("%.3d:30 %s %s %d earned %d elements for his headquarter\n",now_time,s[turn],ss[data[turn]->type],data[turn]->id,hp);
		worriors::total[turn]+=hp;
		hp=0;
	}
}
void city::beat()
{
	int turn,turn2,left_hp=0;
	just_beat_win=-1;
	if (data[0]==NULL || data[1]==NULL)
		return;
	if (color==0 || (color==-1 && id%2==1)) {turn=0;turn2=1;}
	else {turn=1;turn2=0;}
	printf("%.3d:40 %s %s %d ",now_time,s[turn],ss[data[turn]->type],data[turn]->id);
	printf("attacked %s %s %d in city %d with %d elements and force %d\n",s[turn2],ss[data[turn2]->type],data[turn2]->id,id,data[turn]->hp,data[turn]->attack);
	if (data[turn2]->type==LION)
		left_hp=data[turn2]->hp;
	data[turn2]->hp-=data[turn]->attack;
	if (data[turn2]->hp<=0)
	{
		printf("%.3d:40 %s %s %d was killed in city %d\n",now_time,s[data[turn2]->color],ss[data[turn2]->type],data[turn2]->id,id);
		delete data[turn2];
		data[turn2]=NULL;
		data[turn]->kill++;
		data[turn]->twice();
		if (left_hp!=0)
			data[turn]->hp+=left_hp;
		data[turn]->happy(id);
		printf("%.3d:40 %s %s %d earned %d elements for his headquarter\n",now_time,s[turn],ss[data[turn]->type],data[turn]->id,hp);
		worriors_temp[turn]+=hp;
		hp=0;
		beat_win(turn);
	}
	else
	{
		if (data[turn2]->type!=NINJIA)
		{
			printf("%.3d:40 %s %s %d fought back against %s %s %d in city %d\n",now_time,s[turn2],
				ss[data[turn2]->type],data[turn2]->id,s[turn],ss[data[turn]->type],data[turn]->id,id);
			if (data[turn]->type==LION)
				left_hp=data[turn]->hp;
			else left_hp=0;
			data[turn]->hp-=data[turn2]->attack/2;
			if (data[turn]->hp<=0)
			{
				printf("%.3d:40 %s %s %d was killed in city %d\n",now_time,s[data[turn]->color],ss[data[turn]->type],
					data[turn]->id,id);
				delete data[turn];
				data[turn]=NULL;
				if (left_hp!=0)
					data[turn2]->hp+=left_hp;
				printf("%.3d:40 %s %s %d earned %d elements for his headquarter\n",now_time,
					s[turn2],ss[data[turn2]->type],data[turn2]->id,hp);
				worriors_temp[turn2]+=hp;
				hp=0;
				beat_win(turn2);
			}
			else
			{
				data[turn]->happy(id);
				last_beat_win=-1;
			}
		}
		else
		{
			data[turn]->happy(id);
			last_beat_win=-1;
		}
	}
}
void city::go(city* next,int _color)
{
	data[_color]=next->data[_color];
	if (data[_color]!=NULL && data[_color]->type==ICEMAN)
	{
		if ((_color==0 && id%2==0) || (_color==1 && (city_sum-id)%2==1))
		{
			data[_color]->hp-=9;
			if (data[_color]->hp<=0) data[_color]->hp=1;
			data[_color]->attack+=20;
		}
	}
}
bool city::reach_headquater(int _color)
{
	if (data[_color]==NULL)
		return false;
	printf("%.3d:10 %s %s %d reached %s headquarter with %d elements and force %d\n",now_time,
		s[_color],ss[data[_color]->type],data[_color]->id,s[1-_color],data[_color]->hp,data[_color]->attack);
	if (head_num[_color])
		return true;
	head_num[_color]=true;
	return false;
}
void city::print_last_go()
{
	for (int i=0;i<=1;i++)
		if (data[i]!=NULL)
			printf("%.3d:10 %s %s %d marched to city %d with %d elements and force %d\n",now_time,
				s[i],ss[data[i]->type],data[i]->id,id,data[i]->hp,data[i]->attack);
}
void creat()
{
	for (int i=0;i<=1;i++)
	{
		if (worriors::total[i]>=need[now_order[i][order[i]]])
		{
			worriors* temp;
			number[i]++;
			switch (now_order[i][order[i]])
			{
			case 0:
				temp=new dragon(i,number[i],now_order[i][order[i]]);
				break;
			case 1:
				temp=new ninjia(i,number[i],now_order[i][order[i]]);
				break;
			case 2:
				temp=new iceman(i,number[i],now_order[i][order[i]]);
				break;
			case 3:
				temp=new lion(i,number[i],now_order[i][order[i]]);
				break;
			case 4:
				temp=new wolf(i,number[i],now_order[i][order[i]]);
				break;
			default:
				temp=new worriors(i,number[i],now_order[i][order[i]]);
			}
			if (i==0)
				citys[0].data[0]=temp;
			else
				citys[city_sum+1].data[1]=temp;
			order[i]=(order[i]+1)%5;
		}
	}
}
void go_ahead()
{
	for (int i=city_sum+1;i>=1;i--)
		citys[i].go(&citys[i-1],0);
	for (int i=0;i<=city_sum;i++)
		citys[i].go(&citys[i+1],1);
	citys[0].data[0]=NULL;
	citys[city_sum+1].data[1]=NULL;
	if (citys[0].reach_headquater(1))
	{
		printf("%.3d:10 red headquarter was taken\n",now_time);
		game_over=true;
	}
	for (int i=1;i<=city_sum;i++)
		citys[i].print_last_go();
	if (citys[city_sum+1].reach_headquater(0))
	{
		printf("%.3d:10 blue headquarter was taken\n",now_time);
		game_over=true;
	}
}
void pride()
{
	for (int i=1;i<=city_sum;i++)
	{
		if (worriors::total[1]<8)
			break;
		if (citys[i].just_beat_win==1)
		{
			citys[i].data[1]->get_hp(8);
			worriors::total[1]-=8;
		}
	}
	for (int i=city_sum;i>=1;i--)
	{
		if (worriors::total[0]<8)
			break;
		if (citys[i].just_beat_win==0)
		{
			citys[i].data[0]->get_hp(8);
			worriors::total[0]-=8;
		}
	}
	for (int i=0;i<=1;i++)
	{
		worriors::total[i]+=worriors_temp[i];
		worriors_temp[i]=0;
	}
}
int main()
{
	//savefile=fopen("1.txt","w");
	//readfile=fopen("E:/cpp/1.txt","r");
	int times,input;
        int r, k;
	scanf("%d",&times);
	int total_time,already_time;
	for (int t=1;t<=times;t++)
	{
		scanf("%d",&input);
		scanf("%d",&city_sum);
		scanf("%d",&r);
		scanf("%d",&k);
		scanf("%d",&total_time);
		worriors::init(input);
		already_time=0;
		game_over=false;
		now_time=-1;
		number[0]=number[1]=0;
		order[0]=order[1]=0;
		head_num[0]=head_num[1]=false;
		for (int i=0;i<=4;i++)
			scanf("%d",&need[i]);
		for (int i=0;i<=4;i++)
			scanf("%d",&_attack[i]);
		printf("Case:%d\n",t);
		for (int i=0;i<=city_sum+1;i++)
			citys[i].creat(i);
		while (1)
		{
			now_time++;
			creat();
			already_time+=10;
			if (already_time>total_time) break;
			go_ahead();
			if (game_over) break;
			for (int i=1;i<=city_sum;i++)
				citys[i].input_hp();
			already_time+=20;
			if (already_time>total_time) break;
			for (int i=1;i<=city_sum;i++)
				citys[i].output_hp();
			already_time+=10;
			if (already_time>total_time) break;
			for (int i=1;i<=city_sum;i++)
				citys[i].beat();
			pride();
			already_time+=10;
			if (already_time>total_time) break;
			for (int i=0;i<=1;i++)
				printf("%.3d:50 %d elements in %s headquarter\n",now_time,worriors::total[i],s[i]);
			already_time+=10;
			if (already_time>total_time) break;
		}
	}
	//fclose(savefile);
	//fclose(readfile);
	//system("pause");
	return 0;
}

