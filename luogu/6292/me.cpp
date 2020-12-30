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
const int N=400005;
char s[N];
int id[N],n,m; 
struct QUERY{
    int l,r,id;
    bool operator < (const QUERY &rhs) const{
        return r<rhs.r;
    }
}Q[N];

struct SAM{
    int maxlen[N],link[N],trans[N][26],tot=1,lst=1;
    void extend(int id,int pos){
        int cur=++tot,p; ::id[pos]=cur; maxlen[cur]=maxlen[lst]+1;
        for(p=lst;!trans[p][id]&&p;p=link[p]) trans[p][id]=cur;
        if(!p) link[cur]=1;
        else{
            int q=trans[p][id];
            if(maxlen[q]==maxlen[p]+1) link[cur]=q;
            else{
                int y=++tot; maxlen[y]=maxlen[p]+1;
                copy(trans[q],trans[q]+26,trans[y]);
                link[y]=link[q]; link[cur]=link[q]=y;
                for(;p&&trans[p][id]==q;p=link[p]) trans[p][id]=y;
            }
        }
        lst=cur;
    }
}S;

struct Segment_Tree{
    ll sum[N<<1]; int tag[N<<1];
    void pushup(int x){sum[x]=sum[x<<1]+sum[x<<1|1];}
    void pushdown(int x,int l,int mid,int r){
        if(!tag[x]) return;
        tag[x<<1]+=tag[x]; sum[x<<1]+=1ll*(mid-l+1)*tag[x];
        tag[x<<1|1]+=tag[x]; sum[x<<1|1]+=1ll*(r-mid)*tag[x];
        tag[x]=0;
    }
    void update(int x,int l,int r,int L,int R,int val){
        if(L<=l&&r<=R){
            sum[x]+=1ll*(r-l+1)*val; tag[x]+=val;
            return;
        }
        int mid=(l+r)>>1; pushdown(x,l,mid,r);
        if(mid>=L) update(x<<1,l,mid,L,R,val);
        if(mid<R) update(x<<1|1,mid+1,r,L,R,val);
        pushup(x);
    }
    ll query(int x,int l,int r,int L,int R){
        if(L<=l&&r<=R) return sum[x];
        int mid=(l+r)>>1; ll ret=0; pushdown(x,l,mid,r);
        if(mid>=L) ret+=query(x<<1,l,mid,L,R);
        if(mid<R) ret+=query(x<<1|1,mid+1,r,L,R);
        return ret;
    }
}tree;

namespace LCT{
    #define ls ch[x][0]
    #define rs ch[x][1]
    int ch[N][2],cov[N],fa[N],val[N];
    void DEL(int x){fa[x]=0; ch[x][0]=ch[x][1]=0;}
    bool isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
    bool getdir(int x){return ch[fa[x]][1]==x;}
    void pushdown(int x){
        if(!cov[x]) return;
        if(ls) cov[ls]=cov[x],val[ls]=cov[x];
        if(rs) cov[rs]=cov[x],val[rs]=cov[x];
        cov[x]=0;
    }
    void pushall(int x){if(!isroot(x)) pushall(fa[x]); pushdown(x);}
    void rotate(int x){
        int y=fa[x],z=fa[y];
        int dirx=getdir(x),diry=getdir(y);
        if(!isroot(y)) ch[z][diry]=x; fa[x]=z;
        ch[y][dirx]=ch[x][dirx^1]; fa[ch[x][dirx^1]]=y;
        ch[x][dirx^1]=y; fa[y]=x;
        DEL(0);
    }
    void splay(int x){
        pushall(x);
        while(!isroot(x)){
            if(!isroot(fa[x])){
                if(getdir(fa[x])==getdir(x)) rotate(fa[x]);
                else rotate(x);
            }
            rotate(x);
        }
    }
    void access(int x,int pos){
        int y=0;
        while(x){
            splay(x);
            if(val[x]){
                int len=S.maxlen[x],lenfa=S.maxlen[fa[x]];
                tree.update(1,1,n,val[x]-len+1,val[x]-lenfa,-1);
            }
            rs=y; y=x; x=fa[x];
        }
        val[y]=pos; cov[y]=pos;
        tree.update(1,1,n,1,pos,1);
    }
}

ll ans[N];
int main()
{
    scanf("%s",s+1); n=strlen(s+1);
    for(int i=1;i<=n;i++) S.extend(s[i]-'a',i);
    for(int i=2;i<=S.tot;i++) LCT::fa[i]=S.link[i];
    m=read();
    for(int i=1;i<=m;i++) Q[i].l=read(),Q[i].r=read(),Q[i].id=i;
    sort(Q+1,Q+m+1);
    for(int i=1,j=1;i<=n;i++){
        LCT::access(id[i],i);
        while(Q[j].r==i&&j<=m){
            ans[Q[j].id]=tree.query(1,1,n,Q[j].l,Q[j].r);
            j++;
        }
    }
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
    return 0;
}