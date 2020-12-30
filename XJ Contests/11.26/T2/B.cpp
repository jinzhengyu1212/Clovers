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
int n; pii a[N];

struct Segment_Tree{
    int sum[N<<2];
    void pushup(int x){sum[x]=sum[x<<1]+sum[x<<1|1];}
    void build(int x,int l,int r){
        if(l==r){sum[x]=1; return;}
        int mid=(l+r)>>1;
        build(x<<1,l,mid); build(x<<1|1,mid+1,r);
        pushup(x);
    }
    void update(int x,int l,int r,int pos){
        if(l==r){sum[x]=0; return;}
        int mid=(l+r)>>1;
        if(mid>=pos) update(x<<1,l,mid,pos);
        else update(x<<1|1,mid+1,r,pos);
        pushup(x);
    }
    int query(int x,int l,int r,int k){
        if(l==r){return l;}
        int mid=(l+r)>>1;
        if(k>sum[x<<1]) return query(x<<1|1,mid+1,r,k-sum[x<<1]);
        else return query(x<<1,l,mid,k);
    }
}tree;

int ans[N];
int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i].first=read(),a[i].second=read();
    sort(a+1,a+n+1);
    tree.build(1,1,n);
    for(int i=1;i<=n;i++){
        int rest=n-i+1;
        if(a[i].second+1>rest){
            puts("impossible");
            return 0;
        }
        int pos=min(a[i].second+1,rest-a[i].second);
        int tmp=tree.query(1,1,n,pos);
        ans[tmp]=a[i].first;
        tree.update(1,1,n,tmp);
    }
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    puts("");
    return 0;
}