#include <stdio.h>
#define inf 1999999999
#define md 1000000007
#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b
int az[12],al[12],ar[12],w[12],aa[500010][12];
int B[12],C[500010],D[500010],la[500010][12],ra[500010][12];
int ksm(int a,int b) {
	int jg=1;
	while(b>0) {
		if(b&1)
			jg=1ll*jg*a%md;
		a=1ll*a*a%md;
		b=(b>>1);
	}
	return jg;
}
int Cc[12][12],xs[12][12];
void GetB(int k)//伯努利数 
{
	B[0]=1;
	for (int i=1;i<=k+1;i++) {
		for (int j=0;j<=i;j++) {
			if(j==0||j==i)Cc[i][j]=1; 
			else Cc[i][j]=(Cc[i-1][j]+Cc[i-1][j-1])%md;
		}
	}
	for (int i=1;i<=k;i++) {
		int h=0;
		for (int j=0;j<i;j++)
			h=(h+1ll*Cc[i+1][j]*B[j])%md;
		B[i]=1ll*(md-h)*ksm(i+1,md-2)%md;
	}
	for (int i=1;i<=k;i++) {
		int ny=ksm(i+1,md-2);
		for (int j=0;j<=i;j++)
			xs[i][i+1-j]=1ll*Cc[i+1][j]*B[j]%md*ny%md;
	}
}
struct SLi//一次函数 
{
	int k,b;
	SLi() {}
	SLi(int K,int B) {
		k=K;b=B;
	}
	SLi(int Z) {
		k=0;b=Z;
	}
};
SLi operator-(const SLi &x,const SLi &y) {
	return SLi(x.k-y.k,x.b-y.b);
}
int Sum(int k,int n) {
	if(k==0)
		return n+1;
	int jg=0;
	for (int i=0,j=1;i<=k+1;i++) {
		jg=(jg+1ll*j*xs[k][i])%md;
		j=1ll*j*(n+1)%md;
	}
	return jg;
}
struct DXS//多项式 
{
	int sz[12],n;
	void operator=(const DXS &a) {
		n=a.n;
		for (int i=0;i<=n;i++)
			sz[i]=a.sz[i];
	}
	void clear() {
		for (int i=1;i<=10;i++)
			sz[i]=0;
		sz[0]=1;n=0;
	}
	int sum(int l,int r) {
		int ans=0;
		for (int i=0;i<=n;i++) {
			int t=(Sum(i,r)-Sum(i,l-1)+md)%md;
			ans=(ans+1ll*sz[i]*t)%md;
		}
		return ans;
	}
};
DXS operator*(const DXS&x,const SLi&y) {
	DXS rt;
	rt.n=x.n+1;
	rt.sz[rt.n]=0;
	for (int i=0;i<=x.n;i++)
		rt.sz[i]=1ll*y.b*x.sz[i]%md;
	for (int i=0;i<=x.n;i++)
		rt.sz[i+1]=(rt.sz[i+1]+1ll*y.k*x.sz[i])%md;
	return rt;
}
struct SQj//维护区间 
{
	int l,r;
	SQj() {}
	SQj(int L,int R) {
		l=L;r=R;
	}
};
SQj jiao(const SQj&a,const SQj&b) {
	return SQj(max(a.l,b.l),min(a.r,b.r));
}
int floor(int,int);
int ceil(int x,int y) {
	if(y<0)x=-x,y=-y;
	if(x>=0)return (x+y-1)/y;
	return -floor(-x,y);
}
int floor(int x,int y) {
	if(y<0)x=-x,y=-y;
	if(x>=0)return x/y;
	return -ceil(-x,y);
}
SQj Less(SLi a,SLi b) {
	int x=a.k-b.k,y=b.b-a.b;
	if(x==0)return y>=0?SQj(-inf,inf):SQj(inf,-inf);
	if(x>0)return SQj(-inf,floor(y,x));
	return SQj(ceil(y,x),inf);
}
SQj More(SLi a,SLi b) {
	int x=a.k-b.k,y=b.b-a.b;
	if(x==0)return y<=0?SQj(-inf,inf):SQj(inf,-inf);
	if(x>0)return SQj(ceil(y,x),inf);
	return SQj(-inf,floor(y,x));
}
int cal0(int n,int i,int k) {
	int l[12],r[12],jg=1;
	for (int c=1;c<=k;c++)
		l[c]=la[i][c],r[c]=ra[i][c];
	for (int c=1;c<=k;c++) {
		int zl=1-l[c],zr=w[c]-r[c];
		if(c!=C[(i+1)%n]) {
			int s=zr-zl+1;
			if(s<0)s=0;
			jg=1ll*jg*s%md;
		} 
		else {
			int t=aa[i][c],s=0;
			if(D[(i+1)%n]==1) {
				int o=w[c]-t;
				if(o>=zl&&o<=zr)s=1;
			} 
			else {
				int o=1-t;
				if(o>=zl&&o<=zr)s=1;
			}
			jg=1ll*jg*s%md;
		}
	}
	return 1ll*(i+2)*jg%md;
}
int main() {
	int n,k;
	scanf("%d%d",&n,&k);GetB(k);
	for (int i=1;i<=k;i++)
		scanf("%d",&w[i]);
	for (int i=0;i<n;i++) {
		scanf("%d%d",&C[i],&D[i]);
		if(i>0) {
			for (int j=1;j<=k;j++)
				aa[i][j]=aa[i-1][j];
		}
		aa[i][C[i]]+=D[i];//循环节中某一前缀的偏移量
		az[C[i]]+=D[i];
		if(az[C[i]]<al[C[i]])//最左移位
			al[C[i]]=az[C[i]];
		if(az[C[i]]>ar[C[i]])//最右移位
			ar[C[i]]=az[C[i]];
		for (int j=1;j<=k;j++) {
			la[i][j]=al[j];ra[i][j]=ar[j];
		}
	}
	bool zd=false;
	for (int i=1;i<=k;i++) {
		if(az[i]!=0||ar[i]-al[i]>=w[i]) {
			zd=true;break;
		}
	}
	if(!zd)//走不出去 
	{
		printf("-1");
		return 0;
	}
	int ans=1;
	for (int i=1;i<=k;i++) {
		if(i!=C[0])
			ans=1ll*ans*w[i]%md;
	}
	for (int i=0;i<n;i++) {
		ans=(ans+cal0(n,i,k))%md;//特殊处理x=0的情况
		SLi l[12],r[12],d[12];
		for (int c=1;c<=k;c++)//算出对应维度的一次函数 
		{
			if(az[c]>=0) {
				l[c]=al[c];
				int t=az[c]+ra[i][c];
				if(ar[c]>t)t=ar[c];
				r[c]=SLi(az[c],t-az[c]);
			} 
			else {
				r[c]=ar[c];
				int t=az[c]+la[i][c];
				if(al[c]<t)t=al[c];
				l[c]=SLi(az[c],t-az[c]);
			}
			d[c]=r[c]-l[c];
		}
		int tc=C[(i+1)%n];
		SLi o;SLi tz=SLi(az[tc],aa[i][tc]);
		if(D[(i+1)%n]==1)o=w[tc]-tz; 
		else o=1-tz;
		SLi zl=1-l[tc],zr=w[tc]-r[tc];//tc这一维度起点的范围
		SQj qj=jiao(More(o,zl),Less(o,zr));//tc这一维度起点是确定的，需要满足条件
		for (int i=1;i<=k;i++) {
			d[i]=w[i]-d[i];
			qj=jiao(qj,More(d[i],1));//方案数>0
		}
		qj=jiao(qj,SQj(1,inf));
		if(qj.l>qj.r)continue;
		DXS ji;ji.clear();ji=ji*SLi(n,i+2);
		for (int c=1;c<=k;c++)//对应维度相乘 
		{
			if(c!=tc)
				ji=ji*d[c];
		}
		ans=(ans+ji.sum(qj.l,qj.r))%md;
	}
	printf("%d",(ans%md+md)%md);
	return 0;
}