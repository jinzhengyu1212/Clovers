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
struct node{
    int l,r,id;
    bool operator < (const node &rhs) const{
        return l<rhs.l;
    }
}E[M];
 
struct DSU{
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
}T;
 
void init(){
    n=read(); m=read(); sd=read();
    for(register int i=1;i<=n;++i) a[i]=read();
    for(register int i=1;i<=m;++i){
        int l=rd(),r=rd();
        if(l>r) swap(l,r);
        E[i].l=l; E[i].r=r; E[i].id=i;
    }
    T.init();
}
 
int stk[N],top=0,sum[N];
void solve(){
    int ret=0;
    sort(E+1,E+m+1);
    for(register int i=n,j=m;i>=1;--i){
        while(top&&a[stk[top]]<=a[i]){
            T.unite(stk[top],i);
            top--;
        }
        stk[++top]=i; sum[i]=top;
        while(E[j].l==i&&j){
            ret=T.val[T.find(E[j].r)];
            ans[E[j].id]=top-sum[ret]+1;
            j--;
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
