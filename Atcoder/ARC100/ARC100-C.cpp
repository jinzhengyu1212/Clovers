#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=500005;
ll n,a[N],sum=0;
ll _abs(int x){return x<0 ? -x : x;}

int main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]), a[i]-=i;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++) sum+=_abs(a[(n+1)/2]-a[i]);
    cout<<sum<<endl;
    return 0;
}