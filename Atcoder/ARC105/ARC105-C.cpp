#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mk make_pair
#define int long long
typedef pair<int,int> pii;
const int inf=(int)(2e9);
const ll INF=(ll)(5e13);
const int N=500010;
 
int n,w[10];
int m,l[N],v[N],minn=INF,ans=INF;
pii a[N];
bool cmp(pii x,pii y){return x>y;}
stack<int> stk;
 
void init(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&w[i]);
	for(int i=1;i<=m;i++) scanf("%lld%lld",&a[i].second,&a[i].first),minn=min(minn,a[i].first);
	for(int i=1;i<=n;i++){
		if(w[i]>minn){
			puts("-1");
			exit(0);
		}
	}
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++){
		while(!stk.empty()&&a[stk.top()].second<=a[i].second){
			stk.pop();
		}
		stk.push(i);
	}
	m=0;
	while(!stk.empty()) l[++m]=a[stk.top()].second, v[m]=a[stk.top()].first, stk.pop();
}
 
int ti[10];
bool check(int mid,int id){
	int tot=ti[id-1]+mid,W=w[id];
	if(mid>=l[m]) return 1;
	for(int i=id-1;i>=1;i--){
		int now=tot-ti[i]; W+=w[i];
		int pos=upper_bound(l+1,l+m+1,now)-l;
		if(pos!=m+1){
			if(W>v[pos]) return 0;
		}
	}
	return 1;
}
int solve(){
	ti[1]=0; 
	for(int i=1;i<=n;i++){
		if(i==1) continue;
		int l=0,r=min(ans,(int)1e15),mid,best=INF;
		while(l<=r){
			mid=(l+r)>>1;
			if(check(mid,i)) r=mid-1,best=mid;
			else l=mid+1;
		}
		ti[i]=ti[i-1]+best;
		if(ti[i]>ans) return INF;
	}
	return ti[n];
}
 
signed main()
{
	init();
	do{
		ans=min(ans,solve());	
	}while(next_permutation(w+1,w+n+1));
	cout<<ans<<endl;
	return 0;
}