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
const int N=500005;
int n,a[N],sum=0,s[N],S=0;

bool check(int mid){
    int mi=0;
    for(int i=1;i<=n/2+1;i++){
        if(s[i-1]+a[i*2-1]-mi>=mid){
            checkmin(mi,s[i]);
        }
        else if(i==n/2+1) return 0;
    }
    return 1;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        if(i%2==0) sum+=a[i]; 
        S+=a[i];
    }
    for(int i=1;i<=n-1;i+=2) s[i/2+1]=s[i/2]+a[i]-a[i+1];
    if(n%2==0){
        cout<<max(S-sum,sum)<<" "<<min(S-sum,sum)<<endl;
    }
    else{
        int l=-3e8,r=3e8,mid,best;
        while(l<=r){
            mid=(l+r)>>1;
            if(check(mid)) l=mid+1,best=mid;
            else r=mid-1;
        }
        cout<<sum+best<<" "<<S-(sum+best)<<endl;
    }
    return 0;
}