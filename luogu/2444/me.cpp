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
const int N=30005;
struct Aho_Corasick{
    int son[N<<2][2],fail[N<<2],tot=1,leaf[N<<2];
    void init(){son[0][0]=son[0][1]=1;}
    void insert(char *c,int len){
        int now=1;
        for(int i=1;i<=len;i++){
            if(!son[now][c[i]-'0']) son[now][c[i]-'0']=++tot;
            now=son[now][c[i]-'0'];
        }
        leaf[now]=1;
    }
    vector<int> v[N<<2],G[N];
    void run(int u){
        for(auto &to : G[u]) leaf[to]|=leaf[u],run(to);
    }
    void build(){
        queue<int> q;
        q.push(1);
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int i=0;i<2;i++){
                if(son[u][i]) fail[son[u][i]]=son[fail[u]][i],q.push(son[u][i]);
                else son[u][i]=son[fail[u]][i];
            }
        }
        for(int i=2;i<=tot;i++) G[fail[i]].push_back(i);
        for(int i=1;i<=tot;i++){
            for(int j=0;j<2;j++){
                if(son[i][j]) v[i].push_back(son[i][j]);
            }
        }
        run(1);
    }
    int flag,instk[N];
    void dfs(int u){
        instk[u]=1;
        for(auto &to : v[u]){
            if(leaf[to]) continue;
            if(instk[to]){puts("TAK"); exit(0);}
            dfs(to);
        }
        instk[u]=0;
    }
}tree;

char s[N];
int main()
{
    int n;
    tree.init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        tree.insert(s,strlen(s+1));
    }
    tree.build();
    tree.dfs(1);
    puts("NIE");
    return 0;
}