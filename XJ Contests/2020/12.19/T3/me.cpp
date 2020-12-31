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
const int MOD=323232323;
int _abs(int x){return x<0 ? -x : x;}
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
int mul(int x,int y){return 1ll*x*y%MOD;}
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
const int N=50005;
const int BL=200;
int typ,n,m,Q,B,block[N],li[N],ri[N],rem[N],top=0;
struct node{
    int x,y,ti;
};
node merge(node A,node B,int ti){
    if(A.ti<ti) A.x=1,A.y=0;
    if(B.ti<ti) B.x=1,B.y=0;
    return node{mul(A.x,B.x),add(mul(B.x,A.y),B.y),ti};
}

struct Segment_Tree{
    node tag[N<<2]; int ti;
    void pushdown(int x){
        tag[x<<1]=merge(tag[x<<1],tag[x],ti);
        tag[x<<1|1]=merge(tag[x<<1|1],tag[x],ti);
        tag[x]=node{1,0,0};
    }
    void build(int x,int l,int r){
        tag[x]=node{1,0,0};
        if(l==r) return;
        int mid=(l+r)>>1;
        build(x<<1,l,mid); build(x<<1|1,mid+1,r);
    }
    void update(int x,int l,int r,int L,int R,node A){
        if(L<=l&&r<=R){
            tag[x]=merge(tag[x],A,ti); 
            return;
        }
        int mid=(l+r)>>1;
        pushdown(x);
        if(mid>=L) update(x<<1,l,mid,L,R,A);
        if(mid<R) update(x<<1|1,mid+1,r,L,R,A);
    }
    node query(int x,int l,int r,int pos){
        if(l==r) return tag[x];
        int mid=(l+r)>>1; pushdown(x);
        if(mid>=pos) return query(x<<1,l,mid,pos);
        else return query(x<<1|1,mid+1,r,pos);
    }
}tree[252];
struct Upd{
    int l,r,p,q,ti;
}a[N];
void init(){
    typ=read();
    n=read(); m=read(); Q=read();
    checkmax(n,2);
    if(n>5) n=max(n,m), m=n;
    B=(m-1)/BL+1;
    for(int i=1;i<=m;i++) block[i]=(i-1)/BL+1;
    for(int i=1;i<=B;i++){
        tree[i].ti=0;
        tree[i].build(1,1,n);
        li[i]=BL*(i-1)+1,ri[i]=min(m,BL*i);
    }
    for(int i=1;i<=m;i++) a[i].ti=0;
}
void rebuild(int P,int ti){
    tree[P].ti=ti;
    for(int i=li[P];i<=ri[P];i++){
        if(a[i].ti!=0){
            tree[P].update(1,1,n,a[i].l,a[i].r,node{a[i].p,a[i].q,ti});
        }
    }
}

void query(int pos,int l,int r){
    node ans=node{1,0,inf};
    for(int i=l;i<=min(r,ri[block[l]]);i++){
        if(a[i].ti==0||(a[i].l>pos||a[i].r<pos)) continue;
        ans=merge(ans,node{a[i].p,a[i].q,inf},0);
    }
    for(int i=block[l]+1;i<block[r];i++){
        ans=merge(ans,tree[i].query(1,1,n,pos),0);
    }    
    if(block[l]!=block[r]) 
        for(int i=li[block[r]];i<=r;i++){
            if(a[i].ti==0||(a[i].l>pos||a[i].r<pos)) continue;
            ans=merge(ans,node{a[i].p,a[i].q,inf},0);
        }
    printf("%d\n",ans.y);
}

void solve(){
    for(int ttt=1;ttt<=Q;ttt++){
        char opt[2]; scanf("%s",opt);
        if(opt[0]=='I'){
            int l=read(),r=read(),y=read(),p=read(),q=read();
            a[y].ti=ttt; a[y].l=l,a[y].r=r;
            a[y].p=p,a[y].q=q;
            rebuild(block[y],ttt);
            rem[++top]=y;
        }
        else if(opt[0]=='D'){
            int y=read(); a[rem[y]].ti=0;
            rebuild(block[rem[y]],ttt);
        }
        else {
            int pos=read(),l=read(),r=read();
            query(pos,l,r);
        }
    }
}

int main()
{
    init(); solve();
    return 0;
}