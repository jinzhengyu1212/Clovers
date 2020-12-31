#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=300005;
int n,a[N];

signed main(){
    scanf("%lld",&n); for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    int now=0,ans=0;
    for(int i=n;i>=1;i--){
        if(a[i]==1){
            if(now) now--,ans++;
        }
        else{
            if(a[i]%2==1){
                now+=(a[i]-3)/2;
                ans++;
            }
            else now+=a[i]/2;
        }
    }
    printf("%lld\n",ans+(now*2)/3);
    return 0;
}