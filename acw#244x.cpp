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
	{   // ��Ϊ������ͣ����һ��1֮ǰ��λ��,���Բ������� x-1,�ٰ� pos+1.
		// ��һ�������ϱ���ԭ����ͬ�� 
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
