#include<bits/stdc++.h>
#define rint register int
using namespace std;
const int N=1000+24;
int n;
int a[N],b[N],c[N],ans[N];
inline void Hamult(int *a,int *b,int *c) //High_accuracy_Multiplication
{
	for(rint i=1;i<=c[0];i++) c[i]=0; 
	c[0]=0;
	int x=0;
	for(rint i=1;i<=b[0];i++)    
	{    
	  	x=0;//用于存放进位    
	    for(rint j=1;j<=a[0];j++)//对乘数每一位进行处理    
	    {    
	        c[i+j-1]+=a[j]*b[i]+x;//当前乘积+上次乘积进位+原数    
	        x=c[i+j-1]/10;    
    	    c[i+j-1]%=10;    
	    }    
	    c[i+a[0]]+=x;//进位    
	}    
	c[0]=a[0]+b[0]+10;
	while(c[c[0]]==0) c[0]--;
	return;
}
inline void Haadd(int *a,int *b,int *c)
{
	int i,j;
	int len=max(a[0],b[0]);
	int x=0,p=0;
	for(i=1;i<=len+1;i++) {
		c[i]=a[i]+b[i]+x;
		x=c[i]/10;
		c[i]=c[i]%10;
	}
	c[0]=len+1;
	while(c[c[0]]==0) c[0]--;
	return;
}
inline void Hatrans(char *ch,int *c)
{
	c[0]=strlen(ch);
	for(rint i=1;i<=c[0];i++) {
		c[c[0]-i+1]=ch[i]-'0';
	}
	return;
}
inline void Haget(char *ch)
{
	char inc='\0';
	int i=0;
	while(inc=getchar()) {
		if(inc>='0'&&inc<='9') break;
	}
	while(inc>='0'&&inc<='9') {
		ch[i]=inc; i++;
	}
	return;
}
inline void Haconver(int s,int *a)
{
	memset(a,0,sizeof(a));
	int i=0;
	while(s!=0) {
		a[++i]=s%10;
		s=s/10;
	}
	a[0]=i;
	return;
}
inline void Hacopy(int *a,int *c)
{
	for(rint i=0;i<=c[0];i++) {
		a[i]=c[i];
	}
	return;
}
int main()
{
	scanf("%d",&n);
	Haconver(1,a);
	for(rint i=1;i<=n;i++) {
		Haconver(i,b);
		Hamult(a,b,c);
		Hacopy(a,c);
		Haadd(ans,c,ans);
	}
	for(rint i=ans[0];i>=1;i--) printf("%d",ans[i]);
	return 0;
}

