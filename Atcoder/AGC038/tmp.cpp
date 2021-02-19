#include <bits/stdc++.h>
using namespace std;
#define fp(i,l,r) for(register int (i)=(l);(i)<=(r);++(i))
#define fd(i,l,r) for(register int (i)=(l);(i)>=(r);--(i))
#define fe(i,u) for(register int (i)=front[(u)];(i);(i)=e[(i)].next)
#define mem(a) memset((a),0,sizeof (a))
#define O(x) cerr<<#x<<':'<<x<<endl
#define ll long long
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return x;
}
void wr(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)wr(x/10);
	putchar('0'+x%10);
}
const int MAXN=5e4+10,mod=1e9+7;
struct node{
	int a[1024],tot;
}s[MAXN];
int n,m,S,A[12][MAXN],len,id[MAXN];
char ss[MAXN];
string opt="";
node num[MAXN]; int top=0;
inline node calc(const node &a,const node &b,char op){
	node res;
	if(op=='<'){
		fp(i,0,S)res.a[i]=1ll*a.a[i]*b.a[i]%mod;
		res.tot=1ll*a.tot*b.tot%mod;
	}
	else if(op=='>'){
		ll t=1ll*a.tot*b.tot%mod;
		fp(i,0,S)res.a[i]=(t-1ll*(a.tot-a.a[i])*(b.tot-b.a[i]))%mod;
		res.tot=t;
	}
	else{
		fp(i,0,S)res.a[i]=(1ll*a.tot*b.a[i]+1ll*b.tot*a.a[i])%mod;
		res.tot=2ll*a.tot*b.tot%mod;
	}
	return res;
}
int Y;
inline bool cmp(int q1,int q2){return A[q1][Y]>A[q2][Y];}
inline void doit(){
	while(opt!=""&&opt.back()!='('){
		char ch=opt.back();opt.pop_back();
		node num1=num[top--];
		node num2=num[top--];
		num[++top]=calc(num1,num2,ch);
	}
}
main(){
	n=read();m=read();S=(1<<m)-1;
	fp(i,0,m-1)fp(j,1,n)A[i][j]=read();
	fp(i,0,m-1)fp(j,0,S)s[i].a[j]=j>>i&1;
	fp(i,0,m-1)s[i].tot=1;
	scanf("%s",ss+1);len=strlen(ss+1);
	fp(i,1,len){
		char ch=ss[i];
		if(isdigit(ch)){
			num[++top]=s[ch-'0'];doit();
		}
		else if(ch==')')opt.pop_back(),doit();
		else opt.push_back(ch);
	}
	node p=num[top];
	ll res=0;
	fp(i,0,m-1)id[i]=i;
	fp(kk,1,n){
		Y=kk;
		sort(id,id+m,cmp);
		int t=0;ll os=0;
		fp(i,0,m-1)if(p.a[t|=1<<id[i]]){
			res=(res+1ll*(p.a[t]-os)*A[id[i]][Y])%mod;
			os=p.a[t];
		}
	}
	printf("%lld\n",(res%mod+mod)%mod);
	return 0;
}