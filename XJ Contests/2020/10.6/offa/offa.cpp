#include<bits/stdc++.h>
using namespace std;
#define il inline
const int N=5000005;

il char gc()
{
    static char now[1<<20],*S,*T;
    if (T==S)
    {
        T=(S=now)+fread(now,1,1<<20,stdin);
        if (T==S) return EOF;
    }
    return *S++;
}//getchar
 
il int read()
{
    int res=0,sign=1;
    char c;
    while ((c=gc())<'0'||c>'9') if (c=='-') sign=-1;
    res=(c^48);
    while ((c=gc())>='0'&&c<='9') res=(res<<3)+(res<<1)+(c^48);
    return res*sign;
}

typedef long long ll;
const ll inf=(ll)1e18+5;

int n,a[N],m,b[N],p[N],pos[N],nxt[N],vis[N],best[N];
ll dp[N],pre[N],ans=0,whole[N];
int main(){
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++) p[i]=read();
    m=read();
    for(int i=1;i<=m;i++) b[i]=read(),pos[b[i]]=i;
    int now=-1;
    for(int i=n;i>=1;i--){
        if(pos[i]) now=i;
        nxt[i]=now;
    }
    int nowmax=0;
    dp[0]=0;
    for(int i=1;i<=m;i++) dp[i]=inf;
    for(int i=1;i<=n;i++){
        whole[i]=whole[i-1];
        if(!pos[a[i]]){
            if(p[i]<0) ans+=p[i];
            else{
                if(nxt[a[i]]==-1||nowmax<pos[nxt[a[i]]]) ans+=p[i];
                else pre[pos[nxt[a[i]]]]+=p[i];
            }
            continue;
        }
        int id=pos[a[i]];
        if(nowmax<id-1||(vis[id]&&p[i]<0)){
            ans+=p[i];
            continue;
        }
        if(dp[id-1]!=inf){
            if(dp[id]+whole[i-1]-whole[best[id]]+min(0,p[i])>
                    dp[id-1]+pre[id]+whole[i-1]-whole[best[id-1]]){
                dp[id]=dp[id-1]+pre[id]+whole[i-1]-whole[best[id-1]],best[id]=i;
            }
        }
        if(dp[id]!=inf) nowmax=max(nowmax,id);
        if(p[i]<0) whole[i]+=p[i];
        else vis[id]=1;
    }
    if(dp[m]>=1e17) puts("Impossible");
    else printf("%lld\n",dp[m]+whole[n]-whole[best[m]]+ans);
    return 0;
}