#include<cstdio>
#include<iostream>
using namespace std;
const int N=256;
char a[N];
int main()
{
    int i,j;
    int x=0,y,z;
    int tmp=1;
    scanf("%s",a+1);
    for(i=1;i<=11;i++) {
        if(i==2||i==6) 
            continue;
        x=x+(a[i]-'0')*tmp;
        tmp++;
    }
    x=x%11;
    if((x!=10&&x==a[13]-'0')||(x==10&&a[13]=='X'))
        puts("Right");
    else {
        a[13]='\0';
        printf("%s",a+1);
        putchar((x==10) ? 'X' : ('0'+x) );
    }
    return 0;
}
