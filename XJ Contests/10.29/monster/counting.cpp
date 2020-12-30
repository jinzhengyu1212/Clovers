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
string s; int n,L;
map<string,int> mp;
string ins(string S,string X,int pos){//after pos
    string ret="";
    for(int i=0;i<=pos;i++) ret+=S[i];
    ret=ret+X; 
    for(int i=pos+1;i<sz(S);i++) ret+=s[i];
    return ret;
}
string del(string S,int pos,int len){
    string ret="";
    for(int i=0;i<pos;i++) ret+=S[i];
    for(int i=pos+len;i<sz(S);i++) ret+=S[i];
    return ret;
}
int ans=0;

void dfs(string S,int len){
    if(len>10) return;
    cout<<S<<" "<<len<<endl;
    if(len==L){
        cout<<S<<"PPP\n"<<endl;
        ans++;
    }
    for(int i=0;i<sz(S);i++){
        string t="aa",tmp=ins(S,t,i);
        if(!mp.count(tmp)) mp[tmp]=1, dfs(tmp,len+2);
        t="bbb",tmp=ins(S,t,i);
        if(!mp.count(tmp)) mp[tmp]=1,dfs(tmp,len+3);
        t="ababab",tmp=ins(S,t,i);
        if(!mp.count(tmp)) mp[tmp]=1,dfs(tmp,len+6);
    }
    for(int i=0;i<sz(S);i++){
        if(sz(S)-i>=2&&S.substr(i,2)=="aa"){
            string tmp=del(S,i,2);
            if(!mp.count(tmp)) mp[tmp]=1,dfs(tmp,len-2);
        }
        if(sz(S)-i>=3&&S.substr(i,3)=="bbb"){
            string tmp=del(S,i,3);
            if(!mp.count(tmp)) mp[tmp]=1,dfs(tmp,len-3);
        }
        if(sz(S)-i>=6&&S.substr(i,6)=="ababab"){
            string tmp=del(S,i,6);
            if(!mp.count(tmp)) mp[tmp]=1,dfs(tmp,len-6);
        }
    }
} 

int main()
{
    cin>>s; 
    n=sz(s);
    scanf("%d",&L);
    if(L==0&&n<=2){
        if(s[1]=='a'&&s[2]=='a') puts("1");
        else puts("0");
        return 0;
    }
    dfs(s,n);
    cout<<ans<<endl;
    return 0;
}