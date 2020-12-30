#include<iostream>
#include<cstdio>
#include<algorithm>
#pragma GCC optimize(3)
#include<cstring>
#include<ctime>

#define fo(i,j,l) for(int i=j;i<=l;i++)
#define fd(i,j,l) for(int i=j;i>=l;i--)
#define random(x) rand()%(x)

using namespace std;
typedef unsigned long long ll;
const ll N=100,mo=998244353;
ll x[N],oo,ss[N],cs[N],n,m;
int t; ll ans;

ll mod(ll x,ll y,ll m)
{
    ll tmp=(ll)((long double)x*y/m+1e-8)*m;
    return (x*y-tmp+m)%m;
}

ll ksm(ll o,ll t,ll m)
{
    ll y=1; o%=m; t=t%(m-1);
    for(;t;t>>=1,o=mod(o,o,m))
    if(t&1)y=mod(y,o,m);
    return y;
}

bool Miller_Rabin(ll o)
{
    if(!(o&1))return false;
    int y=0; ll u=o-1;
    for(;!(u&1);y++)u>>=1;
    fo(i,1,3){
        x[0]=rand()%(o-1)+1;
        x[0]=ksm(x[0],u,o);
        fo(l,1,y){
            x[l]=mod(x[l-1],x[l-1],o);
            if(x[l]==1&&x[l-1]!=1&&x[l-1]!=(o-1))return false;
        }
        if(x[y]!=1)return false;
    } return true;
}

ll iabs(ll o)
{return o<0?(-o):o;}

ll gcd(ll a,ll b)
{return b==0?a:gcd(b,a%b);}

void find(ll o)
{
    if(o==1)return;
    if(Miller_Rabin(o)){
        ss[++oo]=o; return;
    }
    ll c=random(o-1)+1,P=0;
    ll x2=random(o),x1=x2;int i=1,k=2;
    while(1){
        i++;
        x1=(mod(x1,x1,o)+c)%o;
        P=gcd(iabs(x2-x1),o);
        if(P>1&&P<o)break;
        if(x1==x2)x1=x2=random(o),c=random(o-1)+1;
        if(i==k)k<<=1,x2=x1;
    }
     find(P); find(o/P);
}

void dg(int o,ll k)
{
    if(o==oo+1){
        ll uu=n/k,y1=ksm(m%(mo),k,mo),y2=gcd(uu,m)%mo;
        ll yy=mod(y1,y2,mo),phi=uu;
        fo(i,1,oo)
        if(uu%ss[i]==0)phi=(phi/ss[i])*(ss[i]-1);
        ans=(ans+mod(phi%mo,yy,mo))%mo;
        return;
    }
    ll yy=1;
    for(int i=0;i<=cs[o];i++,yy*=ss[o])dg(o+1,k*yy);
}
int a3[]={0,0,2,4,5,7,10,12};
int a4[]={0,0,4,7,16,24,41,58};
int a5[]={0,0,4,13,34,77,148,265};
int a6[]={0,0,8,32,113,301,730,1504};
int a7[]={0,0,9,66,325,1179,3441,8578};

int main()
{
    srand(23333);
    cin>>t;
    fo(tt,1,t){     
        scanf("%lld%lld",&n,&m);
        oo=0; ll nn=n;
        while(!(nn&1))nn>>=1,ss[++oo]=2; find(nn); sort(ss+1,ss+oo+1);
        int yy=0; ss[0]=0;
        fo(i,1,oo)if(ss[i]==ss[i-1])cs[yy]++;else ss[++yy]=ss[i],cs[yy]=1;
        oo=yy;
        ans=0; nn=n%mo; ll mm=m%mo;
        if(n%2==1)ans=mod(nn,ksm(mm,n/2+1,mo),mo);else {
            ans=mod((n/2)%mo,ksm(mm,n/2+1,mo),mo);
            ans=(ans+mod((n/2)%mo,ksm(mm,n/2,mo),mo)*(1+(m%2==0)))%mo; 
        }
        dg(1,1);
        ans=ans*ksm(2*mod(nn,mm,mo)%mo,mo-2,mo)%mo;
        printf("%lld\n",ans); 
        if(n==3) printf("%d\n",a3[m]);
        else if(n==4) printf("%d\n",a4[m]);
        else if(n==5) printf("%d\n",a5[m]);
        else if(n==6) printf("%d\n",a6[m]);
        else printf("%d\n",a7[m]);
    }
}