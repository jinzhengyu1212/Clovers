#include<bits/stdc++.h>
using namespace std;
#define RI register int
int read() {
	int q=0;char ch=' ';
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
	return q;
}
typedef long long LL;
const int N=120005;
int n,Q,top1,top2;
int a[N],mi[N<<2],js[N<<2],laz[N<<2],ti[N<<2],st1[N],st2[N];
//mi:最小值 js:最小值个数 laz:最小值的加减标记 ti:答案更新标记 ans:区间答案
LL ans[N<<2],res[N];
struct node{int l,r,id;}q[N];
int cmp(node x,node y) {return x.r<y.r;}

void addmi(int i,int num) {mi[i]+=num,laz[i]+=num;}
void addti(int i,int num) {ans[i]+=1LL*js[i]*num,ti[i]+=num;}
void pd(int i) {
	int l=i<<1,r=(i<<1)|1;
	if(laz[i]) addmi(l,laz[i]),addmi(r,laz[i]),laz[i]=0;//先下放laz，再下放ti
	if(ti[i]) {//右端点取r时，[r,r]肯定是0，所以整棵线段树的最小值是0
		if(mi[l]==mi[i]) addti(l,ti[i]);
		if(mi[r]==mi[i]) addti(r,ti[i]);
		//在做这个过程时，可能一次移动右端点更新还没有完成，又已经下放了laz，所以不能写成mi[l]==0
		ti[i]=0;
	}
}
void up(int i) {
	int l=i<<1,r=(i<<1)|1;
	mi[i]=min(mi[l],mi[r]),js[i]=0;
	if(mi[l]==mi[i]) js[i]+=js[l];
	if(mi[r]==mi[i]) js[i]+=js[r];
	ans[i]=ans[l]+ans[r];
}
void build(int s,int t,int i) {
	mi[i]=s,js[i]=1;//一开始将mi[i]=s，最小值个数的计算才是对的。
	if(s==t) return;
	int mid=(s+t)>>1;
	build(s,mid,i<<1),build(mid+1,t,(i<<1)|1);
}
void add(int l,int r,int s,int t,int i,int num) {
	if(l<=s&&t<=r) {addmi(i,num);return;}
	int mid=(s+t)>>1;pd(i);
	if(l<=mid) add(l,r,s,mid,i<<1,num);
	if(mid+1<=r) add(l,r,mid+1,t,(i<<1)|1,num);
	up(i);
}
LL query(int l,int r,int s,int t,int i) {
	if(l<=s&&t<=r) return ans[i];
	int mid=(s+t)>>1;LL re=0;pd(i);
	if(l<=mid) re=query(l,r,s,mid,i<<1);
	if(mid+1<=r) re+=query(l,r,mid+1,t,(i<<1)|1);
	return re;
}
int main()
{
    int x,y;
    n=read();
    for(RI i=1;i<=n;++i) a[i]=read();
    Q=read();
    for(RI i=1;i<=Q;++i) q[i].l=read(),q[i].r=read(),q[i].id=i;
    sort(q+1,q+1+Q,cmp);
    build(1,n,1);
    for(RI i=1,j=1;i<=n;++i) {
    	addmi(1,-1);
    	while(top1&&a[i]>a[st1[top1]]) {
    		add(st1[top1-1]+1,st1[top1],1,n,1,a[i]-a[st1[top1]]);
    		--top1;
    	}
    	st1[++top1]=i;
    	while(top2&&a[i]<a[st2[top2]]) {
    		add(st2[top2-1]+1,st2[top2],1,n,1,a[st2[top2]]-a[i]);
    		--top2;
    	}
    	st2[++top2]=i;
    	addti(1,1);//打一个time标记，把当前右端点造成的贡献下放
    	while(j<=Q&&q[j].r==i) res[q[j].id]=query(q[j].l,q[j].r,1,n,1),++j;
    }
    for(RI i=1;i<=Q;++i) printf("%lld\n",res[i]);
    return 0;
}
//stone 0