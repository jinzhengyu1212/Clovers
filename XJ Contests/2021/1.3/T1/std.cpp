#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const ll N=1e5+10;
struct LineJ{
    ll d[80];
    void Insert(ll x){
        for(ll i=60;i>=0;i--)
            if((x>>i)&1){
                if(d[i])x^=d[i];
                else{
                    d[i]=x;
                    break;
                }
            }
        return;
    }
    ll get_max(ll x){
        for(ll i=60;i>=0;i--)
            if((x^d[i])>x)
                x^=d[i];
        return x;
    }
    ll get_min(ll x){
        for(ll i=60;i>=0;i--)
            if((x^d[i])<x)
                x^=d[i];
        return x;
    }
}suf[N],now,tmp;
ll n,op,a[N],ans;
void Merge(LineJ &x,LineJ &y){
    tmp=x;
    for(ll i=0;i<=60;i++)
        if(y.d[i])tmp.Insert(y.d[i]);
    return;
}
int main()
{
    scanf("%lld%lld",&op,&n);;
    for(ll i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    for(ll i=n;i>=1;i--){
        suf[i]=suf[i+1];
        suf[i].Insert(a[i]);
    }
    for(ll i=1;i<=n;i++){
        Merge(suf[i+1],now);
        ll k;
        if(op)ans+=(k=tmp.get_max(a[i]));
        else ans+=(k=tmp.get_min(a[i]));
        now.Insert(k);
    }
    printf("%lld\n",ans);
}