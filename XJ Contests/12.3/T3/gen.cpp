#include <bits/stdc++.h>
#define setIO(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
#define closefile fclose(stdin),fclose(stdout)
#define m_p make_pair
#define sz(x) (int)x.size()
#define see(x) cerr<<x<<" "
#define seeln(x) cerr<<x<<endl
#define out(x) cerr<<#x<<" = "<<x<<" "
#define outln(x) cerr<<#x<<" = "<<x<<endl
#define outarr(x,l,r) cerr<<#x"["<<l<<"-"<<r<<"] = "; for (int _i=l;_i<=r;++_i) cerr<<x[_i]<<" "; cerr<<endl;
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
template <class T> void read(T &x)
{
	x=0; char c=getchar(); int flag=0;
	while (c<'0'||c>'9') flag|=(c=='-'),c=getchar();
	while (c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	if (flag) x=-x;
}
template <class T> T _max(T a,T b){return a>b ? a : b;}
template <class T> T _min(T a,T b){return a<b ? a : b;}
template <class T> bool checkmax(T &a,T b){return b>a ? a=b,1 : 0;}
template <class T> bool checkmin(T &a,T b){return b<a ? a=b,1 : 0;}
unsigned seed=std::chrono::system_clock::now().time_since_epoch().count();
mt19937 my_rand(seed);
template <class T> T ran(T l,T r){return my_rand()%(r-l+1)+l;}
int a[100005],b[1000005];
void init()
{
	int n=ran(1,10);
	int m=ran(1,10);
	for (int i=1;i<=n;++i) a[i]=i;
	random_shuffle(a+1,a+n+1);
	int now=n;
	printf("%d %d\n",n,m);
	for (int i=1;i<=m;++i)
	{
		int x=ran(2,5);
		if (x==2) --x;
		if (x==1&&now<=1) x=3;
		if (x==1)
		{
			int o1=ran(1,now-1);
			int o2=ran(o1+1,now);
			printf("1 %d %d\n",a[o1],a[o2]);
			int tmp=0;
			for (int j=1;j<=now;++j) if (j^o2) b[++tmp]=a[j];
			for (int j=1;j<=tmp;++j) a[j]=b[j];
			now=tmp;
		}
		else if (x==3)
		{
			int o=ran(1,now);
			int t=ran(1,1000);
			printf("3 %d %d\n",a[o],t);
		}
		else if (x==4)
		{
			int o=ran(1,now);
			int t=ran(1,1000);
			printf("4 %d %d\n",a[o],t);
		}
		else
		{
			int o=ran(1,n);
			printf("5 %d\n",o);
		}
	}
}

void solve()
{
}

int main()
{
	//setIO("");
	init();
	solve();
	closefile;
	return 0;
}
