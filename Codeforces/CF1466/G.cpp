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
const int N=2000005;
int n,q;
char s[N],t[N];
struct SAM{
    int link[N],maxlen[N],trans[N][26],f[N],firstpos[N];
    void extend(int id){
        int cur=++sz,p; f[sz]=1;
        maxlen[cur]=maxlen[lst]+1; firstpos[cur]=maxlen[cur];
        for(p=lst;p&&!trans[p][id];p=link[p]) trans[p][id]=cur;
        if(!p) link[cur]=1;
        else{
            int q=trans[p][id];
            if(maxlen[q]==maxlen[p]+1) link[cur]=q;
            else{
                int tmp=++sz; 
                maxlen[tmp]=maxlen[p]+1; firstpos[tmp]=firstpos[q];
                copy(trans[q],trans[q]+26,trans[tmp]);
                link[tmp]=link[q];
                for(;p&&trans[p][id]==q;p=link[p]) trans[p][id]=tmp;
                link[cur]=link[q]=tmp;
            }
        }
        lst=cur;
    }
    vector<int> v[N];
    void build(){
        for(int i=2;i<=sz;i++) v[link[i]].push_back(i);
    }
    void dfs(int u){
        for(auto &to : v[u]) dfs(to),f[u]+=f[to];
    }
}tree;

int main()
{
    n=read(); q=read();
    scanf("%s",s+1); scanf("%s",t+1);
    while(n<1000000){
        
    }
    return 0;
}