#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
typedef long long ll;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int n,m,a[N],deg[N],vis[N];
vector<int> d[N],v[N];

void init(){
    n=read(); m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        deg[x]++; deg[y]++;
        v[x].push_back(y); v[y].push_back(x);
    }
    for(int i=1;i<=m;i++){
        int k=read();
        for(int j=1;j<=k;j++){
            int x=read();
            d[i].push_back(x);
        }
    }
}

void solve(){
    for(int i=m;i>=1;i--){
        for(int j=0;j<(int)d[i].size();j++){
            int now=d[i][j];
            if(vis[now]) continue;
            deg[now]--;
            if(deg[now]==-1) d[i-1].push_back(now);
            for(int k=0;k<(int)v[now].size();k++){
                int to=v[now][k];
                deg[to]--;
                if(deg[to]==-1) d[i-1].push_back(to);
            }
            vis[now]=1;
        }
        for(int j=0;j<(int)d[i].size();j++){
            int now=d[i][j];
            if(!vis[now]) continue;
            deg[now]++;
            for(int k=0;k<(int)v[now].size();k++){
                int to=v[now][k];
                deg[to]++;
            }
            vis[now]=0;
        }
        //d[i].clear();
    }
    ll ans=0;
    for(int i=1;i<=n;i++) ans+=1ll*a[i];
    for(int i=0;i<(int)d[0].size();i++){
        int now=d[0][i];
        if(vis[now]) continue;
        ans-=1ll*a[now]; vis[now]=1;
    }
    printf("%lld\n",ans);
}

int main(){
    init(); solve();
    return 0;
}