#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define int long long
int n,a[200005],sum[200005];
int stk[200005],top=0,add=0;
signed main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],sum[i]=sum[i-1]+a[i];
    if(n==1){
        cout<<a[1]<<endl;
        return 0;
    }
    stk[++top]=a[1];
    for(int i=2;i<=n;i++){
            
    }
    return 0;
}
