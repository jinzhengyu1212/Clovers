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
const int M=500005;

int n,m;
struct Edge{
    int x,y,l,w;
}E[M];

void init(){
    n=read(); m=read();
    for(int i=1;i<=m;i++){
        E[i].x=read(),E[i].y=read(),E[i].l=read(),E[i].w=read(); 
        if(E[i].x>E[i].y) swap(E[i].x,E[i].y);
    }
}

namespace solver1{
    int tot=0;
    struct EEEE{
        int from,to,dis;
        bool operator < (const EEEE &rhs) const{
            return dis<rhs.dis;
        }
    }Edg[2000002];
    namespace DSU{
        int fa[N];
        int getfather(int x){
            if(x==fa[x]) return x;
            return fa[x]=getfather(fa[x]);
        }
        void unite(int x,int y){
            x=getfather(x); y=getfather(y);
            fa[x]=y;
        }
        bool same(int x,int y){return getfather(x)==getfather(y);}
    }
    void kruskal(){
        sort(Edg+1,Edg+tot+1);
        for(int i=1;i<=n;i++) DSU::fa[i]=i;
        int cnt=0; ll ans=0;
        for(int i=1;i<=tot;i++){
            if(cnt==n-1) break;
            int x=Edg[i].from,y=Edg[i].to;
            if(DSU::same(x,y)) continue;
            ans+=Edg[i].dis; cnt++;
            DSU::unite(x,y);
        }
        printf("%lld\n",ans);
    }
    void init(){
        for(int i=1;i<=m;i++){
            for(int j=0;j<E[i].l;j++){
                Edg[++tot].from=E[i].x+j;
                Edg[tot].to=E[i].y+j;
                Edg[tot].dis=E[i].w;
            }
        }
    }
    void main(){
        init();
        kruskal();
    }
}

bool check1(){
    for(int i=1;i<=m;i++) if(E[i].l!=1) return 0;
    return 1;
}


void solve(){
    if((n<=5005&&m<=5005)||check1()){
        solver1::main();
        return;
    }
}

int main()
{
    init(); solve();
    return 0;
}