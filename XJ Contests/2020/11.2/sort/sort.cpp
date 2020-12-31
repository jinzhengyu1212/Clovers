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
const int N=500005;
int n;
ll k,a[N];

ll A[N],ret=0;
bool check(ll mid){
    A[0]=0;
    for(int i=1;i<=n;i++){
        A[i]=A[i-1]+(a[i]-mid);
    } 
    ret=0;
    for(int i=1;i<=n;i++){
        int j=i;
        while(A[j]<=A[j-1]&&j!=0){
            swap(A[j],A[j-1]);
            ret++; if(ret>=k) return 1;
            j--;
        }
    }
    return 0;
}

int main()
{
    n=read();
    scanf("%lld",&k);
    for(int i=1;i<=n;i++) a[i]=read(),a[i]*=1e6;
    if(n==1){
        printf("%.3lf\n",1.0*a[1]/1e6);
        return 0;
    }
    ll l=0,r=(ll)1e13,mid,best;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid)) r=mid-1,best=mid;
        else l=mid+1;
    }
    printf("%.3lf\n",best/1e6);
    return 0;
}