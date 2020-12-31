#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll x,ll y){
    if(!y) return x;
    return gcd(y,x%y);
}

int main(){
    ll n,m;
    scanf("%lld%lld",&n,&m);
    ll sum1=(n+m-1)*(n+m)/2;
    ll sum2=(n-1)*n/2;
    ll g=gcd(sum1,sum2);
    printf("%lld/%lld\n",sum2/g,sum1/g);
    return 0;
}