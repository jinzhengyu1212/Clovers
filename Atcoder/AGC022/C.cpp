/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e9;
const ll INF=(ll)5e18;
const int MOD=998244353;
int _abs(int x){return x<0 ? -x : x;}
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
#define mul(x,y) (ll)(x)*(y)%MOD
void Add(int &x,int y){x+=y; if(x>=MOD) x-=MOD;}
void Sub(int &x,int y){x-=y; if(x<0) x+=MOD;}
void Mul(int &x,int y){x=mul(x,y);}
int qpow(int x,int y){int ret=1; while(y){if(y&1) ret=mul(ret,x); x=mul(x,x); y>>=1;} return ret;}
void checkmin(int &x,int y){if(x>y) x=y;}
void checkmax(int &x,int y){if(x<y) x=y;}
void checkmin(ll &x,ll y){if(x>y) x=y;}
void checkmax(ll &x,ll y){if(x<y) x=y;}
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=55;
vector<pii> v[N];
int n,a[N],b[N];
int bl[N],vis[N];
ll ans=0; int able=0;

bool dfs(int u,int fin){
    if(u==fin) return 1;
    vis[u]=1;
    for(auto &to : v[u]){
        if(!bl[to.second]||vis[to.first]) continue;
        if(dfs(to.first,fin)) return 1;
    }
    return 0;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++) b[i]=read();
    for(int i=1;i<=50;i++){
        for(int j=i;j<=50;j++){
            v[j].push_back(mk(j%i,i));
        }
    }
    for(int i=1;i<=50;i++) bl[i]=1;
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        if(!dfs(a[i],b[i])){puts("-1"); return 0;} 
    }
    for(int i=50;i>=1;i--){
        bl[i]=0; int flag=1;
        for(int j=i-1;j>=0;j--) bl[j]=1;
        for(int j=1;j<=n;j++){
            memset(vis,0,sizeof(vis));
            if(!dfs(a[j],b[j])){flag=0; break;} 
        }
        if(!flag) bl[i]=1;
    }
    for(int i=50;i>=1;i--) if(bl[i]) ans|=(1ll<<i);
    cout<<ans<<endl;
    return 0;
}