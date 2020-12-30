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
const int N=500005;
int tot,n,L,R,k,val[N],m;
ll ans=0;
struct Chairman_Tree{
    int ls[N<<5],rs[N<<5],sum[N<<5];
    void pushup(int x){sum[x]=sum[ls[x]]+sum[rs[x]];}
    void build(int x,int l,int r){
        if(l==r){sum[x]=0; return;}
        int mid=(l+r)>>1;
        ls[x]=++tot; rs[x]=++tot;
        build(ls[x],l,mid); build(rs[x],mid+1,r);
        pushup(x);
    }
    void insert(int x,int y,int l,int r,int pos){
        if(l==r){sum[x]=sum[y]+1; return;}
        int mid=(l+r)>>1;
        if(mid>=pos) ls[x]=++tot,rs[x]=rs[y],insert(ls[x],ls[y],l,mid,pos);
        else rs[x]=++tot,ls[x]=ls[y],insert(rs[x],rs[y],mid+1,r,pos);
        pushup(x);
    }
    int query(int x,int y,int l,int r,int k){
        if(l==r) return l;
        int mid=(l+r)>>1,tmp=sum[ls[x]]-sum[ls[y]];
        if(k>tmp) return query(rs[x],rs[y],mid+1,r,k-tmp);
        else return query(ls[x],ls[y],l,mid,k);
    }
}tree;
priority_queue<pii> q;
int now[N],a[N];

int main()
{
    n=read(); k=read(); L=read(); R=read();
    tot=n;
    for(int i=1;i<=n;i++) a[i]=read()+a[i-1],val[i]=a[i];
    val[n+1]=0;
    sort(val+1,val+n+2); m=unique(val+1,val+n+2)-val-1;
    for(int i=0;i<=n;i++) a[i]=lower_bound(val+1,val+m+1,a[i])-val;
    tree.build(0,1,m);
    for(int i=1;i<=n;i++) tree.insert(i,i-1,1,m,a[i-1]);
    for(int i=L;i<=n;i++){
        now[i]=1; int v=tree.query(i-L+1,max(0,i-R),1,m,now[i]);
        //out(i); outln(val[v]);
        q.push(mk(val[a[i]]-val[v],i));
    }
    while(k--){
        pii u=q.top(); q.pop();
        ans+=u.first;
        if(now[u.second]==min(R-L+1,u.second-L+1)) continue;
        now[u.second]++;
        int v=tree.query(u.second-L+1,max(0,u.second-R),1,m,now[u.second]);
        q.push(mk(val[a[u.second]]-val[v],u.second));
    }
    cout<<ans<<endl;
    return 0;
}
//第一次肯定是选最小值，可以用st表，但是后面就不知道怎么求第k大了，然后就上了主席树。。
//其实可以把要求最小值的区间也扔进去，然后就可以RMQ了