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
#define int long long
const int N=200005;
int n,m,Rt[N],tot=0,cnt=1;
struct Segment_Tree{
    ll sum[N<<5]; int ls[N<<5],rs[N<<5];
    stack<int> stk;
    void del(int x){sum[x]=ls[x]=rs[x]=0; stk.push(x);}
    int newnode(){int ret; if(!stk.empty()) ret=stk.top(),stk.pop(); else ret=++tot; return ret;}
    void pushup(int x){sum[x]=sum[ls[x]]+sum[rs[x]];}
    void update(int x,int l,int r,int pos,int val){
        if(l==r){sum[x]+=val; return;}
        int mid=(l+r)>>1;
        if(mid>=pos){
            if(!ls[x]) ls[x]=newnode();
            update(ls[x],l,mid,pos,val);
        }
        else{
            if(!rs[x]) rs[x]=newnode();
            update(rs[x],mid+1,r,pos,val);
        }
        pushup(x);
    }
    ll query(int x,int l,int r,int L,int R){
        if(L<=l&&r<=R) return sum[x];
        int mid=(l+r)>>1; ll ret=0;
        if(mid>=L&&ls[x]) ret+=query(ls[x],l,mid,L,R);
        if(mid<R&&rs[x]) ret+=query(rs[x],mid+1,r,L,R);
        return ret;
    }
    int find(int x,int l,int r,int k){
        if(l==r) return l;
        int mid=(l+r)>>1,tmp=sum[ls[x]];
        if(k>tmp) return find(rs[x],mid+1,r,k-tmp);
        else return find(ls[x],l,mid,k);
    }
    int merge(int x,int y){
        if(!x||!y) return x+y;
        sum[x]+=sum[y];
        ls[x]=merge(ls[x],ls[y]); rs[x]=merge(rs[x],rs[y]);
        del(y); return x;
    }
    void split(int x,int &y,int l,int r,int k){
        y=newnode(); 
        if(l==r){swap(sum[x],sum[y]); return;}
        int mid=(l+r)>>1;
        if(mid<k){
            if(rs[x]) split(rs[x],rs[y],mid+1,r,k);
        }
        else{
            swap(rs[x],rs[y]);
            if(ls[x]) split(ls[x],ls[y],l,mid,k);
        }
        pushup(x); pushup(y);
    }
}tree;

signed main()
{
    n=read(); m=read(); Rt[1]=++tot;
    for(int i=1;i<=n;i++){
        int x=read();
        tree.update(Rt[1],1,n,i,x);
    }
    for(int ttt=1;ttt<=m;ttt++){
        int opt=read();
        if(opt==0){
            int p=read(),x=read(),y=read();
            tree.split(Rt[p],Rt[++cnt],1,n,x);
            cnt++;
            if(y!=n) tree.split(Rt[cnt-1],Rt[cnt],1,n,y+1);
            if(y!=n) Rt[p]=tree.merge(Rt[p],Rt[cnt]),cnt--;
        }
        else if(opt==1){
            int p=read(),t=read();
            Rt[p]=tree.merge(Rt[p],Rt[t]);
        }
        else if(opt==2){
            int p=read(),x=read(),q=read();
            tree.update(Rt[p],1,n,q,x);
        }
        else if(opt==3){
            int p=read(),x=read(),y=read();
            printf("%lld\n",tree.query(Rt[p],1,n,x,y));
        }
        else{
            int p=read(),k=read();
            if(tree.sum[Rt[p]]<k) puts("-1");
            else printf("%lld\n",tree.find(Rt[p],1,n,k));
        }
    }
    return 0;
}