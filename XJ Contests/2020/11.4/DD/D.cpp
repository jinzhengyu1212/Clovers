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
int mul3(int x,int y,int z){return mul(x,mul(y,z));}
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
const int N=200005;
namespace Poly{
    int rev[N<<1],G[N<<1],IG[N<<1];
    int a[N<<1],b[N<<1];
    void getrev(int len){
        rev[0]=0; rev[len-1]=len-1;
        for(int i=1;i<len-1;i++) rev[i]=(rev[i>>1]>>1)+(len>>1)*(i&1);
    }
    void getinv(int len){
        for(int i=1;i<=len;i<<=1){
            G[i]=qpow(3,(MOD-1)/i);
            IG[i]=qpow(G[i],MOD-2);
        }
    }
    void ntt(int *a,int len,int flag){
        for(int i=0;i<len;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
        for(int h=1;h<len;h<<=1){
            int wn=(flag==1 ? G[h<<1] : IG[h<<1]);
            int tmp1,tmp2,w;
            for(int i=0;i<len;i+=(h<<1)){
                w=1;
                for(int j=i;j<i+h;j++){
                    tmp1=a[j]; tmp2=mul(a[j+h],w);
                    a[j]=add(tmp1,tmp2);
                    a[j+h]=sub(tmp1,tmp2);
                    w=mul(w,wn);
                }
            }
        }
        if(flag==-1){
            int invlen=qpow(len,MOD-2);
            for(int i=0;i<len;i++) a[i]=mul(a[i],invlen);
        }
    }
    int getlen(int n){
        int ret=1;
        while(ret<n) ret<<=1;
        return ret;
    }
    void multi(int *a,int *b,int n,int m){
        int len=getlen(n+m+1);
        getrev(len); getinv(len);
        ntt(a,len,1); ntt(b,len,1); 
        for(int i=0;i<len;i++) a[i]=mul(a[i],b[i]);
        ntt(a,len,-1);
    }
}

int f1[N<<1],g1[N<<1],f2[N<<1],g2[N<<1],fac[N<<1];
int main(){
    int n,m; scanf("%d%d",&n,&m);
    fac[0]=1; for(int i=1;i<=max(n,m);i++) fac[i]=mul(fac[i-1],i);
    for(int i=0;i<=n;i++) 
        f1[i]=mul(qpow(MOD-1,i),qpow(fac[i],MOD-2)),
        g1[i]=mul(qpow(i,n),qpow(fac[i],MOD-2));
    Poly::multi(f1,g1,n,n);

    for(int i=0;i<=m;i++) 
        f2[i]=mul(qpow(MOD-1,i),qpow(fac[i],MOD-2)),
        g2[i]=mul(qpow(i,m),qpow(fac[i],MOD-2));
    Poly::multi(f2,g2,m,m);
    
    int ans=0;
    for(int i=m+1;i<N;i++) f2[i]=0;
    for(int i=n+1;i<N;i++) f1[i]=0;
    for(int i=1;i<=m;i++){
        int tmp1=mul(mul(f2[i],fac[i]),mul(f1[i-1],fac[i-1]));
        int tmp2=mul(mul(f2[i],fac[i]),mul(f1[i],fac[i]));
        //cout<<tmp1<<" "<<tmp2<<endl;
        ans=add(ans,add(tmp1,tmp2));
    }
    for(int i=1;i<=n;i++){
        int tmp1=mul(mul(f1[i],fac[i]),mul(f2[i-1],fac[i-1]));
        int tmp2=mul(mul(f1[i],fac[i]),mul(f2[i],fac[i]));
        //cout<<tmp1<<" "<<tmp2<<endl;
        ans=add(ans,add(tmp1,tmp2));
    }
    cout<<ans<<endl;
    return 0;
}