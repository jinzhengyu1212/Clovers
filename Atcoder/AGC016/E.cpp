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
const int N=405;

int n,m;
vector<pii> v[N];
int vis[N],lst[N];

void init(){
    n=read(); m=read();
    for(int i=1;i<=m;i++){
        int x=read(),y=read();
        v[x].push_back(mk(y,i));
        v[y].push_back(mk(x,i));
    }
}

int valid=1;
int TT;
void dfs(int u,int ti){//is alive until ti
    if(!valid) return;
    for(auto & E : v[u]){
        int to=E.first;
        if(E.second==ti) continue;
        if(E.second<ti){
            if(vis[to]!=E.second&&vis[to]!=-1){
                valid=0;
                return;
            }
            if(E.second>lst[to]&&lst[to]!=-1){
                valid=0;
                return;
            }
            vis[to]=E.second;
            dfs(to,E.second);
        }
        else{
            if(lst[to]==-1) lst[to]=E.second;
            else checkmin(lst[to],E.second);
        }
    }
}

struct node{
    int id,ti;
    bool operator < (const node &rhs) const{
        return ti>rhs.ti;
    }
};
priority_queue<node> Q;

int alive[N];
int bl[N][N];
void solve(int now){
    TT=now;
    memset(vis,-1,sizeof(vis));
    memset(lst,-1,sizeof(lst));
    valid=1; vis[now]=m+1;
    dfs(now,m+1);
    if(!valid) return;
    while(!Q.empty()) Q.pop();
    for(int i=1;i<=n;i++){
        if(lst[i]<vis[i]&&lst[i]!=-1) return;
        if(vis[i]!=-1||lst[i]==-1) continue;
        Q.push({i,lst[i]});
    }
    while(!Q.empty()){
        node U=Q.top(); Q.pop();
        int u=U.id;
        if(vis[u]!=-1) continue; 
        vis[u]=U.ti;
        for(auto &E : v[u]){
            if(E.second<U.ti) continue;
            int to=E.first;
            if(vis[to]>E.second) return;
            if(lst[to]>E.second||lst[to]==-1){
                lst[to]=E.second;
                Q.push({to,lst[to]});
            }
        }
    }
    alive[now]=1;
    for(int i=1;i<=n;i++) {
        if(vis[i]==-1){
            bl[now][i]=1;
        }
    }
}

int main()
{
    init();
    int ans=0;
    for(int i=1;i<=n;i++) solve(i);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(alive[i]&&alive[j]){
                ans+=bl[i][j];
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}