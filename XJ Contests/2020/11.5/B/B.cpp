/*
the vast starry sky,
bright for those who chase the light.
*/
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
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
const int N=1000005;
const int MOD1=19260817;
const int MOD2=77090107;
const int B=41;
pii operator + (pii x,pii y){
    return mk((x.first+y.first)%MOD1,(x.second+y.second)%MOD2);
}
pii operator - (pii x,pii y){
    return mk((x.first-y.first+MOD1)%MOD1,(x.second-y.second+MOD2)%MOD2);
}
pii operator * (pii x,int y){
    return mk(1ll*x.first*y%MOD1,1ll*x.second*y%MOD2);
}
pii operator * (pii x,pii y){
    return mk((ll)x.first*y.first%MOD1,(ll)x.second*y.second%MOD2);
}
pii Base[N],sum[N]; int n;
char s[N];
pii f(int l,int r){
    return (sum[r]-sum[l-1])*Base[n-r];
}
void init(){
    scanf("%s",s+1);
    n=strlen(s+1);
    Base[0]=mk(1,1);
    for(int i=1;i<=n;i++) Base[i]=Base[i-1]*B;
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+(Base[i]*(s[i]-'a'+1));
    }
}

ll ans=1; int head[N];
void solve(){
    for(int d=1;d<n;d++){
        int k=n/d,rest=n%d;
        if(n%d==0) ans++,k--,rest=d;
        head[1]=1;
        ans++;
        for(int i=2;i<=k;i++) head[i]=head[i-1]+d;
        for(int i=k;i>=1;i--){
            pii f1=f(head[i],head[i]+d-1);
            pii f2=f(head[i]+rest,head[i]+rest+d-1);
            if(f1!=f2) ans++; 
        }
    }
    printf("%lld\n",ans);
}

int main()
{  
    init();
    solve();
    return 0;
}