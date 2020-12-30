#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define mk make_pair
#define out(x) cerr<<#x<<" = "<<x<<" "
#define outln(x) cerr<<#x<<" = "<<x<<endl
using namespace std;
const int N=1005;
const int MOD=998244353;
inline int read() {
    int f = 1, x = 0;
    char s = getchar();
    while (s < '0' || s > '9') {
        if (s == '-')
            f = -1;
        s = getchar();
    }
    while (s >= '0' && s <= '9') {
        x = x * 10 + s - '0';
        s = getchar();
    }
    return x * f;
}
int T,n,m;
int a[2005],b[2005];
int n1,n2,m1,m2;
int h1[2005],h2[2005],l1[2005],l2[2005],F,BL=0,sum;
bitset<1000001> dp[1000];
void init()
{
	BL=0;
	n = read();
	for (int i=1;i<=n;++i) a[i] = read();
	m = read();
	for (int i=1;i<=m;++i) b[i] = read();
	for (int i=0;i<=n;++i) dp[i].reset();
	dp[0][0]=1;
	sum=0;
	for (int i=1;i<=n;++i)
	{
		sum+=a[i];
		dp[i]=dp[i-1]|(dp[i-1]<<a[i]);
	}
	if (sum%2)
	{
		printf("No\n");
		BL=1;
		return;
	}
	F=sum/2;
	if (!(dp[n][F]))
	{
		puts("No");
		BL=1;
		return;
	}
	n1=0,n2=0;
	for (int i=n;i>=1;--i)
	{
		if (dp[i-1][F])
		{
			h2[++n2]=a[i];
		}
		else if (dp[i-1][F-a[i]])
		{
			h1[++n1]=a[i];
			F-=a[i];
		}
	}
	for (int i=0;i<=m;++i) dp[i].reset();
	dp[0][0]=1;
	sum=0;
	for (int i=1;i<=m;++i)
	{
		sum+=b[i];
		dp[i]=dp[i-1]|(dp[i-1]<<b[i]);
	}
	if (sum%2)
	{
		puts("No");
		BL=1;
		return ;
	}
	F=sum/2;
	if (!(dp[m][F]))
	{
		printf("No\n");
		BL=1;
		return;
	}
	m1=0,m2=0;
	for (int i=m;i>=1;--i)
	{
		if (dp[i-1][F])
		{
			l2[++m2]=b[i];
		}
		else if (dp[i-1][F-b[i]])
		{
			F-=b[i];
			l1[++m1]=b[i];
        }
    }
	if(n!=m){
		puts("No");
		BL=1;
		return;
	}
}

bool cmp(int x,int y){return x>y;}
void solve(){
    puts("Yes");
    int ch=0;
    int maxn=max(n1,n2);
    int maxm=max(m1,m2);
    if(maxm<maxn) swap(l1,h1),swap(l2,h2),swap(n1,m1),swap(n2,m2),ch=1;
    if(m1>m2) swap(l1,l2),swap(m1,m2);
    if(n1<n2) swap(n1,n2),swap(h1,h2);
    sort(l1+1,l1+m1+1,cmp);
    sort(l2+1,l2+m2+1,cmp);
    sort(h1+1,h1+n1+1);
    sort(h2+1,h2+n2+1);
    int nowx=0,nowy=0,flag1=0,flag2=0;
    int i=1,j=1;
    int rnd=0;
    while(1){
        if(rnd&1){
            if(flag2==0) nowy+=h1[j],j++;
            else nowy-=h2[j],j++;
            if(j>n1&&!flag2) j=1,flag2=1;
        }
        else{
            if(flag1==0) nowx+=l1[i],i++;
            else nowx-=l2[i],i++;
            if(i>m1&&!flag1) i=1,flag1=1;
        }
        rnd++;
        if(!ch) printf("%d %d\n",nowy,nowx);
        else printf("%d %d\n",nowx,nowy);
        if(nowx==0&&nowy==0) return;
    }
}

signed main()
{
    scanf("%d",&T);
    while(T--)
    {
        init(); 
        if(!BL) solve();
    }
    return 0;
}
