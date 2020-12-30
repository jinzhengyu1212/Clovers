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
const int N=2000005;
const int inv2=(MOD+1)/2;
pii a[N]; int n,val[N];
int in[N],out[N];
int ans;

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        a[i].first=read(),a[i].second=read();
        val[i*2-1]=a[i].first,val[i*2]=a[i].second;
    }
    sort(val+1,val+n+n+1);
    int nn=unique(val+1,val+n+n+1)-val-1;
    for(int i=1;i<=n;i++){
        a[i].first=lower_bound(val+1,val+nn+1,a[i].first)-val;
        a[i].second=lower_bound(val+1,val+nn+1,a[i].second)-val;
        in[a[i].first]++; out[a[i].second]++;
    }
    int now=0; ans=qpow(2,n);
    for(int i=1;i<=nn;i++){
        now-=out[i];
        now+=in[i];
        if(now>=3){puts("0"); return 0;}
        if(now==2) Mul(ans,inv2);
    }
    cout<<ans<<endl;
    return 0;
}