#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
const int N=700005;
int n,m,a[N],sum[N],Sum[N];

bool check(int mid,int p,int q){
    __int128_t tmp=sum[mid]+(__int128_t)Sum[mid]*p;
    return tmp>=q;
}
 
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    sort(a+1,a+n+1); reverse(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+a[i]*(1-i);
        Sum[i]=Sum[i-1]+a[i];
    }
    while(m--){
        int p,q; scanf("%lld%lld",&p,&q);
        if(p<=0){
            puts("-1");
            continue;
        }
        int l=1,r=min(n,p),mid,best=-1;
        while(l<=r){
            mid=(l+r)>>1;
            if(check(mid,p,q)) best=mid,r=mid-1;
            else l=mid+1;
        }
        printf("%lld\n",best);
    }
    return 0;
}