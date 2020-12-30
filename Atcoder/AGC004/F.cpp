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
const int N=100005;
int n,m,in[N];
vector<int> v[N];
namespace solver1{
    int dp[N],dep[N];
    void dfs(int u,int f){
        dp[u]=(dep[u]&1 ? -1 : 1);
        for(auto &to : v[u]){
            if(to==f) continue;
            dep[to]=dep[u]+1;
            dfs(to,u); dp[u]+=dp[to];
        }
    }
    void main(){
        if(n&1) {puts("-1"); return;}
        int ans=0;
        dfs(1,-1);
        for(int i=1;i<=n;i++) ans+=_abs(dp[i]);
        if(dp[1]) puts("-1");
        else printf("%d\n",ans);
    }
}

namespace solver2{
    vector<int> cir; int a[N],incir[N],vis[N];
    stack<int> stk;
    void dfs1(int u,int f){
        vis[u]=1; stk.push(u);
        for(auto &to : v[u]){
            if(to==f||incir[to]) continue;
            if(vis[to]){
                while(stk.top()!=to){
                    incir[stk.top()]=1;
                    cir.push_back(stk.top());
                    stk.pop();
                }
                incir[stk.top()]=1; cir.push_back(stk.top());
                stk.pop();
            }
            else dfs1(to,u);
        }
        if(!stk.empty()&&stk.top()==u) stk.pop();
    }
    
    int dp[N],dep[N];
    void dfs2(int u,int f){
        vis[u]=1;
        dp[u]=(dep[u]&1 ? -1 : 1);
        for(auto &to : v[u]){
            if(to==f||vis[to]) continue;
            dep[to]=dep[u]+1;
            dfs2(to,u); dp[u]+=dp[to];
        }
    }
    void main(){
        if(n&1) {puts("-1"); return;}
        int ans=0;
        dfs1(1,-1);
        memset(vis,0,sizeof(vis));
        int Rt=cir[0]; dfs2(Rt,-1);
        int m=0;
        for(auto &to : cir) a[++m]=dp[to];
        if(m%2==0){
            if(dp[Rt]){puts("-1"); return;}
            sort(a+1,a+m+1);
            for(int i=1;i<=m;i++) ans+=_abs(a[m/2]-a[i]);
            for(int i=1;i<=n;i++) if(!incir[i]) ans+=_abs(dp[i]);
        }
        else{
            int tmp=dp[Rt]/2;
            for(auto &to : cir) dp[to]-=tmp;
            for(int i=1;i<=n;i++) ans+=_abs(dp[i]);
        }
        cout<<ans<<endl;
    }
}

int main()
{
    n=read(); m=read();
    for(int i=1;i<=m;i++){
        int x=read(),y=read();
        v[x].push_back(y);
        v[y].push_back(x);
        in[x]++; in[y]++;
    }
    if(m==n-1){
        solver1::main();
        return 0;
    }
    else solver2::main();
    return 0;
}