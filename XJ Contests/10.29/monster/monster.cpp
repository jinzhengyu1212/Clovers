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
const int N=500005;
int n,X,Y,a[N],b[N];
ll sum=1,ans=0;
priority_queue<int> Q;

int main()
{
    n=read(); X=read(); Y=read();
    for(int i=1;i<=n;i++){
        a[i]=read(); b[i]=(a[i]+Y-1)/Y-1;
        int rest=a[i]-b[i]*Y;
        a[i]=(rest+X-1)/X;
    }
    while(!Q.empty()) Q.pop();
    for(int i=1;i<=n;i++){
        sum+=b[i];
        if(sum>=a[i]) sum-=a[i],ans++,Q.push(a[i]);
        else{
            if(Q.empty()){
                sum++; continue;
            }
            int u=Q.top(); 
            if(u>a[i]) sum+=u+1-a[i],Q.pop(),Q.push(a[i]);
            else sum++;
        }
    }
    cout<<ans<<endl;
    return 0;
}