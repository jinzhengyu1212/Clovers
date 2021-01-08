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
const int N=100005;
#define int long long
int n,a[N],ans=0,typ;
int b[70];

signed main()
{
    typ=read(); n=read();
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++){
        for(int j=63;j>=0;j--){
            if(a[i]>>j&1){
                if(!b[j]){b[j]=a[i]; break;}
                else a[i]^=b[j];
            }
        }
    }
    for(int i=63;i>=1;i--){
        for(int j=i-1;j>=0;j--){
            if(b[i]>>j&1) b[i]^=b[j];
        }
    }
    memset(a,0,sizeof(a)); int top=0;
    for(int i=63;i>=0;i--){
        if(b[i]) a[++top]=b[i];
    }
    if(typ==0){
        int sum=0;
        for(int i=0;i<=63;i++) sum+=b[i];
        cout<<sum<<endl;
    }
    else{
        int sum=0,val=0;
        for(int i=1;i<=top;i++) val^=a[i];
        sum=val;
        for(int i=2;i<=n;i++) sum+=(val^a[i]);
        cout<<sum<<endl;
    }
    return 0;
}