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
const int N=5000000+5;
template<class T>inline void read(T &num){
	char ch;
	while(!isdigit(ch=getchar()));
	num=ch-'0';
	while(isdigit(ch=getchar()))num=num*10+ch-'0';
}

int tri[N][2],is_end[N],fail[N],vis[N],totn,n;
inline void Insert(char s[]){
	int len=strlen(s),x=0;
	for(int p=0;p<len;++p){
		int ch=s[p]-'0';
		if(tri[x][ch]==0)tri[x][ch]=++totn;
		x=tri[x][ch];
	}
	is_end[x]=1;
}

queue<int> que;
inline void Fail(){
	int x=0;
	if(tri[x][0])que.push(tri[x][0]);
	if(tri[x][1])que.push(tri[x][1]);
	while(que.size()){
		x=que.front();que.pop();
		if(is_end[fail[x]])is_end[x]=1;
//printf("fail[%d]=%d\n",x,fail[x]);
		if(tri[x][0])fail[tri[x][0]]=tri[fail[x]][0],que.push(tri[x][0]);
		else tri[x][0]=tri[fail[x]][0];
		if(tri[x][1])fail[tri[x][1]]=tri[fail[x]][1],que.push(tri[x][1]);
		else tri[x][1]=tri[fail[x]][1];
	}
}

bool dfs(int x=0){
//printf("vis[%d]=%d\n",x,vis[x]);
	if(vis[x])return true;
	vis[x]=1;
//printf("tri[x]=(%d,%d)\n",tri[x][0],tri[x][1]);
//printf("is_end(%d,%d)\n",is_end[tri[x][0]],is_end[tri[x][1]]);
	if(!is_end[tri[x][0]])if(dfs(tri[x][0]))return true;
	if(!is_end[tri[x][1]])if(dfs(tri[x][1]))return true;
	vis[x]=0;
	return false;
}

char s[30000+5];
int main(){
	read(n);
	for(int i=1;i<=n;++i){
		scanf("%s",s);
		Insert(s);
	}
	Fail(); 
    for(int i=0;i<=totn;i++) out(i),out(tri[i][0]),outln(tri[i][1]);
	printf("%s",dfs()?"TAK":"NIE");
	return 0;
}