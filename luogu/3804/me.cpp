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
int sz=1,lst=1;
ll ans=0;
struct SAM{
    int link[N],maxlen[N],trans[N][26]; ll f[N];
    void extend(int id){
        int cur=++sz,p;
        maxlen[cur]=maxlen[lst]+1;
        for(p=lst;p&&!trans[p][id];p=link[p]) trans[p][id]=cur;
        if(!p) link[cur]=1;
        else{
            int q=trans[p][id];
            if(maxlen[q]==maxlen[p]+1) link[cur]=q;
            else{
                int tmp=++sz;
                maxlen[tmp]=maxlen[p]+1;
                copy(trans[q],trans[q]+26,trans[tmp]);
                link[tmp]=link[q];
                for(;p&&trans[p][id]==q;p=link[p]) trans[p][id]=tmp;
                link[cur]=link[q]=tmp;
            }
        }
        lst=cur;
    }
    int vis[N];
    vector<int> v[N];
    void dfs(int u){
        f[u]=1; vis[u]=1;
        for(int i=0;i<26;i++) if(trans[u][i]){
            if(!vis[trans[u][i]]) dfs(trans[u][i]);
            f[u]+=f[trans[u][i]];
        }
    }
}tree;

char s[N]; int n;
int main()
{
    n=read();
    scanf("%s",s+1); 
    for(int i=1;i<=n;i++) tree.extend(s[i]-'a');
    tree.dfs(1);
    cout<<tree.f[1]-1<<endl;
    return 0;
}