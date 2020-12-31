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
const int N=400005;
char s[3][N];
int n,Q;

namespace DSU{
    int fa[N];
    void init(){for(int i=1;i<=n*2;i++) fa[i]=i;}
    int getfather(int x){return x==fa[x] ? x : fa[x]=getfather(fa[x]);}
    void unite(int x,int y){fa[getfather(x)]=getfather(y);}
    bool same(int x,int y){return getfather(x)==getfather(y);}
}

int dep[N],a[N],tot=0;
void init(){
    n=read(); Q=read();
    scanf("%s",s[1]+1); scanf("%s",s[2]+1);
    DSU::init();
    for(int i=1;i<=n;i++){
        if(i<n){
            if(s[1][i]=='0'&&s[1][i+1]=='0') DSU::unite(i,i+1);
            if(s[2][i]=='0'&&s[2][i+1]=='0') DSU::unite(i+n,i+n+1);
        }
        if(s[1][i]=='0'&&s[2][i]=='0') DSU::unite(i,i+n);
    }
}

int vis[N];
void bfs(int S,int T){
    queue<int> q;
    q.push(S);
    for(int i=1;i<=2*n;i++) vis[i]=0; vis[S]=1;
    while(!q.empty()){
        int x=q.front(); q.pop();
        if(x==T){
            printf("%d\n",vis[T]-1);
            return;
        }
        int hx=(x>n)+1;
        int lx=(x-1)%n+1;
        if(hx==1&&s[2][lx]=='0'&&!vis[x+n]) q.push(x+n),vis[x+n]=vis[x]+1;
        if(hx==2&&s[1][lx]=='0'&&!vis[x+n]) q.push(x-n),vis[x-n]=vis[x]+1;
        if(s[hx][lx+1]=='0'&&!vis[x+1]) q.push(x+1),vis[x+1]=vis[x]+1;
    }
}

void solve(){
    while(Q--){
        int x=read(),y=read();
        if(!DSU::same(x,y)){
            puts("You have been confusional!");
            continue;
        }
        int hx=(x>n)+1, hy=(y>n)+1;
        int lx=(x-1)%n+1, ly=(y-1)%n+1;
        if(s[hx][lx]=='1'||s[hy][ly]=='1'){
            puts("You have been confusional!");
            continue;
        }
        if(lx>ly) swap(x,y);
        bfs(x,y);
    }
}

int main()
{
    init(); solve();
    return 0;
}