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
#define tot(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=1000005;
char s[N];
int n,tot=1,lst=1,bl[N<<1],maxlen[N<<1];
vector<int> v[N];

struct SAM{
    int trans[N<<1][26],link[N<<1];
    void extend(int id){
        int cur=++tot,p; bl[cur]=1;
        maxlen[cur]=maxlen[lst]+1;
        for(p=lst;p&&!trans[p][id];p=link[p]) trans[p][id]=cur;
        if(!p) link[cur]=1;
        else{
            int q=trans[p][id];
            if(maxlen[q]==maxlen[p]+1) link[cur]=q;
            else{
                int y=++tot; maxlen[y]=maxlen[p]+1;
                copy(trans[q],trans[q]+26,trans[y]);
                link[y]=link[q]; link[q]=link[cur]=y;
                for(;p&&trans[p][id]==q;p=link[p]) trans[p][id]=y;
            }
        }
        lst=cur;
    }
    void build(){
        for(int i=2;i<=tot;i++){
            v[link[i]].push_back(i);
        }
    }
}T;
double dp[N];

void dfs(int u){
    dp[u]=1.0*bl[u]*maxlen[u];
    for(auto &to : v[u]){
        dfs(to);
        double tmp=(dp[to]-maxlen[u])/(dp[u]+dp[to]-2*maxlen[u]);
        if(dp[u]) dp[u]=dp[u]*tmp+(1.0-tmp)*maxlen[u];
        else dp[u]=dp[to];
    }
}

int main()
{
    scanf("%s",s+1); n=strlen(s+1);
    for(int i=n;i>=1;i--) T.extend(s[i]-'a');
    T.build();
    dfs(1);
    printf("%.6lf\n",dp[1]);
    return 0;
}