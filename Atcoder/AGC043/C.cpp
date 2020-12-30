#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD=998244353;
const int K=(int)1e18%MOD;
const int N=120000;
int qpow(int x,int y){
    int ret=1;
    while(y){
        if(y&1) ret=ret*x%MOD;
        x=x*x%MOD;
        y>>=1;
    }
    return ret;
}
vector<int> mp[4][N];
int n,m[4],sg[4][N],dp[4][N];

signed main(){
    scanf("%lld",&n);
    for(int t=1;t<=3;t++){
        scanf("%lld",&m[t]);
        for(int i=1;i<=m[t];i++){
            int x,y; scanf("%lld%lld",&x,&y);
            if(x>y) swap(x,y);
            mp[t][x].push_back(y);
        }
        for(int i=n;i>=1;i--){
            set<int> st; st.clear();
            for(int j=0;j<(int)mp[t][i].size();j++){
                int to=mp[t][i][j];
                st.insert(sg[t][to]);
            }
            while(st.count(sg[t][i])) sg[t][i]++;
        }
        //for(int i=1;i<=n;i++) printf("sg[i]=%d\n",sg[t][i]);
        for(int i=1;i<=n;i++) (dp[t][sg[t][i]]+=qpow(K,i))%=MOD;
    }
    int ans=0;
    for(int i=0;i<=1000;i++){
        for(int j=0;j<=1000;j++){
            (ans+=dp[1][i]*dp[2][j]%MOD*dp[3][i^j]%MOD)%=MOD;
        }
    }   
    cout<<ans<<endl;
    return 0;
}