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
const int M=200005;
int Rt[M],n,m,lstans=0,typ,Q,tot=0; pii E[M];
void decode(int &l,int &r){
    if(typ>0){
        l=(l+typ*lstans)%m+1;
        r=(r+typ*lstans)%m+1;
    }
    if(l>r) swap(l,r);
}
struct Chairman_Tree{
    int ls[M<<5],rs[M<<5],sum[M<<5];
    void pushup(int x){sum[x]=sum[ls[x]]+sum[rs[x]];}
    void insert(int x,int y,int l,int r,int pos,int val){
        if(l==r){sum[x]=sum[y]+val; return;}
        int mid=(l+r)>>1;
        if(mid>=pos) ls[x]=++tot,rs[x]=rs[y],insert(ls[x],ls[y],l,mid,pos,val);
        else rs[x]=++tot,ls[x]=ls[y],insert(rs[x],rs[y],mid+1,r,pos,val);
        pushup(x);
    }
    int query(int x,int l,int r,int L,int R){
        if(L<=l&&r<=R) return sum[x];
        int mid=(l+r)>>1,ret=0;
        if(mid>=L) ret+=query(ls[x],l,mid,L,R);
        if(mid<R) ret+=query(rs[x],mid+1,r,L,R);
        return ret;
    }
}T;

namespace LCT{
    #define ls ch[x][0]
    #define rs ch[x][1]
    int ch[N+M][2],rev[N+M],fa[N+M],mi[N+M],val[N+M];
    void init(){memset(val,0x3f,sizeof(val));}
    int isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
    int getdir(int x){return ch[fa[x]][1]==x;}
    void pushup(int x){
        mi[x]=x; 
        if(val[mi[x]]>val[mi[ls]]) mi[x]=mi[ls];
        if(val[mi[x]]>val[mi[rs]]) mi[x]=mi[rs];
    }
    void pushdown(int x){
        if(rev[x]){
            swap(ch[ls][0],ch[ls][1]);
            swap(ch[rs][0],ch[rs][1]);
            rev[ls]^=1; rev[rs]^=1; rev[x]=0;
        }
    }
    void pushall(int x){if(!isroot(x)) pushall(fa[x]); pushdown(x);}
    void rotate(int x){
        int y=fa[x],z=fa[y],dirx=getdir(x),diry=getdir(y);
        ch[y][dirx]=ch[x][dirx^1]; fa[ch[x][dirx^1]]=y;
        if(!isroot(y)) ch[z][diry]=x; fa[x]=z;
        ch[x][dirx^1]=y; fa[y]=x;
        pushup(y); pushup(x);
    }
    void splay(int x){
        pushall(x);
        while(!isroot(x)){
            int y=fa[x];
            if(!isroot(y)){
                if(getdir(y)==getdir(x)) rotate(y);
                else rotate(x);
            }
            rotate(x);
        }
    }
    void access(int x){
        for(int y=0;x;y=x,x=fa[x]){
            splay(x);
            ch[x][1]=y; pushup(x); 
        }
    }
    void makeroot(int x){
        access(x); splay(x);
        rev[x]^=1; swap(ls,rs);
    }
    int findroot(int x){
        access(x); splay(x);
        while(ls) x=ls;
        splay(x);
        return x;
    }
    void link(int x,int y){makeroot(x); fa[x]=y;}
    void split(int x,int y){makeroot(x); access(y); splay(y);}
    void cut(int x,int y){split(x,y); ch[y][0]=0; fa[x]=0; pushup(y);}
}

int main()
{
    n=read(); m=read(); Q=read(); typ=read();
    for(int i=1;i<=m;i++) E[i].first=read(),E[i].second=read();
    LCT::init();
    for(int i=1;i<=m;i++){
        if(E[i].first==E[i].second){
            Rt[i]=Rt[i-1];
            continue;
        }
        Rt[i]=++tot; int pre=Rt[i];
        T.insert(Rt[i],Rt[i-1],1,m,i,1);
        int x=E[i].first,y=E[i].second;
        LCT::val[i+n]=i;
        if(LCT::findroot(x)!=LCT::findroot(y)){
            LCT::link(i+n,x); LCT::link(y,i+n);
        }
        else{
            LCT::split(x,y);
            int z=LCT::mi[y];
            LCT::cut(E[z-n].first,z); LCT::cut(E[z-n].second,z);
            LCT::link(i+n,x); LCT::link(y,i+n);
            Rt[i]=++tot;
            T.insert(Rt[i],pre,1,m,z-n,-1);
        }
    }   
    while(Q--){
        int l=read(),r=read(); decode(l,r);
        lstans=n-T.query(Rt[r],1,m,l,r);
        printf("%d\n",lstans);
    }
    return 0;
}