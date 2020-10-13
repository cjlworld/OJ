// acw#244
#include<cmath>
#include<cstdio>
#include<iostream>

using namespace std;

const int N=1e5+5;

int sum[4*N];

int n;
int a[N];
int h[N];

struct Bits
{
	int c[N];
	inline int lowbit(int x)
	{
		return x&(-x);
	}
	void Update(int x,int y)
	{
		for(;x<=n;x+=lowbit(x)) 
			c[x]+=y;
	}
	int Fdkth(int x)
	{   // 因为倍增会停在下一个1之前的位置,所以不妨跳到 x-1,再把 pos+1.
		// 这一点与树上倍增原理相同。 
		int k=log2(n),pos=0;
		for(int i=k;i>=0;i--) {
			if(pos+(1<<i)<=n&&x>c[pos+(1<<i)]) 
				pos+=(1<<i),x-=c[pos];
		}
		return pos+1;
	}
}C;

int main()
{
//	freopen("1.in","r",stdin);
    int i;
    scanf("%d",&n);
    for(i=2;i<=n;i++) 
        scanf("%d",&a[i]);
    for(i=1;i<=n;i++) 
        C.Update(i,1);
    for(i=n;i>=1;i--) {
        h[i]=C.Fdkth(a[i]+1);
        C.Update(h[i],-1);
    }
    for(i=1;i<=n;i++) 
        printf("%d\n",h[i]);
    return 0;
}
