#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=200005;
const int inf=(int)5e18;
int n,a[N],sum[N],avr;
int ans=inf;

int A[5];
void calc(){
    sort(A+1,A+5);
    ans=min(ans,A[4]-A[1]);
}

signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]), sum[i]=sum[i-1]+a[i];
    for(int m=2;m<=n;m++){
        int sum1=sum[m],sum2=sum[n]-sum[m];
        int pos1=upper_bound(sum+1,sum+m+1,sum[m]/2)-sum;
        int pos2=upper_bound(sum+m+1,sum+n+1,sum2/2+sum[m])-sum;
        for(int i=0;i<=1;i++){
            for(int j=0;j<=1;j++){
                int x=pos1-i,y=pos2-j;
                if(y==m||x==0) continue;
                if(y>n||x>m) continue;
                A[1]=sum[x]; A[2]=sum[m]-sum[x];
                A[3]=sum[y]-sum[m]; A[4]=sum[n]-sum[y];
                calc();
            }
        }
    }
    cout<<ans<<endl;
}