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
const int N=1050005;
int n,tot,m,Base[N],ans[N]; char s[N];

struct Trie{
    int rev[N],val[N],ch[N][3],cnt=1;
    void insert(int Val){
        int x=1,tmp=Val;
        for(int i=1;i<=n;i++){
            if(!ch[x][Val%3]) ch[x][Val%3]=++cnt;
            x=ch[x][Val%3]; Val/=3;
        }
        val[x]=tmp;
    }
    void pushdown(int x){
        if(rev[x]){
            for(int i=0;i<3;i++) rev[ch[x][i]]^=1;
            swap(ch[x][1],ch[x][2]); rev[x]=0;
        }
    }
    void Add(){
        int x=1;
        for(int i=1;i<=n;i++){
            pushdown(x);
            swap(ch[x][0],ch[x][1]); swap(ch[x][0],ch[x][2]);
            x=ch[x][0];
        }
    }
    void dfs(int u,int dep,int Val){
        pushdown(u);
        if(dep==n){ans[val[u]]=Val; return;}
        for(int i=0;i<3;i++) dfs(ch[u][i],dep+1,Val+i*Base[dep]);
    }
}tree;

int main()
{
    n=read(); scanf("%s",s+1);
    Base[0]=1; for(int i=1;i<=n;i++) Base[i]=Base[i-1]*3;
    tot=Base[n]; m=strlen(s+1);
    for(int i=0;i<tot;i++) tree.insert(i);
    for(int i=1;i<=m;i++){
        if(s[i]=='S') tree.rev[1]^=1;
        else tree.Add();
    }
    tree.dfs(1,0,0); 
    for(int i=0;i<tot;i++) printf("%d ",ans[i]); puts("");
    return 0;
}