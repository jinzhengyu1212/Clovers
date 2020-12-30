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
const int N=1100005;
int n,m; double a[N];

void FWT_or(int len,double *a){
    for(int h=1;h<len;h<<=1){
        for(int i=0;i<len;i+=(h<<1)){
            for(int j=i;j<i+h;j++) a[j+h]+=a[j];
        }
    }
}

double f[N],ans=0;
int count(int x){
    int ret=0;
    for(int i=0;i<m;i++) ret+=(x>>i&1);
    return ret;
}
int main()
{
    m=read(); n=(1<<m);
    for(int i=0;i<n;i++) scanf("%lf",&a[i]);
    FWT_or(n,a);
    for(int i=1;i<n;i++){
        f[i]=1.0/(1.0-a[n-1-i]);
        if(1.0-a[n-1-i]<1e-8){puts("INF"); return 0;}
    }
    for(int i=1;i<n;i++){
        double flag=(count(i)&1 ? 1 : -1);
        ans+=flag*f[i];
    }   
    printf("%.12lf\n",ans);
    return 0;
}