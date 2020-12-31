#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=120000;
const int inf=(int)5e18;
int n,k,dp[N],a[N],l,r,sum[N];
multiset<int> st;
void subtask1(){
    for(int i=l;i<=n;i++){
        for(int j=max(1ll,i-r+1);j<=i-l+1;j++){
            st.insert(sum[i]-sum[j-1]);
        }
    }
    int ans=0;
    while(k--){
        ans+=*st.rbegin();
        st.erase(--st.end());
    }
    cout<<ans<<endl;
}

void subtask2(){
    int ans=-inf,sum=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,sum+a[i]);
        sum=max(0ll,sum+a[i]);
    }
    cout<<ans<<endl;
}

signed main(){
    scanf("%lld%lld%lld%lld",&n,&k,&l,&r);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
    if(n<=1000||l==r){
        subtask1();
        return 0;
    }
    if(k==1){
        subtask2();
        return 0;
    }
}