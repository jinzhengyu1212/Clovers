#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
#define out(x) cerr<<#x<<"="<<x<<"  "
#define outln(x) cerr<<#x<<"="<<x<<endl
const int MOD=998244353;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
int mul(int x,int y){return 1ll*x*y%MOD;}
void Add(int &x,int y){x+=y; if(x>=MOD) x-=MOD;}
void Sub(int &x,int y){x-=y; if(x<0) x+=MOD;}
void Mul(int &x,int y){x=1ll*x*y%MOD;}
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
    return x*f;
}
const int N=120000;
int n,a[N],m;
struct OPT{
    vector<pii> add;//pos add
    int mul,typ;
}opt[N];
vector<int> tmp[N];
map<pii,int> mp;
vector<int> v[N]; int in[N],copyin[N];

int id[N],tot=0;
void topo(){
    for(int i=1;i<=m;i++) copyin[i]=in[i];
    queue<int> q; while(!q.empty()) q.pop();
    for(int i=1;i<=m;i++){
        if(opt[i].typ!=3) continue;
        if(in[i]==0) q.push(i);
    } 
    while(!q.empty()){
        int u=q.front(); q.pop(); id[++tot]=u;
        for(int i=0;i<(int)v[u].size();i++){
            int to=v[u][i];
            if(!--in[to]) q.push(to);
        }
    }
    reverse(id+1,id+tot+1);
}

int val[N],vis[N];
void init(){
    n=read();
    mp.clear();
    for(int i=1;i<=n;i++) a[i]=read();
    m=read();
    for(int i=1;i<=m;i++) opt[i].add.clear(),opt[i].mul=1;
    for(int i=1;i<=m;i++){
        opt[i].typ=read();
        if(opt[i].typ==1){
            int x=read(),y=read();
            opt[i].add.push_back(mk(x,y));
        }
        else if(opt[i].typ==2){
            int x=read();
            opt[i].mul=x;
        }
        else{
            int C=read();
            for(int j=1;j<=C;j++){
                int x=read();
                tmp[i].push_back(x);
            }
        }
    }
    for(int i=1;i<=m;i++){
        if(opt[i].typ==3){
            for(int j=(int)tmp[i].size()-1;j>=0;j--){
                int to=tmp[i][j];
                if(opt[to].typ==3){
                    v[i].push_back(to); in[to]++;
                    mp[mk(i,to)]=0;
                }
            }
        }
    }
    topo();
    for(int i=1;i<=tot;i++){
        int u=id[i],multag=1;
        for(int j=(int)tmp[u].size()-1;j>=0;j--){
            int to=tmp[u][j];
            if(opt[to].typ==1){
                pii T=opt[to].add[0];
                int pos=T.first, ad=T.second;
                opt[u].add.push_back(mk(pos,mul(ad,multag)));
            }
            else if(opt[to].typ==2){
                Mul(multag,opt[to].mul);
            }
            else{
                Add(mp[mk(u,to)],multag);
                Mul(multag,opt[to].mul);
            }
        }
        opt[u].mul=multag;
    }
}

void dfs(int u){
    vis[u]=1;
    for(int i=0;i<(int)v[u].size();i++){
        int to=v[u][i];
        Add(val[to],mul(val[u],mp[mk(u,to)]));
        if(!vis[to]) dfs(to);
    }
}

int Q,f[N],Ad[N];
void solve(){
    for(int i=1;i<=max(n,m);i++) val[i]=0,Ad[i]=0;
    Q=read();
    for(int i=1;i<=Q;i++) f[i]=read();
    int multag=1;
    for(int i=Q;i>=1;i--){
        int u=f[i];
        if(opt[u].typ==1){
            pii T=opt[u].add[0];
            int pos=T.first, ad=T.second;
            Add(Ad[pos],mul(multag,ad));
        }
        else if(opt[u].typ==2){
            Mul(multag,opt[u].mul);
        }
        else{
            Add(val[u],multag);
            Mul(multag,opt[u].mul);
        }
    }
    for(int i=1;i<=n;i++) Mul(a[i],multag);
    for(int i=1;i<=m;i++){
        if(opt[i].typ==3&&!vis[i]&&!copyin[i]){
            dfs(i); 
        }
    }
    //for(int i=1;i<=n;i++) Add(a[i],Ad[i]);
    //for(int i=1;i<=n;i++) printf("%d ",a[i]);
    for(int i=1;i<=m;i++){
        if(opt[i].typ==3){
            for(int j=0;j<(int)opt[i].add.size();j++){
                pii T=opt[i].add[j];
                int pos=T.first, ad=T.second;
                Add(Ad[pos],mul(val[i],ad));
            }
        }
    }
    for(int i=1;i<=n;i++) Add(a[i],Ad[i]);
    for(int i=1;i<=n;i++) printf("%d ",a[i]);
}

int main(){
    //freopen("call.in","r",stdin);
    //freopen("call.out","w",stdout);
    init(); solve();
    fclose(stdin); fclose(stdout);
    return 0;
}