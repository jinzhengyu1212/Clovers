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
const ll INF=(ll)5e16;
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
const int N=500005;
int a[N],mx[N],n,val[N],m;

namespace solver1{
    ll dp[2005][2005]; 
    void main(){
        memset(dp,0x3f,sizeof(dp));
        dp[1][0]=0;
        for(int i=1;i<n;i++){
            for(int j=0;j<=i;j++) if(j!=mx[i]){
                if(i+1==mx[i+1]){
                    checkmin(dp[i+1][mx[i]],dp[i][j]);
                    checkmin(dp[i+1][j],dp[i][j]);
                }
                else{
                    checkmin(dp[i+1][j],dp[i][j]+a[mx[i]]-a[i+1]);
                    if(a[i+1]>a[j]) checkmin(dp[i+1][i+1],dp[i][j]);
                    else checkmin(dp[i+1][j],dp[i][j]+a[j]-a[i+1]);
                }
            }
        }
        ll ans=INF;
        for(int i=1;i<=n;i++) checkmin(ans,dp[n][i]);
        cout<<ans<<endl;
    }
}
/*struct Segment_Tree{
    ll mi[N<<2],tag[N<<2],;
    void pushup(int x){
        mi[x]=min(mi[x<<1]+mi[x<<1|1]);
    }
    void pushdown(int x){
        if(tag[x]){
            mi[x<<1]+=tag[x]; tag[x<<1]+=tag[x];
            mi[x<<1|1]+=tag[x]; tag[x<<1|1]+=tag[x];
        }
        tag[x]=0;
    }
    void build(int x,int l,int r){
        if(l==r){mi[x]=(l==0 ? 0 : INF); return;}
        int mid=(l+r)>>1;
        build(x<<1,l,mid); build(x<<1|1,mid+1,r);
        pushup(x);
    }
    ll query(int x,int l,int r,int L,int R){
        if(L<=l&&r<=R) return mi[x];
        int mid=(l+r)>>1; ll ret=INF;
        pushdown(x);
        if(mid>=L) checkmin(ret,query(x<<1,l,mid,L,R));
        if(mid<R) checkmin(ret,query(x<<1|1,mid+1,L,R));
    }
    void update(int x,int l,int r,int L,int R,ll val){
        if(L<=l&&r<=R){
            mi[x]+=val; tag[x]+=val;
            return;
        }
        int mid=(l+r)>>1; pushdown(x);
        if(mid>=L) update(x<<1,l,mid,L,R,val);
        if(mid<R) update(x<<1|1,mid+1,r,L,R,val);
        pushup(x);
    }
    void insert(int x,int l,int r,int pos,ll val){
        if(l==r){checkmin(mi[x],val); return;}
        int mid=(l+r)>>1; pushdown(x);
        if(mid>=pos) insert(x<<1,l,mid,pos,val);
        else insert(x<<1|1,mid+1,r,pos,val);
        pushup(x);
    }
}tree;

namespace solver2{
    int val[N];
    void main(){
        for(int i=1;i<=n;i++) val[i]=a[i];
        sort(val+1,val+n+1); m=unique(val+1,val+n+1)-val-1;
        for(int i=1;i<=n;i++) a[i]=lower_bound(val+1,val+m+1,a[i])-val;
        tree.build(1,0,m);
        for(int i=1;i<n;i++){
            if(i+1==mx[i+1]){
                ll val=tree.mi[1];
                tree.insert(1,0,m,a[mx[i]],val);
            }
            else{
                tree.update(1,0,m,)
            }
        }
    }
}*/

int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++){
        if(a[i]>a[mx[i-1]]) mx[i]=i;
        else mx[i]=mx[i-1];
    }
    if(n<=2000){
        solver1::main();
        return 0;
    }
    return 0;
}