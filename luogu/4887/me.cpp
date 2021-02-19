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
const int M=16384;
int blk[N],a[N],n,m,k,B;
vector<int> num;

struct Query{
    int l,r,id;
    bool operator < (const Query &rhs) const{
        if(blk[l]==blk[rhs.l]) return r<rhs.r;
        else return blk[l]<blk[rhs.l];
    }
}Q[N];
struct node{
    int l,r,typ,id;
};
vector<node> v[N];
int f1[N],f2[N];//x:1~x-1, x:1~x
int t[M]; ll ans[N];

int main()
{
    n=read(); m=read(); k=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=0;i<M;i++)
        if(__builtin_popcount(i)==k) num.push_back(i);
    B=(int)sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=(i+B-1)/B;
    for(int i=1;i<=m;i++){
        Q[i].l=read(); Q[i].r=read(); Q[i].id=i;
    }
    sort(Q+1,Q+m+1);
    memset(t,0,sizeof(t));
    for(int i=1;i<=n;i++){
        f1[i]=t[a[i]];
        for(auto &u : num) t[u^a[i]]++;
        f2[i]=t[a[i]];
    }
    int l=1,r=1;
    for(int i=1;i<=m;i++){
        int L=l,R=r;
        while(L>Q[i].l) L--,ans[Q[i].id]-=f2[L];
        if(L!=l) v[r].push_back({L,l-1,1,Q[i].id}),l=L;
        while(R<Q[i].r) R++,ans[Q[i].id]+=f1[R];
        if(R!=r) v[l-1].push_back({r+1,R,-1,Q[i].id}),r=R;
        while(L<Q[i].l) ans[Q[i].id]+=f2[L],L++;
        if(L!=l) v[r].push_back({l,L-1,-1,Q[i].id}),l=L;
        while(R>Q[i].r) ans[Q[i].id]-=f1[R],R--;
        if(R!=r) v[l-1].push_back({R+1,r,1,Q[i].id}),r=R;
    }
    memset(t,0,sizeof(t));
    for(int i=1;i<=n;i++){
        for(auto &u : num) t[u^a[i]]++;
        for(auto &u : v[i]){
            for(int j=u.l;j<=u.r;j++) ans[u.id]+=u.typ*t[a[j]];
        }
    }
    for(int i=1;i<=m;i++) ans[Q[i].id]+=ans[Q[i-1].id];
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
    return 0;
}