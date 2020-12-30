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
ll _abs(ll x){return x<0 ? -x : x;}
int T; pii a[5];

ll calc(ll mid){
    ll ret=0;
    ret+=_abs(a[2].second-a[1].second)+_abs(a[2].first-a[1].first-mid);
    ret+=_abs(a[3].first-a[1].first)+_abs(a[3].second-a[1].second-mid);
    ret+=_abs(a[4].first-a[1].first-mid)+_abs(a[4].second-a[1].second-mid);
    return ret;
}

int main()
{
    T=read();
    while(T--){
        ll ans=INF;
        for(int i=1;i<=4;i++) a[i].first=read(),a[i].second=read();
        sort(a+1,a+5);
        do{
            ll l=1,r=2e9,mid1,mid2,best;
            while(l+2<r){
                mid1=(l+l+r)/3;
                mid2=(l+r+r)/3;
                if(calc(mid1)<calc(mid2)) best=mid1,r=mid2;
                else best=mid2,l=mid1; 
            }
            checkmin(ans,calc(best));
        }while(next_permutation(a+1,a+5));
        printf("%lld\n",ans);
    }
    return 0;
}