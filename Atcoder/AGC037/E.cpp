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
const int N=5005;
int n,k;
string s,ans,t; char c='z';
int flag=0;
string cut(string s,int pos){
    string ret="";
    int pos2=n-pos;
    for(int i=pos2;i<n;i++) ret+=s[i];
    for(int i=n-1;i>=pos;i--) ret+=s[i];
    return ret;
}
void solve(string s){
    flag=0;
    if(s=="abbaabbbaa") flag=1;
    for(int i=1;i<k;i++){
        int pos=n-1;
        while(pos&&s[pos-1]==c) pos--;
        s=cut(s,pos);
    }
    string tmp=s; reverse(tmp.begin(),tmp.end());
    s=s+tmp;
    int pos=n-1;
    while(pos&&s[pos-1]==c) pos--;
    ans=min(ans,s.substr(pos,n));
}

int main()
{
    n=read(); k=read();
    cin>>s;
    for(int i=0;i<n;i++) c=min(c,s[i]);
    ans=s;
    if(k>=20){
        for(int i=1;i<=n;i++) printf("%c",c);
        puts("");
        return 0;
    }
    if(k==1){
        for(int i=0;i<n;i++) ans=min(ans,cut(s,i));
        cout<<ans<<endl;
        return 0;
    }
    k--;
    for(int i=0;i<n;i++){
        if(s[i]==c&&s[i-1]!=c){
            t=cut(s,i);
            solve(t);
        }
    }
    cout<<ans<<endl;
    return 0;
}