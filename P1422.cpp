#include<bits/stdc++.h>
using namespace std;
/*���õ�����150ǧ��ʱ�����²��ְ�ÿǧ��ʱ0.4463Ԫִ�У�
���õ�����151~400ǧ��ʱ�Ĳ��ְ�ÿǧ��ʱ0.4663Ԫִ�У�
���õ�����401ǧ��ʱ�����ϲ��ְ�ÿǧ��ʱ0.5663Ԫִ��*/
int n;
double tot;
int main()
{
 	cin>>n;
 	if(n>=150) tot+=0.4463*150.0;
 	else { tot+=0.4463*n; }
	if(n>=400) {
		tot+=0.4663*250.0;
		tot+=0.5663*(n-400);
	}
	else if(n>=150) {
		tot+=0.4663*(n-150);
	}
	cout<<fixed<<setprecision(1)<<tot;
	return 0;
}

