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
const int N=1000005;
const int MOD1=19260817;
const int MOD2=77090107;
const int B=41;
pii operator + (pii x,pii y){
    return mk((x.first+y.first)%MOD1,(x.second+y.second)%MOD2);
}
pii operator - (pii x,pii y){
    return mk((x.first-y.first+MOD1)%MOD1,(x.second-y.second+MOD2)%MOD2);
}
pii operator * (pii x,int y){
    return mk(1ll*x.first*y%MOD1,1ll*x.second*y*MOD2);
}
string s[N];
int n,m;
pii Base[N];
pii h[N],l[N];
pii Hash(string s){
    pii ret=mk(0,0);
    for(int i=0;i<sz(s);i++) ret=ret+(Base[i]*(s[i]-'a'));
    return ret;
}

void init(){
    cin>>n>>m;
    for(int i=0;i<n;i++) cin>>s[i];
    Base[0]=mk(1,1);
    for(int i=1;i<=max(n,m);i++) Base[i]=Base[i-1]*B;
    for(int i=0;i<n;i++) l[i]=Hash(s[i]);
    for(int i=0;i<m;i++){
        string S="";
        for(int j=0;j<n;j++) S+=s[j][i];
        h[i]=Hash(S);
    }
}

int le[N];
void manacher(pii *a,int len){
    static pii A[N<<1]; static int d[N<<1];
    A[1]=mk(-1,-1);
    for(int i=0;i<len;i++) A[i*2+2]=a[i],A[i*2+3]=mk(-1,-1);
    d[1]=1; int best=1;
    len=len*2+1;
    for(int i=2;i<=len;i++){
        int lim=best+d[best]-1;
        if(i>lim){
            int l=i-1,r=i+1;
            while(l>=1&&r<=len&&A[l]==A[r]) l--,r++;
            d[i]=r-i;
        }
        else{
            int mir=best*2-i; d[i]=d[mir];
            d[i]=min(d[i],lim-i+1);
            int r=d[i]+i,l=i-d[i];
            while(l>=1&&r<=len&&A[l]==A[r]) l--,r++;
            d[i]=r-i;
        }
        if(best+d[best]<i+d[i]) best=i;
    }
    for(int i=1;i<=len;i+=2){
        le[i/2]=d[i]/2;
    }
}

int blR[N],blL[N],sumR[N];
void run(int len){
    memset(blL,0,sizeof(blL));
    memset(blR,0,sizeof(blR));
    blL[0]=1; blR[len]=1;
    int mx=0;
    for(int i=1;i<=len;i++){
        if(mx>=i-le[i]) blL[i]=1,mx=i;
    }
    int mi=len;
    for(int i=len-1;i>=0;i--){
        if(mi<=i+le[i]) blR[i]=1,mi=i;
    }
}

void solve(){
    ll tmp1=0,tmp2=0;
    manacher(l,n);
    run(n);
    sumR[n]=blR[n];
    for(int i=n-1;i>=0;i--) sumR[i]=sumR[i+1]+blR[i];
    for(int i=0;i<n;i++) if(blL[i]) tmp1+=sumR[i+1];
    manacher(h,m);
    run(m);
    sumR[m]=blR[m];
    for(int i=m-1;i>=0;i--) sumR[i]=sumR[i+1]+blR[i];
    for(int i=0;i<m;i++) if(blL[i]) tmp2+=sumR[i+1];
    printf("%lld\n",tmp1*tmp2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    init(); solve();
    return 0;
}