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
const int N=200005;
const int M=1005;

/*struct Segment_Tree{
    int sum[N<<2],tag[N<<2];
    void pushup(int x){sum[x]=sum[x<<1]+sum[x<<1|1];}
    void pushdown(int x,int l,int mid,int r){
        if(tag[x]==-1) return;
        if(tag[x]==1){
            sum[x<<1]=mid-l+1;
            tag[x<<1]=1;
            sum[x<<1|1]=r-mid;
            tag[x<<1|1]=1;
        }
        else{
            sum[x<<1]=0; sum[x<<1|1]=0;
            tag[x<<1]=0; tag[x<<1|1]=0;
        }
        tag[x]=-1;
    }
    void build(int x,int l,int r){
        sum[x]=0; tag[x]=-1;
        if(l==r) return;
        int mid=(l+r)>>1; 
        build(x<<1,l,mid); build(x<<1|1,mid+1,r);
    }
    void update(int x,int l,int r,int L,int R,int bl){
        if(L<=l&&r<=R){
            if(bl==0){
                sum[x]=0;
                tag[x]=0;
            }
            else{
                sum[x]=r-l+1;
                tag[x]=1;
            }
            return;
        }
        int mid=(l+r)>>1;
        pushdown(x,l,mid,r);
        if(mid>=L) update(x<<1,l,mid,L,R,bl);
        if(mid<R) update(x<<1|1,mid+1,r,L,R,bl);
        pushup(x);      
    }
    int query(int x,int l,int r,int pos){
        if(l==r){return sum[x];}
        int mid=(l+r)>>1;
        pushdown(x,l,mid,r);
        if(mid>=pos) return query(x<<1,l,mid,pos);
        else return query(x<<1|1,mid+1,r,pos);
    }
};*/

int n,Q; ll a[N]; ll sum=0;
namespace solver1{
    ll sum[N],cnt[N]; int vis[N];
    void query(){
        for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i]*i,cnt[i]=cnt[i-1]+a[i];
        //for(int i=1;i<=n;i++) cout<<a[i]<<" "; cout<<endl;
        ll ans=INF,pos=-1;
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                ll cntl=cnt[i],cntr=cnt[n]-cnt[i];
                if(ans>cntl*i-sum[i]+(sum[n]-sum[i])-cntr*i)
                    ans=cntl*i-sum[i]+(sum[n]-sum[i])-cntr*i,pos=i;
            }
        }
        printf("%lld\n",pos);
    }
    void main(){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++) a[i]=read();
        while(Q--){
            int opt=read();
            if(opt==1){
                int x=read(),k=read();
                a[x]+=k;
            }
            else if(opt==2){
                int x=read(),k=read();
                a[x]-=k;
            }
            else if(opt==3){
                int l=read(),r=read();
                for(int i=l;i<=r;i++) vis[i]=0;
            }
            else{
                int l=read(),r=read();
                for(int i=l;i<=r;i++) vis[i]=1;
            }
            query();
        }
    }
}

struct BIT{
    ll a[N];
    int lowbit(int x){return x&(-x);}
    void update(int x,int add){
        for(int i=x;i<=n;i+=lowbit(i)) a[i]+=add;
    }
    ll query(int x){
        ll ret=0;
        for(int i=x;i;i-=lowbit(i)) ret+=a[i];
        return ret;
    }
}tree1;

int findmid(){
    int l=1,r=n,mid,best;
    while(l<=r){
        mid=(l+r)>>1;
        if(tree1.query(mid)>=(sum+1)/2) best=mid,r=mid-1;
        else l=mid+1;
    }
    return best;
}

void init(){
    for(int i=1;i<=n;i++){
        a[i]=read();
        tree1.update(i,a[i]);
        sum+=a[i];
    }
}

void solve(){
    while(Q--){
        int opt=read();
        if(opt==1){
            int x=read(),k=read();
            sum+=k; tree1.update(x,k);
        }
        else if(opt==2){
            int x=read(),k=read();
            sum-=k; tree1.update(x,-k);
        }
        int mid=findmid();
        printf("%d\n",mid);
    }
}

int main()
{
    n=read(); Q=read();
    init();
    solve();
    return 0;
}