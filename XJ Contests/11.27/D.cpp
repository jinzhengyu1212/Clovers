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
const int N=50005;
const int M=1005;
#define double long double
const double eps=1e-20;
#define int long long
int n,m,k,t,a[N],sum[N],D;
 
void init(){
    n=read(); m=read(); k=read(); t=read();
    for(int i=1;i<=n;i++) a[i]=read(),sum[i]=sum[i-1]+a[i];
    D=k/sum[n]; k%=sum[n];
    for(int i=n+1;i<=n+n;i++) a[i]=a[i-n],sum[i]=sum[i-1]+a[i];
}
 
namespace solver1{
    int ans=0;
    int find(int from){
        int l=from,r=n+n,mid,best;
        while(l<=r){
            mid=(l+r)>>1;
            if(sum[mid]-sum[from-1]>=k) best=mid,r=mid-1;
            else l=mid+1;
        }
        return best;
    }
    void main(){
        int pos=1;
        for(int i=1;i<=m;i++){
            ans=0;
            ans+=D*n;
            if(!k){
                printf("%.2Lf ",(double)ans+eps);
                continue;
            }
            int to=find(pos);
            ans+=to-pos;
            double tmp=k-(sum[to-1]-sum[pos-1]);
            tmp/=(double)a[to];
            printf("%.2Lf ",(double)ans+tmp+eps);
            pos=to%n+1;
        }
        puts("");
    }
}
 
namespace solver2{
    int find(int from,int rest){
        if(k-rest<=0) return from;
        int l=from+1,r=n+n,mid,best;
        while(l<=r){
            mid=(l+r)>>1;
            if(sum[mid]-sum[from]>=k-rest) best=mid,r=mid-1;
            else l=mid+1;
        }
        return best;
    }
    void main(){
        int pos=1,rest=a[1];
        for(int i=1;i<=m;i++){
            int ans=0; ans+=D*n;
            //if(i==69) outln(pos),outln(rest);
            if(!k){
                printf("%.2Lf ",(double)ans+eps);
                continue;
            }
            int to=find(pos,rest);
            if(to==pos){
                rest-=k;
                double tmp=1.0*k/(1.0*a[pos]);
                printf("%.2Lf ",tmp+eps);
                continue;
            }
            double tmp1=1.0*rest/(1.0*a[pos]);
            ans+=to-(pos+1);
            double tmp2=k-rest-(sum[to-1]-sum[pos]);
            rest=a[to]-tmp2;
            tmp2/=(double)a[to];
            printf("%.2Lf ",(double)ans+tmp1+tmp2+eps);
            pos=to%n; if(pos==0) pos=n;
        }
        puts("");
    }
}
 
signed main()
{
    init();
    if(t==0) solver1::main();
    else solver2::main();
    return 0;
}