#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=500005;

ll a,b,c,d;
void solve(){
    scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
    if(a>b*c||(a==b*c&&d<c)){
        puts("-1");
        return;
    }
    if(a<=d*b){
        printf("%lld\n",a);
    }
    else{
        
    }
}

int main(){
    int T=1; scanf("%d",&T);
    while(T--){
        solve();
    }
    return 0;
}