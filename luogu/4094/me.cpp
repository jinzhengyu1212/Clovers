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

int tot,n,Q; char s[N];
struct Chairman_Tree{
    int ls[N<<5],rs[N<<5],sum[N<<5];
    void pushup(int x){sum[x]=sum[ls[x]]+sum[rs[x]];}
    void build(int x,int l,int r){
        if(l==r){sum[x]=0; return;}
        int mid=(l+r)>>1;
        build(ls[x],l,mid); build(rs[x],mid+1,r);
    }
    void insert(int x,int y,int l,int r,int pos){
        if(l==r){sum[x]=sum[y]+1; return;}
        int mid=(l+r)>>1;
        if(mid>=pos) ls[x]=++tot,rs[x]=rs[y],insert(ls[x],ls[y],l,mid,pos);
        else rs[x]=++tot,ls[x]=ls[y],insert(rs[x],rs[y],mid+1,r,pos);
        pushup(x);
    }   
    int query(int x,int y,int l,int r,int L,int R){
        if(L<=l&&r<=R){return sum[y]-sum[x];}
        int mid=(l+r)>>1,ret=0;
        if(mid>=L) ret+=query(ls[x],ls[y],l,mid,L,R);
        if(mid<R) ret+=query(rs[x],rs[y],mid+1,r,L,R);
        return ret;
    }
}tree;

struct SA{
    int sa[N],rk[N],oldrk[N],cnt[N],P[N],id[N];
    bool cmp(int x,int y,int w){
        return oldrk[x]==oldrk[y]&&oldrk[x+w]==oldrk[y+w];
    }
    void build(){
        int m=130,p;
        for(int i=1;i<=n;i++) ++cnt[rk[i]=s[i]];
        for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
        for(int i=n;i>=1;i--) sa[cnt[rk[i]]--]=i;
        for(int w=1;w<n;w<<=1,m=p){
            memset(cnt,0,sizeof(int)*(m+1));
            p=0;
            for(int i=n;i>n-w;i--) id[++p]=i;
            for(int i=1;i<=n;i++) if(sa[i]>w) id[++p]=sa[i]-w;
            for(int i=1;i<=n;i++) ++cnt[P[i]=rk[id[i]]];
            for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
            for(int i=n;i>=1;i--) sa[cnt[P[i]]--]=id[i];
            memcpy(oldrk,rk,sizeof(int)*(n+1));
            p=0;
            for(int i=1;i<=n;i++){
                rk[sa[i]]=(cmp(sa[i],sa[i-1],w) ? p : ++p);
            }
            if(p==n) break;
        }
    }
    int height[N];
    void build_height(){
        int k=0;
        for(int i=1;i<=n;i++){
            if(k) k--;
            while(s[i+k]==s[sa[rk[i]-1]+k]) k++;
            height[rk[i]]=k;
        }
    }
}S;
int st[N][20],lg[N];
int query(int l,int r){
    if(l>r) return inf;
    int sz=r-l+1,S=lg[sz];
    return min(st[l][S],st[r-(1<<S)+1][S]);
}

void init(){
    n=read(); Q=read(); tot=n;
    scanf("%s",s+1);
    S.build(); S.build_height();
    tree.build(0,1,n);
    for(int i=1;i<=n;i++) tree.insert(i,i-1,1,n,S.rk[i]);
    for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1; 
    for(int i=1;i<=n;i++) st[i][0]=S.height[i];
    for(int j=1;j<20;j++){
        for(int i=1;i<=n;i++){
            if(i+(1<<j)-1>n) break;
            int to=i+(1<<(j-1));
            st[i][j]=min(st[i][j-1],st[to][j-1]);
        }
    }
}

int findr(int from,int val){
    int l=from+1,r=n,mid,best=from;
    while(l<=r){
        mid=(l+r)>>1;
        if(query(from+1,mid)>=val) l=mid+1,best=mid;
        else r=mid-1;
    }
    return best;
}

int findl(int from,int val){
    int l=1,r=from-1,mid,best=from;
    while(l<=r){
        mid=(l+r)>>1;
        if(query(mid+1,from)>=val) r=mid-1,best=mid;
        else l=mid+1;
    }
    return best;
}

int A,B,C,D;
bool check(int mid){
    int L=findl(S.rk[C],mid),R=findr(S.rk[C],mid);
    int szR=B-mid+1;
    return tree.query(A-1,szR,1,n,L,R);
}

void solve(){
    while(Q--){
        A=read(); B=read(); C=read(); D=read();
        int l=1,r=min(B-A+1,D-C+1),mid,best=0;
        while(l<=r){
            mid=(l+r)>>1;
            if(check(mid)) l=mid+1,best=mid;
            else r=mid-1;
        }
        printf("%d\n",best);
    }
}

int main()
{
    init(); solve();
    return 0;
}