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
int n,c,Q,cnt[N][105],pre[N][105],h[N],f[N];
int calc(int n,int num){
    int x1=n/num,y1=n%num;
    return num*c+x1*x1*(num-y1)+(x1+1)*(x1+1)*y1;
}

signed main()
{
    n=read(); c=read(); Q=read();
    for(int i=1;i<=n;i++) h[i]=read();
    sort(h+1,h+n+1);
    int k=sqrt(c);
    if(k*(k+1)<c) k++;//k+1 is better
    for(int i=1,j=1;i<=c+k;i++){
        while(calc(i,j)>calc(i,j+1)) j++;
        f[i]=calc(i,j);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<k;j++) pre[i][j]=pre[i-1][j],cnt[i][j]=cnt[i-1][j];
        pre[i][h[i]%k]+=(h[i]/k); cnt[i][h[i]%k]++;
    }
    while(Q--){
        int K=read();
        int pos=upper_bound(h+1,h+n+1,K)-h-1,ans=0;
        if(!pos){puts("0"); continue;}
        while(pos&&h[pos]>=K-c) ans+=f[K-h[pos]],pos--;
        for(int i=1;i<=k;i++){
            int rest=((K-c-i)%k+k)%k,num=cnt[pos][rest];
            int now=(K-c-i)/k*num-pre[pos][rest];
            ans+=f[c+i]*num+now*(k*k+c);
        }
        printf("%lld\n",ans);
    }
    return 0;
}