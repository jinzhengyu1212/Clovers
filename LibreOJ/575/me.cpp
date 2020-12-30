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
int n,L[N],fac[N],ifac[N];
char s[N];

int f[N<<2],g[N<<2],dp[N];
namespace FFT{
    int rev[N<<2],G[N<<2],IG[N<<2];
    int init(int n){
        int len=1; while(len<n) len<<=1;
        rev[0]=0;
        for(int i=1;i<len;i++) rev[i]=(rev[i>>1]>>1)+(i&1 ? len>>1 : 0);
        for(int i=1;i<=len;i<<=1){
            G[i]=qpow(3,(MOD-1)/i);
            IG[i]=qpow(G[i],MOD-2);
        }
        return len;
    }
    void ntt(int *a,int len,int flag){
        for(int i=0;i<len;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
        for(int h=1;h<len;h<<=1){
            int wn=(flag==1 ? G[h<<1] : IG[h<<1]);
            for(int i=0;i<len;i+=(h<<1)){
                int w=1,tmp1,tmp2;
                for(int j=i;j<i+h;j++,Mul(w,wn)){
                    tmp1=a[j]; tmp2=mul(a[j+h],w);
                    a[j]=add(tmp1,tmp2); a[j+h]=sub(tmp1,tmp2);
                }
            }
        }
        if(flag==-1){
            int invlen=qpow(len,MOD-2);
            for(int i=0;i<len;i++) Mul(a[i],invlen);
        }
    }
    void multi(int *a,int *b,int n,int m){
        int len=init(n+m+1);
        for(int i=n+1;i<=len;i++) a[i]=0;
        for(int j=m+1;j<=len;j++) b[j]=0;
        ntt(a,len,1); ntt(b,len,1);
        for(int i=0;i<len;i++) Mul(a[i],b[i]);
        ntt(a,len,-1);
    }
    int a[N<<2],b[N<<2];
    void cdq(int l,int r){
        if(l==r){
            if(l==0) return;
            int flag=(L[l-1]&1 ? MOD-1 : 1);
            dp[l]=mul(f[l],mul(flag,fac[l]));
            if(s[l]=='<') f[l]=0;
            else f[l]=MOD-f[l];
            return;
        }
        int mid=(l+r)>>1;
        cdq(l,mid);
        for(int i=l;i<=mid;i++) a[i-l]=f[i];
        for(int i=0;i<=r-l;i++) b[i]=g[i];
        multi(a,b,mid-l,r-l);
        for(int i=mid+1;i<=r;i++) Add(f[i],a[i-l]);
        cdq(mid+1,r);
    }
}

int main()
{
    scanf("%s",s+1); n=strlen(s+1)+1;
    for(int i=1;i<n;i++) L[i]=L[i-1]+(s[i]=='>');
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=mul(fac[i-1],i);
    ifac[n]=qpow(fac[n],MOD-2);
    for(int i=n-1;i>=0;i--) ifac[i]=mul(ifac[i+1],i+1);
    for(int i=0;i<=n;i++) g[i]=ifac[i];
    f[0]=1; dp[0]=1;
    FFT::cdq(0,n);
    cout<<dp[n]<<endl;
    return 0;
}