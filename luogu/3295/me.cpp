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
const int MOD=1e9+7;
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
int n,m,lg[N];
int idx(int pos,int bit){return n*bit+pos;}
int decode(int x){
    int bit=(x-1)/n;
    int pos=x-n*bit;
    return pos;
}
struct DSU{
    int fa[N*20];
    void init(){for(int i=1;i<=n*20;i++) fa[i]=i;}
    int getfather(int x){return x==fa[x] ? x : fa[x]=getfather(fa[x]);}
    void unite(int x,int y){
        x=getfather(x),y=getfather(y);
        fa[y]=x;
    }
}T;

void init(){
    n=read(); m=read();
    T.init();
    for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1; 
    for(int i=1;i<=m;i++){
        int l1=read(),r1=read(),l2=read(),r2=read();
        if(l1>l2) swap(l1,l2),swap(r1,r2);
        int sz=r1-l1+1;
        for(int j=19;j>=0;j--){
            if(sz>=(1<<j)){
                int x=idx(l1,j),y=idx(l2,j);
                T.unite(x,y);
                sz-=(1<<j); l1+=(1<<j); l2+=(1<<j);
            }
        }
    }
}

void solve(){
    for(int j=19;j>=1;j--){
        for(int i=1;i<=n;i++){
            int to=(1<<(j-1))+i;
            int now=idx(i,j),x=idx(i,j-1),y=idx(to,j-1);
            int k=T.getfather(now);
            if(k!=now){
                k=decode(k);
                T.unite(x,idx(k,j-1));
                T.unite(y,idx(k+(1<<(j-1)),j-1));
            }
        }
    }
    int sz=0;
    for(int i=1;i<=n;i++){
        int now=idx(i,0);
        if(T.getfather(now)==now) sz++;
    }
    printf("%lld\n",mul(9,qpow(10,sz-1)));
}

int main()
{
    init(); solve();
    return 0;
}