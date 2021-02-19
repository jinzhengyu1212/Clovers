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
const int N=6005;
int n,posa[N],posb[N],match[N]; char s[N];
string dp[N]; int first[N];
void init(){
    int topa=0,topb=0;
    for(int i=1;i<=n*2;i++){
        if(s[i]=='a') posa[++topa]=i;
        else posb[++topb]=i;
    }
    for(int i=1;i<=n;i++) match[posa[i]]=posb[i],match[posb[i]]=posa[i];
}

int main()
{
    n=read(); scanf("%s",s+1);
    init();
    dp[n]=(posa[n]<posb[n] ? "ab" : "ba"); dp[0]="";
    first[n]=min(posa[n],posb[n]);
    for(int i=n-1;i>=1;i--){
        dp[i]=dp[i+1];
        first[i]=first[i+1];
        if(posa[i]<posb[i]){
            int pos=-1;
            for(int j=i+1;j<=n;j++){
                if(first[j]>posb[i]){pos=j; break;}
            }
            if(pos!=-1){
                string tmp=dp[pos];
                tmp="ab"+tmp;
                if(tmp>dp[i]){
                    first[i]=posa[i];
                    dp[i]=tmp;
                }
            }
        }
        else{
            vector<int> v; v.clear();
            int l=posb[i]-1,r=posb[i];
            while(l<r){
                l++; 
                if(s[l]=='b'){
                    r=match[l];
                    v.push_back(l); v.push_back(r);
                }
            }
            sort(v.begin(),v.end());
            string tmp="";
            for(auto &u : v) tmp+=s[u];
            int pos=0;
            for(int j=i+1;j<=n;j++){
                if(first[j]>v.back()){pos=j; break;}
            }
            tmp+=dp[pos];
            if(tmp>dp[i]){
                first[i]=posb[i];
                dp[i]=tmp;
            }
        }
        //cout<<i<<" "<<dp[i]<<endl;
    }
    cout<<dp[1]<<endl;
    return 0;
}