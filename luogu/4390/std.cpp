#include <stdio.h>
#include <algorithm>
using namespace std;
const int N=200010;
int w,cnt,qcnt,fcnt,ans[N],c[N];
struct Node{
	int x,y,ti,pos,opt,val; 
}node[N],temp[N];
/*
 pos是询问的位置
 opt是操作种类，等于0是修改，1和-1分别代表询问应该统计正贡献或负贡献。
 val是贡献 
*/ 
int read(){
    int x=0,w=1;char ch;ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x*w;
}
bool cmp(const Node &a,const Node &b){
	if(a.x!=b.x) return a.x<b.x;
	if(a.y!=b.y) return a.y<b.y;
	if(a.ti!=b.ti) return a.ti<b.ti;//
	return a.val>b.val;//请注意这两行与三维偏序模板的不同之处qwq 
}
int lowbit(int x){
	return x&(-x);
}
void add(int x,int v){
	for(;x<=cnt;x+=lowbit(x))
	 c[x]+=v;
}
int query(int x){
	int v=0;
	for(;x;x-=lowbit(x))//如果不+1这里就死了哦qwq 
	 v+=c[x];
	return v;
}
void cdq(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1;
	cdq(l,mid);cdq(mid+1,r);
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r){
		if(node[i].y<=node[j].y){
			if(!node[i].opt)
			 add(node[i].ti,node[i].val);
			temp[k++]=node[i++];
		}
		else{
			if(node[j].opt){
				int s=query(node[j].ti);
				ans[node[j].pos]+=s*node[j].opt;
			}
			temp[k++]=node[j++];
		}
	}
	while(j<=r){
		if(node[j].opt){
			int s=query(node[j].ti);
			ans[node[j].pos]+=s*node[j].opt;
		}
		temp[k++]=node[j++];
	}
	for(int o=l;o<i;o++)
	 if(!node[o].opt)
	  add(node[o].ti,-node[o].val);
	while(i<=mid)
	 temp[k++]=node[i++];
	for(int i=l;i<=r;i++)
	 node[i]=temp[i];
}
int main()
{
	int opt,x,y,xx,yy,num,t=0;
	read();w=read()+1;
	while(1){
		opt=read();
		if(opt==1){
			x=read()+1;y=read()+1;num=read();t++;
			node[++cnt]=Node{x,y,t,0,0,num};
		}
		else if(opt==2){
			x=read(),y=read();xx=read()+1,yy=read()+1;
			node[++cnt]=Node{xx,yy,t,++qcnt,1,0};
			node[++cnt]=Node{x,yy,t,qcnt,-1,0};
			node[++cnt]=Node{xx,y,t,qcnt,-1,0};
			node[++cnt]=Node{x,y,t,qcnt,1,0};
		}
		else break;
	}
	sort(node+1,node+cnt+1,cmp);
	cdq(1,cnt);
	for(int i=1;i<=qcnt;i++)
	 printf("%d\n",ans[i]);
	return 0;
}