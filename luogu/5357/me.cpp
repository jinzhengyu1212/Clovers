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
const int N=400005;
int tot=1,leaf[N];
struct AhoCorasick{
    int son[N][26],fail[N],sum[N];
    void init(){for(int i=0;i<26;i++) son[0][i]=1;}
    void insert(char *c,int len,int id){
        int now=1;
        for(int i=1;i<=len;i++){
            if(!son[now][c[i]-'a']) son[now][c[i]-'a']=++tot;
            now=son[now][c[i]-'a'];
        }
        leaf[id]=now;
    }
    queue<int> q;
    vector<int> v[N];
    void build(){
        fail[0]=0; fail[1]=0;
        q.push(1);
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int i=0;i<26;i++){
                if(son[u][i]) 
                    fail[son[u][i]]=son[fail[u]][i],q.push(son[u][i]);
                else son[u][i]=son[fail[u]][i];
            }
        }
        for(int i=2;i<=tot;i++) v[fail[i]].push_back(i);
    }
    ll sz[N];
    void query(char *c,int len){
        int now=1;
        for(int i=1;i<=len;i++){
            now=son[now][c[i]-'a'];
            sz[now]++;
        }
    }
    void dfs(int u){
        for(auto to : v[u]) dfs(to),sz[u]+=sz[to];
    }
}tree;

int n;
char T[N],S[N*5];
int main()
{
    tree.init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",T+1);
        tree.insert(T,strlen(T+1),i);
    }
    tree.build();
    scanf("%s",S+1);
    tree.query(S,strlen(S+1));
    tree.dfs(1);
    for(int i=1;i<=n;i++){
        printf("%lld\n",tree.sz[leaf[i]]);
    }
    return 0;
}