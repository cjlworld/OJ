#include<bits/stdc++.h>
using namespace std;
/*月用电量在150千瓦时及以下部分按每千瓦时0.4463元执行，
月用电量在151~400千瓦时的部分按每千瓦时0.4663元执行，
月用电量在401千瓦时及以上部分按每千瓦时0.5663元执行*/
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

