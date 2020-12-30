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
namespace DSU{
    int fa[N];
    int getfather(int x){return x==fa[x] ? x : fa[x]=getfather(fa[x]);}
    void unite(int x,int y){fa[getfather(x)]=getfather(y);}
}

struct Mergeable_Heap{
    int val[N],ch[N][2],dis[N];
    int merge(int x,int y){
        if(!x||!y) return x+y;
        if((val[x]==val[y]&&x>y)||val[x]>val[y]) swap(x,y);
        ch[x][1]=merge(ch[x][1],y);
        if(dis[ch[x][1]]>dis[ch[x][0]]) swap(ch[x][0],ch[x][1]);
        dis[x]=dis[ch[x][1]]+1;
        return x;
    }
}H;
int n,m,a[N],Rt[N],vis[N];
int main()
{
    n=read(); m=read();
    for(int i=1;i<=n;i++) H.val[i]=read(),DSU::fa[i]=i,Rt[i]=i;
    for(int i=1;i<=m;i++){
        int opt=read();
        if(opt==1){
            int x=read(),y=read();
            if(vis[x]||vis[y]) continue;
            x=DSU::getfather(x),y=DSU::getfather(y);
            if(x==y) continue;
            DSU::unite(x,y);
            Rt[y]=H.merge(Rt[x],Rt[y]);
        }
        else{
            int x=read(); x=DSU::getfather(x);
            if(!Rt[x]){puts("-1"); continue;}
            printf("%d\n",H.val[Rt[x]]); vis[Rt[x]]=1;
            Rt[x]=H.merge(H.ch[Rt[x]][0],H.ch[Rt[x]][1]);
        }
    }
    return 0;
}