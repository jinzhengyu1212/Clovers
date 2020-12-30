#include<bits/stdc++.h>
using namespace std;
#define cs const
#define re register
#define pb push_back
#define pii pair<int,int>
#define ll long long
#define fi first
#define se second
#define bg begin
cs int RLEN=1<<20|1;
inline char gc(){
    static char ibuf[RLEN],*ib,*ob;
    (ib==ob)&&(ob=(ib=ibuf)+fread(ibuf,1,RLEN,stdin));
    return (ib==ob)?EOF:*ib++;
}
inline int read(){
    char ch=gc();
    int res=0;bool f=1;
    while(!isdigit(ch))f^=ch=='-',ch=gc();
    while(isdigit(ch))res=(res+(res<<2)<<1)+(ch^48),ch=gc();
    return f?res:-res;
}
template<class tp>inline void chemx(tp &a,tp b){a<b?a=b:0;}
template<class tp>inline void chemn(tp &a,tp b){a>b?a=b:0;}
cs int mod=998244353;
inline int add(int a,int b){return (a+=b)>=mod?(a-mod):a;}
inline int dec(int a,int b){a-=b;return a+(a>>31&mod);}
inline int mul(int a,int b){static ll r;r=1ll*a*b;return (r>=mod)?(r%mod):r;}
inline void Add(int &a,int b){(a+=b)>=mod?(a-=mod):0;}
inline void Dec(int &a,int b){a-=b,a+=a>>31&mod;}
inline void Mul(int &a,int b){static ll r;r=1ll*a*b;a=(r>=mod)?(r%mod):r;}
inline int ksm(int a,int b,int res=1){for(;b;b>>=1,Mul(a,a))(b&1)&&(Mul(res,a),1);return res;}
inline int Inv(int x){return ksm(x,mod-2);}
inline int fix(int x){return (x<0)?x+mod:x;}
cs int N=500005;
int fac[N],ifac[N],iv[N];
inline void init_inv(cs int len=N-5){
	iv[0]=iv[1]=fac[0]=ifac[0]=1;
	for(int i=1;i<=len;i++)fac[i]=mul(fac[i-1],i);
	ifac[len]=Inv(fac[len]);
	for(int i=len-1;i;i--)ifac[i]=mul(ifac[i+1],i+1);
	for(int i=2;i<=len;i++)iv[i]=mul(mod-mod/i,iv[mod%i]);
}
typedef vector<int> poly;
namespace Poly{
	cs int G=3,C=21,M=(1<<C)+1;
	int *w[C+1];
	int rev[M];
	inline void init_rev(int lim){
		for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)*(lim>>1));
	}
	inline void init_w(){
		for(int i=1;i<=C;i++)w[i]=new int[(1<<(i-1))+1];
		int wn=ksm(G,(mod-1)/(1<<C));w[C][0]=1;
		for(int i=1,l=1<<(C-1);i<l;i++)w[C][i]=mul(w[C][i-1],wn);
		for(int j=C-1;j;j--)
		for(int i=0;i<(1<<(j-1));i++)w[j][i]=w[j+1][i<<1];
	}
	inline void ntt(int *f,int lim,int kd){
		for(int i=0;i<lim;i++)if(i>rev[i])swap(f[i],f[rev[i]]);
		for(int mid=1,l=1,a0,a1;mid<lim;mid<<=1,l++)
		for(int i=0;i<lim;i+=mid<<1)
		for(int j=0;j<mid;j++)
		a0=f[i+j],a1=mul(f[i+j+mid],w[l][j]),f[i+j]=add(a0,a1),f[i+j+mid]=dec(a0,a1);
		if(kd==-1){
			reverse(f+1,f+lim);
			for(int i=0,iv=Inv(lim);i<lim;i++)Mul(f[i],iv);
		}
	}
	inline poly operator *(poly a,poly b){
		int deg=a.size()+b.size()-1;
		if(deg<=32){
			poly c(deg,0);
			for(int i=0;i<a.size();i++)
			for(int j=0;j<b.size();j++)
			Add(c[i+j],mul(a[i],b[j]));
			return c;
		}
		int lim=1;
		while(lim<deg)lim<<=1;
		init_rev(lim);
		a.resize(lim),ntt(&a[0],lim,1);
		b.resize(lim),ntt(&b[0],lim,1);
		for(int i=0;i<lim;i++)Mul(a[i],b[i]);
		ntt(&a[0],lim,-1),a.resize(deg);
		return a;
	}
	inline poly Inv(poly a,int deg){
		poly b(1,::Inv(a[0])),c;
		for(int lim=4;lim<(deg<<2);lim<<=1){
			init_rev(lim);
			c.resize(lim>>1);
			for(int i=0;i<(lim>>1);i++)c[i]=(i<a.size()?a[i]:0);
			c.resize(lim),ntt(&c[0],lim,1);
			b.resize(lim),ntt(&b[0],lim,1);
			for(int i=0;i<lim;i++)Mul(b[i],dec(2,mul(b[i],c[i])));
			ntt(&b[0],lim,-1),b.resize(lim>>1);
		}
		b.resize(deg);return b;
	}
	inline poly deriv(poly a){
		for(int i=0;i<(int)a.size()-1;i++)a[i]=mul(a[i+1],i+1);a.pop_back();
		return a;
	}
	inline poly integ(poly a){
		a.pb(0);
		for(int i=a.size()-1;i;i--)a[i]=mul(a[i-1],iv[i]);
		a[0]=0;return a;
	}
	inline poly Ln(poly a,int deg){
		a=integ(deriv(a)*Inv(a,deg)),a.resize(deg);return a;
	}
	inline poly Exp(poly a,int deg){
		poly b(1,1),c;
		for(int lim=2;lim<(deg<<1);lim<<=1){
			c=Ln(b,lim);
			for(int i=0;i<lim;i++)c[i]=dec(i<a.size()?a[i]:0,c[i]);
			Add(c[0],1),b=b*c,b.resize(lim);
		}b.resize(deg);return b;
	}
} 
using namespace Poly;
int k,m;
poly e,ek,f,g;
int main(){
	k=read(),m=read();
	init_w(),init_inv();
	e.resize(m+1),ek.resize(m+1),f.resize(m+1);
	for(int i=0,mt=k+1;i<=m;i++,Mul(mt,k+1))e[i]=ifac[i+1],ek[i]=mul(ifac[i+1],mt);
	g=ek*Inv(e,m+1);
    for(int i=1;i<=m;i++) cout<<mul(g[i],fac[i])<<" "; cout<<endl;
	for(int i=1;i<=m;i++){
		f[i]=mul(g[i],fac[i-1]);
		if(!(i&1))f[i]=dec(0,f[i]);
	}
	f=Exp(f,m+1);
	for(int i=1;i<=m;i++)cout<<mul(fac[i],f[i])<<'\n';
}
