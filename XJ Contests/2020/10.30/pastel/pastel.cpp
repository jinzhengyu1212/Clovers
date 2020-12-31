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
const int N=300005;
int n,m,fa[N]; vector<int> v[N];
typedef unsigned int ui;

namespace solver1{
    ui w[N];
    struct Segment_Tree2{
        ui sum[N],tag[N];
        void pushup(int x){sum[x]=sum[x<<1]+sum[x<<1|1];}
        void pushdown(int x,int l,int r,int mid){
            if(!tag[x]) return;
            sum[x<<1]+=tag[x]*(ui)(mid-l+1); tag[x<<1]+=tag[x];
            sum[x<<1|1]+=tag[x]*(ui)(r-mid); tag[x<<1|1]+=tag[x];
            tag[x]=0;
        }
        void update(int x,int l,int r,int L,int R,ui add){
            if(L<=l&&r<=R){sum[x]+=(ui)(r-l+1)*add; tag[x]+=add; return;}
            int mid=(l+r)>>1; pushdown(x,l,r,mid);
            if(mid>=L) update(x<<1,l,mid,L,R,add);
            if(mid<R) update(x<<1|1,mid+1,r,L,R,add);
            pushup(x);
        }
        ui query(int x,int l,int r,int L,int R){
            if(L<=l&&r<=R)return sum[x];
            int mid=(l+r)>>1; pushdown(x,l,r,mid);
            ui ret=0;
            if(mid>=L) ret+=query(x<<1,l,mid,L,R);
            if(mid<R) ret+=query(x<<1|1,mid+1,r,L,R);
            return ret;
        }
    }tree1;

    struct Segment_Tree{
        int fa[N<<2]; pii tag[N<<2];
        void pushdown(int x){
            if(!tag[x].first) return;
            if(tag[x<<1].second<tag[x].second){
                fa[x<<1]=tag[x].first;
                tag[x<<1]=tag[x];
            }
            if(tag[x<<1|1].second<tag[x].second){
                fa[x<<1|1]=tag[x].first;
                tag[x<<1|1]=tag[x];
            }
            tag[x].first=0;
        }
        void update(int x,int l,int r,int L,int R,int Fa,int upd){
            if(L<=l&&r<=R){fa[x]=Fa,tag[x]=mk(Fa,upd); return;}
            int mid=(l+r)>>1;
            pushdown(x);
            if(mid>=L) update(x<<1,l,mid,L,R,Fa,upd);
            if(mid<R) update(x<<1|1,mid+1,r,L,R,Fa,upd);
        }
        int query(int x,int l,int r,int pos){
            if(l==r) return fa[x];
            int mid=(l+r)>>1;
            pushdown(x);
            if(mid>=pos) return query(x<<1,l,mid,pos);
            else return query(x<<1|1,mid+1,r,pos);
        }
    }tree2;

    int nxt[N],pre[N];
    set<int> st;
    void main(){
        for(int i=1;i<=n;i++) nxt[i]=n+1;
        st.insert(1);
        for(int ti=1;ti<=m;ti++){
            int opt,x; int y;
            scanf("%d",&opt);
            x=read(); if(opt==2||opt==4) y=read();
            if(opt==1){
                printf("%u\n",tree1.query(1,1,n,x,x));
            }
            else if(opt==2){
                int fa=nxt[x];
                tree1.update(1,1,n,x,fa-1,y);
            }
            else if(opt==3){
                printf("%u\n",tree1.query(1,1,n,x,n));
            }
            else if(opt==4){
                tree1.update(1,1,n,x,n,y);
            }
            else if(opt==5){
                
            }
        }
    }
}

namespace solver2{
    int col[N]; ui w[N];
    void dfs1(int u,ui val){
        w[u]+=val;
        for(int i=0;i<(int)v[u].size();i++){
            int to=v[u][i];
            if(col[to]==1) continue;
            dfs1(to,val);
        }
    }

    ui dfs2(int u){
        ui ret=w[u];
        for(int i=0;i<(int)v[u].size();i++){
            int to=v[u][i]; 
            ret+=dfs2(to);
        }  
        return ret;
    }

    void dfs3(int u,int val){
        w[u]+=val;
        for(int i=0;i<(int)v[u].size();i++){
            int to=v[u][i]; dfs3(to,val);
        }
    }

    void main(){
        memset(col,0,sizeof(col));
        col[1]=1;
        while(m--){
            int opt,x; int y;
            scanf("%d",&opt);
            x=read(); if(opt==2||opt==4) y=read();
            if(opt==1) printf("%d\n",w[x]);
            else if(opt==2) dfs1(x,y);
            else if(opt==3) printf("%u\n",dfs2(x));
            else if(opt==4) dfs3(x,y);
            else if(opt==5) col[x]=1;
            else col[x]=0;
        }
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;i++){
        scanf("%d",&fa[i]);
        v[fa[i]].push_back(i);
    }
    solver2::main();
    return 0;
}