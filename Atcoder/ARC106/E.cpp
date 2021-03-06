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
const int N=19;
const int M=(1<<N);
int n,k,a[N],full;
int f[M],g[40000000];
void FWT(){
    for(int h=1;h<=full;h<<=1){
        for(int i=0;i<=full;i+=(h<<1)){
            for(int j=i;j<i+h;j++) f[j+h]+=f[j];
        }
    }
}

bool check(int mid){
    memset(f,0,sizeof(f));
    for(int i=1;i<=mid;i++){
        f[g[i]]++;
    }
    FWT();
    for(int S=1;S<=full;S++){
        int cnt=0;
        for(int i=0;i<n;i++){
            if(S>>i&1) cnt+=k;
        }
        int rest=mid-f[full^S];
        if(rest<cnt) return 0;
    }
    return 1;
}

int main()
{
    n=read(); k=read(); full=(1<<n)-1;
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=2*n*k;i++){
        int mask=0;
        for(int j=1;j<=n;j++){
            int tmp=i%(2*a[j]); if(tmp==0) tmp=2*a[j];
            if(tmp<=a[j]) mask|=(1<<(j-1));
        }
        g[i]=mask;
    }
    int l=n*k,r=2*n*k,mid,best;
    while(l<=r){
        mid=(l+r)>>1;
        if(check(mid)) r=mid-1,best=mid;
        else l=mid+1;
    }
    cout<<best<<endl;
    return 0;
}