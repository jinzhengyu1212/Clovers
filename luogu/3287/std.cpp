#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define maxn 10000+10
#define maxk 500+10
#define large 6000
using namespace std;
int n,k,mx,ans;
int h[maxn],tree[large][maxk];
int lowbit(const int a)
{
	return a&(-a);
}
void update(int pos,const int val,int sel)
{
	for(;pos<=mx+k;pos+=lowbit(pos))
	    for(int i=sel;i<=k+1;i+=lowbit(i))
		tree[pos][i]=max(tree[pos][i],val);
}
int search(int pos,int sel)
{
	int ans=0;
	for(;pos;pos-=lowbit(pos))
	    for(int i=sel;i;i-=lowbit(i))
		ans=max(ans,tree[pos][i]);
	return ans;
}
int main(void)
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&h[i]);
		mx=max(mx,h[i]);
	}
	for(int i=1;i<=n;i++)
	    for(int j=k;j>=0;j--)
	    {
	    	int x=search(h[i]+j,j+1)+1; 
	    	ans=max(ans,x);
	    	update(h[i]+j,x,j+1);
	    }
	cout<<ans<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}