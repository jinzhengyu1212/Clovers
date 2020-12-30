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
const int N=500005;
int n; vector<pii> ans;

int main()
{
    n=read();
    if((n&(-n))==n){puts("No"); return 0;}
    int pos1=-1,pos2=-1;
    if(n%2==0){
        pos1=(n&(-n)),pos2=(n^pos1);
        ans.push_back(mk(pos1+1,n*2));
        ans.push_back(mk(pos2,n));
        ans.push_back(mk(pos1+1,pos1));
        ans.push_back(mk(pos1+n,pos1+n+1));
        ans.push_back(mk(pos2,pos2+1));
        ans.push_back(mk(pos2+n+1,pos2+n));
        ans.push_back(mk(1,pos1+1)); ans.push_back(mk(1,pos1+n));
        ans.push_back(mk(1,pos2)); ans.push_back(mk(1,pos2+n+1));
    }
    int lst=n+n-2;
    for(int i=2;i<n;i+=2) if(pos1!=i&&pos2!=i){
        ans.push_back(mk(1,i)); ans.push_back(mk(1,i+n+1));
        ans.push_back(mk(i,i+1)); ans.push_back(mk(i+n+1,i+n));
        lst=i+n;
    }
    puts("Yes");
    ans.push_back(mk(lst,n+1));    
    for(auto &to : ans) printf("%d %d\n",to.first,to.second);
    return 0;
}