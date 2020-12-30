#include<bits/stdc++.h>
using namespace std;
#define int long long 
int n,a,b;
signed main(){
    scanf("%lld%lld%lld",&n,&a,&b);
    if((b-a)%2==0){
        printf("%lld\n",(b-a)/2);
    }
    else{
        int ans=min(b-1,n-a);
        int tmpb=b-a; ans=min(ans,(tmpb-1)/2+a);
        int tmpa=a+(n-b)+1; ans=min(ans,(n-tmpa)/2+n-b+1);
        printf("%lld\n",ans);
    }
    return 0;
}