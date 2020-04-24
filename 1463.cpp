#include<iostream>
#include<cstdio>
#define LL long long 
using namespace std;
LL A,B,C; //k[i+1]=(A*k[i]+k[i]%B)%C
const int M=2e6+5;
const LL Mod=131313;
LL k[M];
template<class T> inline void rd(T &x)
{
	x=0; int sign=1; char inc='\0';
	while(inc=getchar()) {  
		if(inc=='-') sign=-1;
		if(inc>='0'&&inc<='9') break; 
	}
	while(inc>='0'&&inc<='9') { x=(x<<3)+(x<<1)+(inc-'0'), inc=getchar(); }
	x=x*sign; 
	return;
}
	int one[Mod+1];
	int tot;
	struct node
	{
		LL data;
		int next;	
	};
	node num[M];
	inline void add(const LL &key)
	{
		LL t=key%Mod+1;
		tot++;
		num[tot].next=one[t];
		num[tot].data=key;
		one[t]=tot;
		return;
	}
	inline bool find(const LL &key)
	{
		LL t=key%Mod+1;
		for(int i=one[t];i;i=num[i].next) 
			if(num[i].data==key) 
				return true;
		return false;
	}
	inline void del(const LL &key)
	{
		LL t=key%Mod+1;
		int i=0;
		for(i=one[t];i;i=num[i].next) 
			if(num[num[i].next].data==key) 
				break;
		if(i==0) return;
		num[num[i].next].data=-1;
		num[i].next=num[num[i].next].next;
		return;
	}
int main()
{
	rd(A); rd(B); rd(C);
	k[0]=1;
	add(k[0]);
	for(int i=1;i<=M-5e5;i++)
	{
		k[i]=(A*k[i-1]+k[i-1]%B)%C;
		if(find(k[i])) 
		{
			printf("%d",i);
			return 0;
		}
		add(k[i]);
	}
	puts("-1");
	return 0;
}

