#include <bits/stdc++.h>
using namespace std;
const int N=200005;
#define int long long
int n,m,v,p,pos,tmp;
int a[N],sum[N],t[N];

bool cmp(int x,int y)
{
	return x>y;
}

bool check(int x)
{
	if(x<=p) return 1;
	int rest=v-(p-1)-(n-x+1);
	if(rest<0) rest=0;
	int choose=n-(p-1)-(n-x+1);
	int Sum=0;
	for(int i=1;i<=choose;i++) t[i]=a[i+p-1]-a[x],Sum+=t[i];
	if(a[x]+m<a[p]) return 0;
	return Sum<=m*(choose-rest);
}

signed main() 
{
	scanf("%lld%lld%lld%lld",&n,&m,&v,&p);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	sort(a+1,a+n+1,cmp);
	int now=1;
	for(int i=1;i<=n;i++)
	{
		sum[i]=sum[i-1]+a[i];
	}
	int l=p,r=n,mid,best;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid)) l=mid+1,best=mid;
		else r=mid-1;
	}
	cout<<best<<endl;
	return 0;
}
