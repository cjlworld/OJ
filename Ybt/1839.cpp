#include<cstdio>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
const int N=105;
struct student
{
	char name[50];
	int mark1,mark2;
	bool leader;
	bool west;
	int posts;
	int o;
	int money;
	bool operator<(const student &y) 
	{
		return this->money < y.money || (this->money == y.money && this->o > y.o);
	}
}a[N];
int n;
int sum,temp;
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	char tmp;
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%s",a[i].name+1);
		scanf("%d%d",&a[i].mark1,&a[i].mark2);
		cin>>tmp; a[i].leader=(tmp=='Y');
		cin>>tmp; a[i].west=(tmp=='Y');
		scanf("%d",&a[i].posts);
		a[i].o=i;
		
		if(a[i].mark1>80&&a[i].posts>=1) 
			a[i].money+=8000;
		if(a[i].mark1>85&&a[i].mark2>80) 
			a[i].money+=4000;
		if(a[i].mark1>90) 
			a[i].money+=2000;
		if(a[i].mark1>85&&a[i].west) 
			a[i].money+=1000;
		if(a[i].mark2>80&&a[i].leader)
			a[i].money+=850;
		
		if(a[temp]<a[i])
			temp=i;
		sum+=a[i].money;
	}
	printf("%s\n",a[temp].name+1);
	printf("%d\n%d\n",a[temp].money,sum);
	return 0;
}

