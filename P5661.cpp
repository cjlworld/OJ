#include<bits/stdc++.h>
using namespace std;
/*�����ļ��� ��һ�а���һ�������� nn������˳���¼��������
�������� n�У�ÿ�а��� 3 ������������ ����֮����һ���ո�ָ���
�� i�е�
�� 1 ����������� i����¼�����Ľ�ͨ���ߣ�0 ���������1 ����������
�� 2 ����������� i����¼�˳���Ʊ�� price_i
��������������� i����¼��ʼ�˳���ʱ�� t_i���� 0 ʱ�̵ķ���������
���Ǳ�֤���м�¼�ǰ��տ�ʼ�˳���ʱ��˳������ģ��Ҳ��������γ˳���¼������ͬһ���ӡ�*/
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
		else head++;//��֦��֦��֦������������������ 
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

