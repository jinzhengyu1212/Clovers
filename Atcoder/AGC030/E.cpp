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
const int N=20005;
int n,tot1=0,tot2=0,mx;
char S[N],T[N];
int a[N],b[N],A[N],B[N];

int main()
{
    n=read();
    scanf("%s",S+1); scanf("%s",T+1);
    if(S[1]=='1') a[++tot1]=0;
    for(int i=1;i<n;i++) if(S[i]!=S[i+1]) a[++tot1]=i;
    if(S[n]=='1') a[++tot1]=n;
    if(T[1]=='1') b[++tot2]=0;
    for(int i=1;i<n;i++) if(T[i]!=T[i+1]) b[++tot2]=i;
    if(T[n]=='1') b[++tot2]=n;
    mx=tot1+tot2+tot2;//tot1&tot2 are even
    for(int i=1;i<=tot1;i++) A[i+tot2]=a[i];
    for(int i=tot1+tot2+1;i<=mx;i++) A[i]=n;
    int ans=inf;
    for(int pre=0;pre<=tot1+tot2;pre+=2){
        for(int i=1;i<=pre;i++) B[i]=0;
        for(int i=1;i<=tot2;i++) B[pre+i]=b[i];
        for(int i=pre+tot2+1;i<=mx;i++) B[i]=n;
        int ret=0;
        for(int i=1;i<=mx;i++) ret+=_abs(A[i]-B[i]);
        checkmin(ans,ret);
    }
    cout<<ans<<endl;
    return 0;
}