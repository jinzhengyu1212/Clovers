#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<ctime>
#include<climits>
#include<algorithm>
#include<vector>
#define ll long long
using namespace std;
const ll N=1000010,mod=1e9+7;
struct node
{
    ll to,nxt;
}edge[N*2];
vector<ll> v[31];
ll dp[N],w[N],head[N],gcnt,flag,n;
void add(ll x,ll y) {edge[++gcnt]=(node){y,head[x]},head[x]=gcnt;}
void dfs(ll x,ll fa)
{
    ll i,y;
    if(x!=1)
        if(flag==2) dp[x]=max(dp[x],dp[fa]+(w[fa]^w[x]));  
        else if(flag==3) dp[x]=max(dp[x],dp[fa]+(w[fa]|w[x]));
    if(flag==1)
    {
        for(i=0;i<=30;i++)
        {
            if(v[i].size()!=0) dp[x]=max(dp[x],dp[v[i][v[i].size()-1]]+(w[v[i][v[i].size()-1]]&w[x]));
            if((1LL<<i)&w[x]) v[i].push_back(x); 
        }
    }
    for(i=head[x];i!=-1;i=edge[i].nxt)
    {
        y=edge[i].to;
        if(y==fa) continue;
        dfs(y,x);
    }
    if(flag==1) for(i=0;i<=30;i++) if(!v[i].empty()) if((1LL<<i)&w[x]) v[i].pop_back();   
}
int main()
{
    memset(head,-1,sizeof(head)),gcnt=-1;
    ll i,j,x,ans=0;
    char ch[10];
    scanf("%lld%s",&n,ch+1);
    if(ch[1]=='A') flag=1;
    else if(ch[1]=='X') flag=2;
    else flag=3;
    for(i=1;i<=n;i++) scanf("%lld",&w[i]);
    for(i=2;i<=n;i++) scanf("%lld",&x),add(x,i);
    dfs(1,1);
    for(i=1;i<=n;i++) dp[i]+=w[i],dp[i]%=mod,(ans+=(i*dp[i])%mod)%=mod;
    cout<<ans<<endl;
    return ~~(0-0);
}