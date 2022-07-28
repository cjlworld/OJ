#include<bits/stdc++.h>
using namespace std;
/*       ***
    x      **
   ----------
         ***
        ***
   ----------
        ****             
*/
int n;
bool b[16];//第一行一个正整数 n表示可用的数集。第二行 n个正整数 ai表示可用的数。
int a[16];
int c[16];
int k1,k2;
int inc;
unsigned long long tot=0;
void Init()
{
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++) { scanf("%d",&a[i]); b[a[i]]=true; }
	return;
}
void print(int x,int y)
{
	cout<<endl<<"No."<<tot<<endl;
	cout<<inc<<endl;
	cout<<a[x]<<a[y]<<endl<<"---------"<<endl<<k1<<endl<<k2<<endl<<"---------\n"<<k1+k2*10<<endl;
}
bool OK(int d,int si)
{
	int size=0;
	int t;
	while(d!=0) {
		size++;
		t=d%10;
		if(!b[t]) return false;
		d=d/10;
	} 
	if(size==si) return true;
	return false;
}
void check_2(int c[16])
{
	inc=0;
	int i,j;
	for(i=1;i<=3;i++) { inc=inc*10+c[i]; }
	for(i=1;i<=n;i++) {
		k1=a[i]*inc;
		if(OK(k1,3)) {
			for(j=1;j<=n;j++) {
				k2=a[j]*inc;
				if(OK(k2,3)&&OK(k1+k2*10,4)) {
					tot++;
//					print(i,j);
				}
			}
		} 
	}
	return;
}
void dfs_1(int step)
{
	for(int i=1;i<=n;i++) {
		c[step]=a[i];
		if(step==3) check_2(c);
		else dfs_1(step+1);
		c[step]=0;
	}
}
int main()
{
// 	freopen("1.in","r",stdin);
	Init();
	dfs_1(1);
	cout<<tot;
	return 0;
}

