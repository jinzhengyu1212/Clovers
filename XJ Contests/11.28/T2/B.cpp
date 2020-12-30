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
typedef vector<int> V;
typedef vector<V> mac;
const int inv2=(MOD+1)/2;

int n,m; mac a;
void init(){
    n=read(); m=read();
    a.resize(n);
    for(int i=0;i<n;i++) a[i].resize(m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) a[i][j]=read();
    }
}

int ans0=0,ans1=0,ans2=0,ans3=0;
namespace solver0{
    void main(){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                int x=(i+1)*(j+1),y=(n-i)*(m-j);
                Add(ans0,mul(mul(x,y),a[i][j]));
            }
        }
    }
}

namespace solver1{
    mac pre,b;
    void init(int bl){
        pre.resize(n);
        for(int i=0;i<n;i++){
            pre[i].resize(m); pre[i][0]=-1;
            for(int j=0;j<m;j++){
                if(b[i][j]==bl) pre[i][j]=j;
                else if(j) pre[i][j]=pre[i][j-1];
            }
        }
    }
    int stk[N],top=0;
    int solve(int bit,int bl){
        init(bl);
        int ret=0;
        for(int j=0;j<m;j++){
            top=0;
            ret+=j-pre[0][j]; 
            int sum=j-pre[0][j];
            stk[++top]=0;
            for(int i=1;i<n;i++){
                int tmp=j-pre[i][j];
                while(true){
                    if(top==0) break;
                    int now=stk[top],val=j-pre[now][j];
                    if(tmp>val) break;
                    top--; 
                    int dis=(top==0 ? now+1 : now-stk[top]);
                    sum-=dis*val;
                }
                if(!top) sum+=(i+1)*tmp;
                else sum+=(i-stk[top])*tmp;
                stk[++top]=i;
                ret+=sum;
            }
        }
        int S=mul(n,mul(n+1,inv2));
        Mul(S,mul(m,mul(m+1,inv2)));
        if(bl){
            return mul(sub(S,ret),(1ll<<bit)%MOD);
        }
        else return mul(ret,(1ll<<bit)%MOD);
    }
    void main(){
        b=a;
        for(int i=0;i<30;i++){
            for(int p=0;p<n;p++){
                for(int q=0;q<m;q++) b[p][q]=(a[p][q]>>i&1);
            }
            Add(ans1,solve(i,0));
            Add(ans2,solve(i,1));
        }
    }
}

namespace solver2{
    mac sum;
    int query(int sx,int sy,int ex,int ey){
        int x1=(sx==0||sy==0 ? 0 : sum[sx-1][sy-1]);
        int x2=(sx==0 ? 0 : sum[sx-1][ey]);
        int x3=(sy==0 ? 0 : sum[ex][sy-1]);
        return (((sum[ex][ey]^x1)^x2)^x3);
    }
    void main(){
        if(n>100||m>100){
            ans3=-1;
            return;
        }
        sum=a;
        for(int i=1;i<n;i++) sum[i][0]=sum[i-1][0]^a[i][0];
        for(int j=1;j<m;j++) sum[0][j]=sum[0][j-1]^a[0][j];
        for(int i=1;i<n;i++){
            for(int j=1;j<m;j++){
                sum[i][j]=((sum[i-1][j]^sum[i][j-1])^sum[i-1][j-1])^a[i][j];
            }
        }
        for(int ex=0;ex<n;ex++){
            for(int ey=0;ey<m;ey++){
                for(int i=0;i<=ex;i++){
                    for(int j=0;j<=ey;j++){
                        Add(ans3,query(i,j,ex,ey)%MOD);
                    }
                }
            }
        }
    }
}

int main()
{
    init();
    solver0::main();
    solver1::main();
    solver2::main();
    cout<<ans0<<" "<<ans1<<" "<<ans2<<" "<<ans3<<endl;
    return 0;
}