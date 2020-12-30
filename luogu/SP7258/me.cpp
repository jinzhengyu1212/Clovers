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
const int N=1000005;
int lst=1,sz=1;

struct SAM{
    int trans[N][26],maxlen[N],link[N],f[N];
    void extend(int id){
        int cur=++sz,p; maxlen[cur]=maxlen[lst]+1; f[cur]=1;
        for(p=lst;p&&!trans[p][id];p=link[p]) trans[p][id]=cur;
        if(!p) link[cur]=1;
        else{
            int q=trans[p][id];
            if(maxlen[q]==maxlen[p]+1) link[cur]=q;
            else{
                int y=++sz; maxlen[y]=maxlen[p]+1;
                for(;p&&trans[p][id]==q;p=link[p]) trans[p][id]=y;
                copy(trans[q],trans[q]+26,trans[y]);
                link[y]=link[q];
                link[q]=link[cur]=y;
            }
        }
        lst=cur;
    }
    ll dp[N],cnt[N],q[N];
    void run(int t){
        for(int i=1;i<=sz;i++) cnt[maxlen[i]]++;
        for(int i=1;i<=sz;i++) cnt[i]+=cnt[i-1];
        for(int i=1;i<=sz;i++) q[cnt[maxlen[i]]--]=i;
        for(int i=sz;i>=1;i--) f[link[q[i]]]+=f[q[i]];
        if(!t) for(int i=1;i<=sz;i++) f[i]=1;
        for(int i=1;i<=sz;i++) dp[i]=f[i];
        dp[1]=f[1]=0;
        for(int i=sz;i>=1;i--){
            for(int j=0;j<26;j++){
                dp[q[i]]+=dp[trans[q[i]][j]];
            }
        }
    }
    void find(int t,int k){
        int u=1;
        while(k>0){
            for(int i=0;i<26;i++){
                if(!trans[u][i]) continue;
                if(k>dp[trans[u][i]]) k-=dp[trans[u][i]];
                else{
                    u=trans[u][i];
                    putchar('a'+i);
                    k-=f[u]; break;
                }
            }
        }
        puts("");
    }
}T;
char s[N]; int n;

int main()
{
    scanf("%s",s+1); n=strlen(s+1);
    T.maxlen[1]=1;
    for(int i=1;i<=n;i++) T.extend(s[i]-'a');
    int t=read(),k=read();
    T.run(t);
    if(T.dp[1]>=k) T.find(t,k); else puts("-1");
    return 0;
}