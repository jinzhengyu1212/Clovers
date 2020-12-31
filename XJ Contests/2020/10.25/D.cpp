#include<bits/stdc++.h>
using namespace std;
const int MOD=998244353;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
int mul(int x,int y){return 1ll*x*y%MOD;}
int n,d,r;

int main(){
    scanf("%d%d%d",&n,&d,&r);
    if(r==n){
        printf("%d\n",n+d);
    }
    return 0;
}