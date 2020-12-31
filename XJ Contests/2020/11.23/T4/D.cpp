/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
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
const int N=200005;
int n,m;
ll suma[N],sumb[N],a[N],b[N]; pii A[N];

int find(int R,ll S){
    int l=1,r=R,mid,best=-1;
    while(l<=r){
        mid=(l+r)>>1;
        if(suma[R]-suma[mid-1]<=S) best=mid,r=mid-1;
        else l=mid+1;
    }
    return best;
}

int main()
{
    n=read(); m=read();
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&A[i].first,&A[i].second);
    }
    sort(A+1,A+n+1);
    for(int i=1;i<=n;i++) suma[i]=suma[i-1]+A[i].first,
                          sumb[i]=sumb[i-1]+A[i].second;
    for(int i=1;i<=n;i++) a[i]=A[i].first,b[i]=A[i].second;
    while(m--){
        ll S,ans=0; scanf("%lld",&S);
        int pos=upper_bound(a+1,a+n+1,S)-a-1;
        while(pos!=0){
            int L=find(pos,S);
            S-=suma[pos]-suma[L-1]; ans+=sumb[pos]-sumb[L-1];
            pos=L-1; if(!pos) break;
            pos=upper_bound(a+1,a+n+1,S)-a-1;
        }
        printf("%lld\n",ans);
    }
    return 0;
}