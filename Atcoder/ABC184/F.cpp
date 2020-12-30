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
const int N=41;
const int M=5000000;
int n,a[N],T;
int B[M],tmp[N],cnt=0,ans=0,tot=0;

void init(){
    int full=(1<<cnt)-1;
    for(int S=0;S<=full;S++){
        ll sum=0;
        for(int i=1;i<=cnt;i++){
            if(S>>(i-1)&1) sum+=tmp[i];
        }
        if(sum>T) continue;
        B[++tot]=sum; 
        checkmax(ans,sum);
    }
    sort(B+1,B+tot+1);
    tot=unique(B+1,B+tot+1)-B-1;
}

int main()
{
    n=read(); T=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=(n+1)/2;i++){
        tmp[++cnt]=a[i];
    }
    init();
    cnt=0;
    for(int i=(n+1)/2+1;i<=n;i++){
        tmp[++cnt]=a[i];
    }
    int full=(1<<cnt)-1;
    for(int S=0;S<=full;S++){
        ll sum=0;
        for(int i=1;i<=cnt;i++){
            if(S>>(i-1)&1) sum+=tmp[i];
        }
        if(sum>T) continue;
        checkmax(ans,sum);
        int pos=upper_bound(B+1,B+tot+1,T-sum)-B-1;
        if(pos) checkmax(ans,B[pos]+sum);
    }
    cout<<ans<<endl;
    return 0;
}