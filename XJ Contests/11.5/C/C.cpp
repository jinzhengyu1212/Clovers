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
const int N=500005;
const int M=1005;
int n,m;
namespace solver1{
    int dp[2][1024][3];
    int calc(int mask){
        int ret=0,flag=0;
        for(int i=0;i<m;i++){
            if(mask>>i&1) flag=1;
            else ret+=flag,flag=0;
        }
        ret+=flag;
        return ret;
    }
    void main(){
        int full=(1<<m)-1;
        dp[1][full][0]=dp[1][full][2]=1;
        dp[1][full][1]=2;
        int idx=1;
        vector<int> v;
        for(int i=1;i<n;i++){
            memset(dp[idx^1],0,sizeof(dp[idx^1]));
            for(int mask1=1;mask1<=full;mask1++){
                for(int j=0;j<=2;j++){
                    if(!dp[idx][mask1][j]) continue;
                    int tmp=dp[idx][mask1][j];
                    for(int mask=mask1;mask!=0;mask=(mask-1)&mask1){
                        int cnt=calc(mask);
                        for(int del=0;del<=2-j;del++){
                            int K;
                            if(!del) K=1;
                            else if(del==1) K=(j==0 ? 2 : 1)*cnt;
                            else if(del==2) K=mul(cnt,cnt);
                            dp[idx^1][mask][j+del]=add(dp[idx^1][mask][j+del],mul(tmp,K));
                        }
                    }
                }
            }
            idx^=1;
        }
        int ans=0;
        for(int mask=1;mask<=full;mask++) ans=add(ans,dp[idx][mask][2]);
        cout<<ans<<endl;
    }
}

namespace solver2{
    int dp[2][5005][2][3];
    void main(){
        dp[0][0][0][0]=1;
        int idx=1;
        for(int i=1;i<=m;i++){
            memset(dp[idx],0,sizeof(dp[idx]));
            for(int j=1;j<=n;j++){
                for(int pre=0;pre<=n;pre++){
                    int del=max(j-pre,0);
                    dp[idx][j][0][0]=add(dp[idx][j][0][0],dp[idx^1][pre][0][0]);
                    dp[idx][j][0][1]=add(dp[idx][j][0][1],dp[idx^1][pre][0][1]);
                    if(del) dp[idx][j][0][1]=add(dp[idx][j][0][1],mul(dp[idx^1][pre][0][0],del));
                    dp[idx][j][0][2]=add(dp[idx][j][0][2],dp[idx^1][j][0][2]);
                }                
            }
        }
    }
}

int main()
{
    scanf("%d%d",&m,&n);
    if(m<=10){
        solver1::main();
        return 0;
    }
    else solver2::main();
    return 0;
}