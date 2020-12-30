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
const int N=200005;
vector<int> v[N];
char s[N];
int n;
bool check(){for(int i=1;i<=n;i++) if(s[i]=='0') return 0; return 1;}
bool check0(){for(int i=1;i<=n;i++) if(s[i]=='1') return 0;return 1;}

namespace solver1{
    int mx1[N],mx2[N];
    void dfs1(int u,int f){
        for(auto &to : v[u]){
            if(to==f) continue;
            dfs1(to,u);
            if(mx1[to]+1>mx1[u]){
                mx2[u]=mx1[u];
                mx1[u]=mx1[to]+1;
            }
            else if(mx1[to]+1>mx2[u]) mx2[u]=mx1[to]+1;
        }
    }
    int up[N];
    void dfs2(int u,int f){
        if(f!=-1){
            up[u]=up[f]+1;
            int tmp=(mx1[u]+1==mx1[f] ? mx2[f] : mx1[f]);
            checkmax(up[u],tmp+1);
        }
        for(auto &to : v[u]){
            if(to==f) continue;
            dfs2(to,u);
        }
    }
    void main(){
        dfs1(1,-1); dfs2(1,-1);
        ll ans=0;
        for(int i=1;i<=n;i++){
            int tmp1,tmp2;
            if(up[i]>mx1[i]){
                tmp1=up[i];
                tmp2=mx1[i];
            }
            else{
                tmp1=mx1[i];
                tmp2=max(up[i],mx2[i]);
            }
            ans+=min(tmp1-1,tmp2+1)+1;
        }
        cout<<ans+1<<endl;
    }
}

namespace solver2{
    int mx1[N],mx2[N];
    int mi[N],bl[N],sum=0;
    void dfs1(int u,int f){
        if(s[u]=='1') bl[u]=1;
        for(auto &to : v[u]){
            if(to==f) continue;
            dfs1(to,u); bl[u]+=bl[to];
            if(bl[to]) checkmin(mi[u],mx1[to]+1);
            if(mx1[to]+1>mx1[u]) mx2[u]=mx1[u],mx1[u]=mx1[to]+1;
            else if(mx1[to]+1>mx2[u]) mx2[u]=mx1[to]+1;
        }
    }
    int up[N],fa[N];
    void dfs2(int u,int f){
        if(f!=-1){
            up[u]=up[f]+1; fa[u]=f;
            int tmp=(mx1[u]+1==mx1[f] ? mx2[f] : mx1[f]);
            checkmax(up[u],tmp+1);
            if(sum-bl[u]) checkmin(mi[u],up[u]);
        }
        for(auto &to : v[u]){
            if(to==f) continue;
            dfs2(to,u);
        }
    }
    void main(){
        for(int i=1;i<=n;i++) mi[i]=inf,sum+=(s[i]=='1');
        dfs1(1,-1); dfs2(1,-1);
        ll ans=0;
        for(int u=1;u<=n;u++){
            int Max1,Max2;
            if(up[u]>mx1[u]) Max1=up[u],Max2=mx1[u];
            else Max1=mx1[u],Max2=max(up[u],mx2[u]);
            int L=(s[u]=='0' ? mi[u] : 0);
            ans+=max(min(Max1-1,Max2+1)+1-L,0);
        }
        cout<<ans+1<<endl;
    }
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y);
        v[y].push_back(x);
    }
    scanf("%s",s+1);
    if(check0()){puts("1"); return 0;}
    if(check()){
        solver1::main();
        return 0;
    }
    else solver2::main();
    return 0;
}