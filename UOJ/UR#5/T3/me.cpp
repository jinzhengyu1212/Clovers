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
const int N=100005;
int bl[N],prime[N],tot=0,mu[N];
int n,q,c,d;
void init(){
    mu[1]=1;
    for(int i=2;i<N;i++){
        if(!bl[i]) prime[++tot]=i,mu[i]=MOD-1;
        for(int j=1;j<=tot;j++){
            if(i*prime[j]>=N) break;
            bl[i*prime[j]]=1;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                break;
            }
            mu[i*prime[j]]=MOD-mu[i];
        }
    }
}
void calc(int *f,int *g){
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j+=i){
            Add(g[j],mul(f[i],mu[j/i]));
        }
    }
}
int b[N],z[N],g[N],f[N];

int main()
{
    init();
    n=read(); c=read(); d=read(); q=read();
    while(q--){
        int flag=1;
        for(int i=1;i<=n;i++) b[i]=read();
        for(int i=1;i<=n;i++) Mul(b[i],qpow(qpow(i,d),MOD-2));
        for(int i=1;i<=n;i++) f[i]=0,g[i]=0,z[i]=0;
        calc(b,z);
        for(int i=1;i<=n;i++){
            f[i]=qpow(i,_abs(c-d));
            if(c<d) f[i]=qpow(f[i],MOD-2);
        }
        calc(f,g);
        for(int i=1;i<=n;i++){
            if(!g[i]&&z[i]) flag=0;
            f[i]=mul(z[i],qpow(g[i],MOD-2));
        }
        for(int i=n;i>=1;i--){
            for(int j=i+i;j<=n;j+=i) Sub(f[i],f[j]);
        }
        if(!flag){puts("-1"); continue;}
        for(int i=1;i<=n;i++) printf("%lld ",mul(f[i],qpow(qpow(i,d),MOD-2)));
        puts("");
    }
    return 0;
}