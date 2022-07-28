#include<bits/stdc++.h>
using namespace std;
/*输入文件的 第一行包含一个正整数 nn，代表乘车记录的数量。
接下来的 n行，每行包含 3 个整数，相邻 两数之间以一个空格分隔。
第 i行的
第 1 个整数代表第 i条记录乘坐的交通工具，0 代表地铁，1 代表公交车；
第 2 个整数代表第 i条记录乘车的票价 price_i
第三个整数代表第 i条记录开始乘车的时间 t_i（距 0 时刻的分钟数）。
我们保证出行记录是按照开始乘车的时间顺序给出的，且不会有两次乘车记录出现在同一分钟。*/
int n;
const int N=1e5+5;
struct ticket
{
	int kind;
	int t;
	int price;
};
ticket a[N];
ticket q[N];
long long head=0,tail=0;
unsigned long long tot=0;
void print();
void Init()
{
	int i,j;
	cin>>n;
	for(i=1;i<=n;i++) {
		scanf("%d%d%d",&a[i].kind,&a[i].price,&a[i].t); 
	}
	return;
}
int find(int t,int price)
{
//	print();
	if(head>=tail) return 0;
	int i,j;
	for(j=head+1;j<=tail;j++) {
		if(q[j].kind) continue;
		if(t-q[j].t<=45) {
			if(price<=q[j].price) { q[j].t=0; q[j].kind=1; q[j].price=0; break; }	
		}
		else head++;//剪枝剪枝剪枝！！！！！！！！！ 
	} 
//	print();
	if(j>tail) return price;
	else return 0;
}
void print()
{
	cout<<"tot="<<tot<<endl;
	for(int i=1;i<=tail;i++) {
		cout<<"{"<<q[i].kind<<","<<q[i].price<<","<<q[i].t<<"}"<<endl;
	}
	cout<<endl;
	return;
}
void Moni()
{
	int i,j;
	for(i=1;i<=n;i++) {
		if(a[i].kind) {
			tot+=find(a[i].t,a[i].price);
		}
		else {
			tail++;
			q[tail]=a[i];
			tot+=a[i].price;
		}
	}
	return;
}
int main()
{
 //	freopen("1.in","r",stdin);
	Init();
	Moni();
	cout<<tot;
	return 0;
}

