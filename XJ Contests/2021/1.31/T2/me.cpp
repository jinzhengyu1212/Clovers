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
const int MOD=1e9+7;
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
#define int long long
int n,k,C[66][66],Base[66];

namespace solver1{
    void main(){
        int ans=0;
        for(int a=0;a<n;a++){
            int sum=0;
            for(int pre=1;pre<k;pre++){
                int mx=0;
                for(int i=0;i<=k-pre-1;i++){
                    int rest=n-(pre+i)*a;
                    if(rest%(k-pre-i)==0) checkmax(mx,C[k-pre-1][i]);
                }
                sum+=mx;
            }
            checkmax(ans,sum);
        }
        cout<<ans*2<<endl;
    }
}

#define ran(l,r) rand()%((r)-(l)+1)+(l)
namespace solver2{
    void main(){
        int ans=0;
        int tmp=20000;
        srand(time(0));
        while(tmp--){
            int a=ran(1,n);
            int sum=0;
            for(int pre=1;pre<k;pre++){
                int mx=0;
                for(int i=0;i<=k-pre-1;i++){
                    int rest=n-(pre+i)*a;
                    if(rest%(k-pre-i)==0) checkmax(mx,C[k-pre-1][i]);
                }
                sum+=mx;
            }
            checkmax(ans,sum);
        }
        cout<<ans*2<<endl;
    }
}

signed main()
{
    k=read(); n=read();
    C[0][0]=1;
    for(int i=1;i<=k;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++) C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
    Base[0]=1; for(int i=1;i<=k;i++) Base[i]=Base[i-1]*2;
    if(n%k==0){
        printf("%lld\n",Base[k]);
        return 0;
    }
    else if(1ll*n*k*k<=100000000){
        solver1::main();
        return 0;
    }
    solver2::main();
    return 0;
}