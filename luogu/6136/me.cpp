#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)((1<<30)+5);
const ll INF=(ll)5e18;
const int MOD=998244353;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
#define mul(x,y) (ll)(x)*(y)%MOD
int qpow(int x,int y){int ret=1; while(y){if(y&1) ret=mul(ret,x); x=mul(x,x); y>>=1;} return ret;}
void checkmin(int &x,int y){if(x>y) x=y;}
void checkmax(int &x,int y){if(x<y) x=y;}
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=1200005;
int tot=2;
struct Splay{
    #define ls ch[x][0]
    #define rs ch[x][1]
    int ch[N][2],fa[N],sz[N],val[N],root,cnt[N];
    void init(){root=1; fa[2]=1; ch[1][1]=2; val[1]=-inf; val[2]=inf; sz[1]=2; sz[2]=1; cnt[1]=1; cnt[2]=1;}
    int getdir(int x){return ch[fa[x]][1]==x;}
    bool isroot(int x){return fa[x]==0;}
    void pushup(int x){sz[x]=sz[ls]+sz[rs]+cnt[x];}
    void rotate(int x){
        int y=fa[x],z=fa[y],dirx=getdir(x),diry=getdir(y);
        ch[z][diry]=x; fa[x]=z;
        ch[y][dirx]=ch[x][dirx^1]; fa[ch[x][dirx^1]]=y;
        ch[x][dirx^1]=y; fa[y]=x;
        pushup(y); pushup(x);
    }
    void splay(int x,int goal=0){
        while(fa[x]!=goal){
            int y=fa[x];
            if(fa[y]!=goal){
                if(getdir(y)==getdir(x)) rotate(y);
                else rotate(x);
            }
            rotate(x);
        }
        if(!goal) root=x;
    }
    int kth(int S){
        int x=root;
        assert(S<=sz[x]);
        while(x){
            if(sz[ls]<S&&sz[ls]+cnt[x]>=S) return x;
            else if(sz[ls]+cnt[x]<S) S-=(sz[ls]+cnt[x]),x=rs;
            else x=ls;
        }
    }
    int rank(int Val){
        int x=root,ret=0;
        while(x){
            if(val[x]<Val) ret+=sz[ls]+cnt[x],x=rs;
            else x=ls;
        }
        return ret+1;
    }
    int pree(int Val){
        int x=root,best;
        while(x){
            if(val[x]<Val) best=val[x],x=rs;
            else x=ls;
        }
        return best;
    }
    int succ(int Val){
        int x=root,best;
        while(x){
            if(val[x]>Val) best=val[x],x=ls;
            else x=rs;
        }
        return best;
    }
    void insert(int Val){
        int rk=rank(Val)-1;
        int x=kth(rk),y=kth(rk+1);
        splay(x); splay(y,x);
        int flag=0;
        if(val[y]==Val) cnt[y]++;
        else sz[++tot]=1, cnt[tot]=1, fa[tot]=y, ch[y][0]=tot, val[tot]=Val, flag=1;
        pushup(y); pushup(x); 
        if(flag) splay(tot);
    }
    void del(int Val){
        int rk=rank(Val);
        int x=kth(rk-1),y=kth(rk+1);
        splay(x); splay(y,x);
        if(ch[y][0]) ch[y][0]=0; 
        else cnt[y]--;
        pushup(y); pushup(x);
    }
    void print(){
        outln(root);
        for(int i=1;i<=tot;i++){
            out(i); out(sz[i]); out(val[i]); out(cnt[i]); out(fa[i]); out(ch[i][0]); outln(ch[i][1]);
        }
    }
}tree;
int n,m,lst=0,ans=0;
int decode(int x){return x^lst;}

int main()
{
    tree.init();
    n=read(); m=read();
    for(int i=1;i<=n;i++){
        int x=read(); tree.insert(x);
        //tree.print();
    }
    while(m--){
        int opt=read(),x=decode(read());
        if(opt==1) tree.insert(x);
        else if(opt==2) tree.del(x);
        else if(opt==3) lst=tree.rank(x)-1;
        else if(opt==4) lst=tree.val[tree.kth(x+1)];
        else if(opt==5) lst=tree.pree(x);
        else lst=tree.succ(x);
        //tree.print();
        if(opt>=3) ans^=lst;
    }
    printf("%d\n",ans);
    return 0;
}