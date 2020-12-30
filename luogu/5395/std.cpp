#include<cstdio>
#include<algorithm>
#include<cstring>
const int md=167772161,N=524288,g3=(md+1)/3;
typedef long long LL;
int n,lim,rev[N];
inline void upd(int&a){a+=a>>31&md;}
inline int pow(int a,int b){
    int ret=1;
    for(;b;b>>=1,a=(LL)a*a%md)if(b&1)ret=(LL)ret*a%md;
    return ret;
}
int pri[N/10],isp[N],a[N],fac[N],inv[N],tot,k,b[N],c[N],iv[N];
void init(const int n){
    a[1]=1;
    for(int i=2;i<=n;++i){
        if(!isp[i])pri[++tot]=i,a[i]=pow(i,n);
        for(int j=1;j<=tot&&i*pri[j]<=n;++j){
            isp[i*pri[j]]=1,a[i*pri[j]]=a[i]*(LL)a[pri[j]]%md;
            if(i%pri[j]==0)break;
        }
    }
}
void initFFT(int n){
    int l=-1;
    for(lim=1;lim<n;lim<<=1)++l;
    for(int i=1;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
}
void NTT(int*a,int f){
    for(int i=1;i<lim;++i)if(i<rev[i])std::swap(a[i],a[rev[i]]);
    for(int i=1;i<lim;i<<=1){
        const int gi=pow(f?3:g3,(md-1)/(i<<1));
        for(int j=0;j<lim;j+=i<<1)
        for(int k=0,g=1;k<i;++k,g=(LL)g*gi%md){
            const int x=a[j+k],y=(LL)g*a[j+k+i]%md;
            upd(a[j+k]+=y-md),upd(a[j+k+i]=x-y);
        }
    }
    if(!f){
        const int iv=pow(lim,md-2);
        for(int i=0;i<lim;++i)a[i]=(LL)a[i]*iv%md;
    }
}
int main(){
    scanf("%d",&n);
    init(n);
    initFFT(++n<<1);
    for(int i=*fac=1;i<n;++i)fac[i]=(LL)fac[i-1]*i%md;
    inv[n-1]=pow(fac[n-1],md-2);
    for(int i=n-2;~i;--i)iv[i]=inv[i]=(i+1LL)*inv[i+1]%md;
    for(int i=1;i<n;++i)a[i]=(LL)a[i]*inv[i]%md,b[i-1]=inv[i];
    for(int i=0;i<n;++i)
    if(i&1)inv[i]=md-inv[i];
    NTT(a,1),NTT(inv,1);
    for(int i=0;i<lim;++i)a[i]=(LL)a[i]*inv[i]%md;
    NTT(a,0);
    for(int i=0;i<n;++i)
    printf("%d%c",a[i]," \n"[i==n-1]);
    return 0;
}