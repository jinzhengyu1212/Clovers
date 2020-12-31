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
const ll INF=(ll)5e17;
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
const int N=370005*2;
int n,col[N];ll Copy[N],ans=-INF,val[N];

struct Virtual_Tree{
    vector<pii> v[N];
    int e=0,first[N],nxt[N<<1],point[N<<1];ll w[N<<1];
    void add_edge(int x,int y,ll z){
        e++; point[e]=y;
        nxt[e]=first[x]; first[x]=e; w[e]=z;
    }
    int lg[N],st[N<<1][21],tot=0,dfn[N],Out[N],dfn_clock=0,pos[N];
    ll sum[N]; ll dp[N][2];
    
    void dfs1(int u){
        dfn[u]=++dfn_clock; st[++tot][0]=u; pos[u]=tot;
        for(auto &to : v[u]){
            if(dfn[to.first]) continue;
            sum[to.first]=sum[u]+to.second;
            dfs1(to.first); st[++tot][0]=u;
        }
        Out[u]=dfn_clock;
    }

    bool isfa(int x,int y){return dfn[x]<=dfn[y]&&Out[x]>=Out[y];}
    int LCA(int x,int y){
        if(pos[x]>pos[y]) swap(pos[x],pos[y]);
        int l=pos[x],r=pos[y],sz=r-l+1;
        return min(st[l][lg[sz]],st[r-(1<<lg[sz])+1][lg[sz]]);
    }

    void init(){
        for(int i=1;i<=n;i++) v[i].clear();
        for(int i=1;i<n;i++){
            int x=read(),y=read(),z=read();
            v[x].push_back(mk(y,z)); v[y].push_back(mk(x,z));
        }
        for(int i=1;i<=n;i++) dfn[i]=0;
        dfs1(1);
        for(int i=1;i<=n;i++) first[i]=-1;
        lg[1]=0; for(int i=2;i<=tot;i++) lg[i]=lg[i>>1]+1;
        for(int j=1;j<=lg[tot];j++){
            for(int i=1;i+(1<<j)<=tot;i++){
                st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
            }
        }
        for(int i=1;i<=n;i++) dp[i][0]=-INF,dp[i][1]=-INF;
    }

    pii a[N]; int m=0;
    vector<int> S;
    stack<int> stk;
    int vis[N];

    int valid[N];
    void dfs2(int u,int f){
        if(valid[u]) dp[u][col[u]]=val[u];
        ll ret=-INF;
        for(int i=first[u];i!=-1;i=nxt[i]){
            int to=point[i];
            if(to==f) continue;
            dfs2(to,u);
            checkmax(ret,dp[u][0]+dp[to][1]-2*sum[u]);
            checkmax(ret,dp[u][1]+dp[to][0]-2*sum[u]);
            checkmax(dp[u][0],dp[to][0]);
            checkmax(dp[u][1],dp[to][1]);
        }
        checkmax(ans,ret);
    }

    void build(vector<int> &A){
        int mi=inf; e=0;
        m=0; S.clear(); while(!stk.empty()) stk.pop();
        for(auto &to : A) a[++m]=mk(dfn[to],to),valid[to]=1;
        sort(a+1,a+m+1);
        vis[1]=1; stk.push(1); S.push_back(1);
        /*out<<"origin:";
        for(auto &to : A) cout<<to<<" "; cout<<endl;*/
        for(int i=1;i<=m;i++){
            int poped=0;
            if(a[i].second==1) continue;
            int now=a[i].second;
            int lca=LCA(stk.top(),now),tmp;
            while(!isfa(stk.top(),now)){
                tmp=stk.top(); poped=1;
                stk.pop();
                if(isfa(stk.top(),now)) break;
                add_edge(stk.top(),tmp,sum[tmp]-sum[stk.top()]);
            }
            if(!vis[lca]){
                vis[lca]=1; S.push_back(lca);
                stk.push(lca); add_edge(lca,tmp,sum[tmp]-sum[lca]);
            }
            else if(poped) add_edge(stk.top(),tmp,sum[tmp]-sum[stk.top()]);
            vis[now]=1; S.push_back(now); stk.push(now);
        }
        while(stk.top()!=1){
            int to=stk.top(); stk.pop();
            int u=stk.top();
            add_edge(u,to,sum[to]-sum[u]);
        }
        /*cout<<"now:";
        for(auto &to : S) cout<<to<<" "; cout<<endl;
        for(auto &u : S){
            out(u); out(sum[u]);out(Copy[u]); out(col[u]); outln(val[u]);
            for(int i=first[u];i!=-1;i=nxt[i]){
                cout<<u<<" "<<point[i]<<" "<<w[i]<<endl;
            }
        }
        cout<<endl;*/
    }

    void solve(){
        dfs2(1,-1);
        for(auto &to : S){
            vis[to]=0,first[to]=-1;
            dp[to][0]=-INF;
            dp[to][1]=-INF;
            valid[to]=0;
        }
    }
}tree2;

struct Tree1{
    vector<pii> v[N],G[N];
    int m;
    void rebuild(int u,int fa){
        int cnt=0,lst=0;
        for(auto &to : v[u]){
            if(to.first==fa) continue;
            cnt++;
            if(cnt==1){
                G[u].push_back(to);
                G[to.first].push_back(mk(u,to.second));
                lst=u;
            }
            else if(cnt==sz(v[u])-(u!=1)){
                G[lst].push_back(to);
                G[to.first].push_back(mk(lst,to.second));
            }
            else{
                m++;
                G[lst].push_back(mk(m,0));
                G[m].push_back(mk(lst,0));
                G[m].push_back(to); 
                G[to.first].push_back(mk(m,to.second));
                lst=m;
            }
        }
    }
    void dfs1(int u,int f){
        rebuild(u,f);
        for(auto &to : v[u]){
            if(to.first==f) continue;
            Copy[to.first]=Copy[u]+to.second;
            dfs1(to.first,u);
        }   
    }
    void init(){
        for(int i=1;i<=n;i++) v[i].clear();
        for(int i=1;i<n;i++){
            int x=read(),y=read(),z=read();
            v[x].push_back(mk(y,z)); v[y].push_back(mk(x,z));
        }
        dfs1(1,-1); 
        for(int i=1;i<=m;i++) v[i]=G[i],G[i].clear();
        
        /*cout<<endl;
        cout<<"newtree1:\n";
        for(int i=1;i<=m;i++){
            out(i); out(dep[i]); outln(Copy[i]);
            for(auto &to : v[i]){
                printf("%d %d %d\n",i,to.first,to.second);
            }
        }
        cout<<endl;*/
    }

    pii Edg; int Edgval;
    int sz[N],mi,vis[N];
    void findedge(int u,int f,int S){
        sz[u]=1;
        for(auto &to : v[u]){
            if(to.first==f||vis[to.first]) continue;
            findedge(to.first,u,S); sz[u]+=sz[to.first];
            if(mi>max(sz[to.first],S-sz[to.first])){
                mi=max(sz[to.first],S-sz[to.first]);
                Edg=mk(u,to.first); Edgval=to.second;
            }
        }
    }

    ll dep[N];
    vector<int> A;
    void dfs2(int u,int f,int color,int base){
        col[u]=color; if(u<=n) A.push_back(u);
        val[u]=dep[u]+Copy[u]+base; sz[u]=1;
        for(auto &to : v[u]){
            if(to.first==f||vis[to.first]) continue;
            dep[to.first]=dep[u]+to.second;
            dfs2(to.first,u,color,base);
            sz[u]+=sz[to.first];
        }
    }
    void solve(int S,int now){
        if(S==1) return;
        mi=inf; A.clear();
        findedge(now,-1,S); 
        int X=Edg.first,Y=Edg.second;
        //out(now); out(X); out(Y); out(Edgval); outln(S);
        dep[X]=0; dep[Y]=0;
        vis[X]=1; dfs2(Y,-1,0,Edgval); vis[X]=0;
        vis[Y]=1; dfs2(X,-1,1,0); vis[Y]=0;
        tree2.build(A);
        tree2.solve();
        vis[X]=1; solve(sz[Y],Y); vis[X]=0;
        vis[Y]=1; solve(sz[X],X); vis[Y]=0;
    }
}tree1;

int main()
{
    n=read(); tree1.m=n;
    tree1.init();
    tree2.init();
    tree1.solve(tree1.m,1);
    ans/=2;
    for(int i=1;i<=n;i++){
        //out(Copy[i]); outln(tree2.sum[i]);
        checkmax(ans,Copy[i]-tree2.sum[i]);
    }
    cout<<ans<<endl;
    return 0;
}