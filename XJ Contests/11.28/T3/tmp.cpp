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
#define il inline
il char gc()
{
    static char now[1<<20],*S,*T;
    if (T==S)
    {
        T=(S=now)+fread(now,1,1<<20,stdin);
        if (T==S) return EOF;
    }
    return *S++;
}
il int read()
{
    int res=0,sign=1;
    char c;
    while ((c=gc())<'0'||c>'9') if (c=='-') sign=-1;
    res=(c^48);
    while ((c=gc())>='0'&&c<='9') res=(res<<3)+(res<<1)+(c^48);
    return res*sign;
}
const int N=1000005;
const int M=10000005;
unsigned sd;
int n,m,a[N];
int rd(){return (sd^=sd <<13, sd^=sd >>17, sd^=sd<<5)%n+1;}
int ans[M];
int fst[N],nxt[M],point[M],id[M],e=0;
void add_edge(int x,int y,int ID){
    e++; point[e]=y; id[e]=ID;
    nxt[e]=fst[x]; fst[x]=e;
}

namespace DSU{
    int fa[N],sz[N],val[N];
    void init(){for(register int i=1;i<=n;++i) fa[i]=i,sz[i]=1,val[i]=i;}
    il int find(int x){
        if(x==fa[x]) return x;
        return fa[x]=find(fa[x]);
    }
    il void unite(int x,int y){
        int tmp=y;
        x=find(x),y=find(y);
        if(x==y) return; 
        if(sz[x]>sz[y]) swap(x,y);
        fa[x]=y; val[y]=tmp; sz[y]+=sz[x];
    }
}

void init(){
    n=read(); m=read(); sd=read();
    memset(fst,-1,sizeof(fst));
    for(register int i=1;i<=n;++i) a[i]=read();
    for(register int i=1;i<=m;++i){
        int l=rd(),r=rd();
        if(l>r) swap(l,r);
        add_edge(l,r,i);
    }
    DSU::init();
}

int stk[N],top=0,sum[N];
void solve(){
    int ret=0;
    for(register int i=n;i>=1;--i){
        while(top&&a[stk[top]]<=a[i]){
            DSU::unite(stk[top],i);
            top--;
        }
        stk[++top]=i; sum[i]=top;
        for(register int E=fst[i];E!=-1;E=nxt[E]){
            ret=DSU::val[DSU::find(point[E])];
            ans[id[E]]=top-sum[ret]+1;
        }
    }
    ret=0;
    for(register int i=1;i<=m;++i){
        Add(ret,mul(i,ans[i]));
    }
    printf("%d\n",ret);
}

int main()
{
    init(); solve();
    return 0;
}