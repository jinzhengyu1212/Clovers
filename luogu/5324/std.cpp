#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define ll long long
using namespace std;
inline int read(){
	int re=0,flag=1;char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') flag=-1;
		ch=getchar();
	}
	while(isdigit(ch)) re=(re<<1)+(re<<3)+ch-'0',ch=getchar();
	return re*flag;
}
int n,m,a[1000010],cnt[1000010],ori[1000010],pos;
struct ele{//合并用的线段树元素，query的时候很方便，merge就好了
	int minn,cnt;
	ele(int mm=0,int cc=0){minn=mm;cnt=cc;}
	friend inline ele merge(const ele &a,const ele &b){
		ele re;re.minn=min(a.minn,b.minn);
		if(re.minn==a.minn) re.cnt+=a.cnt;
		if(re.minn==b.minn) re.cnt+=b.cnt;
		assert(re.minn>=0);
		return re;
	}
}seg[2000010];int tag[2000010];//有区间修改，加lazytag
inline void pushtag(int num,int w){seg[num].minn+=w;tag[num]+=w;assert(seg[num].minn>=0);}
inline void push(int l,int r,int num){
	if(l==r||!tag[num]) return;
	pushtag(num<<1,tag[num]);
	pushtag(num<<1|1,tag[num]);
	tag[num]=0;
}
inline void build(int l,int r,int num){
	if(l==r){seg[num]=ele(ori[l],1);return;}
	int mid=(l+r)>>1;
	build(l,mid,num<<1);build(mid+1,r,num<<1|1);
	seg[num]=merge(seg[num<<1],seg[num<<1|1]);
}
inline void change(int l,int r,int num,int pos,int w){
	if(l==r){seg[num].minn+=w;return;}
	int mid=(l+r)>>1;push(l,r,num);
	if(mid>=pos) change(l,mid,num<<1,pos,w);
	else change(mid+1,r,num<<1|1,pos,w);
	seg[num]=merge(seg[num<<1],seg[num<<1|1]);
}
inline void add(int l,int r,int ql,int qr,int num,int w){
	if(l>=ql&&r<=qr){pushtag(num,w);return;}
	int mid=(l+r)>>1;push(l,r,num);
	if(mid>=ql) add(l,mid,ql,qr,num<<1,w);
	if(mid<qr) add(mid+1,r,ql,qr,num<<1|1,w);
	seg[num]=merge(seg[num<<1],seg[num<<1|1]);
}
inline ele query(int l,int r,int ql,int qr,int num){
	if(l>=ql&&r<=qr) return seg[num];
	int mid=(l+r)>>1;ele re(2e9,0);push(l,r,num);
	if(mid>=ql) re=merge(re,query(l,mid,ql,qr,num<<1));
	if(mid<qr) re=merge(re,query(mid+1,r,ql,qr,num<<1|1));
	return re;
}
int main(){
	n=read();m=read();int i,t1,t2,j,tot=n+n+m+m;ele ans;
	pos=n+m;
	for(i=1;i<=n;i++) cnt[(a[i]=read()+pos)]++;
	for(i=1;i<=tot;i++) if(cnt[i])
		for(j=i;j>i-cnt[i];j--) ori[j]++;
	build(1,tot,1);
	while(m--){
		t1=read();t2=read();
		if(t1){
			//直接维护，注意不在目前范围内的位置不要change！！！
			t2+=pos;
			cnt[a[t1]]--;ori[a[t1]-cnt[a[t1]]]--;
			if(a[t1]<=pos+n&&a[t1]>pos) change(1,tot,1,a[t1]-cnt[a[t1]],-1);
			a[t1]=t2;
			if(a[t1]<=pos+n&&a[t1]>pos) change(1,tot,1,a[t1]-cnt[a[t1]],1);
			ori[a[t1]-cnt[a[t1]]]++;cnt[a[t1]]++;
		}
		else{
			//查看是否有区间需要加入or删除！！！
			if(~t2){
				pos--;
				if(cnt[pos+n+1]) add(1,tot,pos+n+1-cnt[pos+n+1]+1,pos+n+1,1,-1);
				if(cnt[pos+1]) add(1,tot,pos+1-cnt[pos+1]+1,pos+1,1,1);
			}
			else{
				pos++;
				if(cnt[pos+n]) add(1,tot,pos+n-cnt[pos+n]+1,pos+n,1,1);
				if(cnt[pos]) add(1,tot,pos-cnt[pos]+1,pos,1,-1);
			}
		}
		ans=query(1,tot,pos+1,pos+n,1);
		if(ans.minn) puts("0");
		else printf("%d\n",ans.cnt);
	}
}