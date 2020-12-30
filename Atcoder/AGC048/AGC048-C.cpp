#include<bits/stdc++.h>
using namespace std;
const long long inf=(long long)5e18;
const int N=500005;
int n,L,a[N],b[N],A[N],B[N];
int f(int x){return x<0 ? 0 : x;}

int main(){
    scanf("%d%d",&n,&L);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    a[n+1]=L+1,b[n+1]=L+1;
    for(int i=1;i<=n+1;i++){
        A[i]=a[i]-a[i-1]-1;
        B[i]=b[i]-b[i-1]-1;
    }
    long long ans=0;
    for(int i=1,j=1;i<=n+1;i++){
        if(!B[i]) continue;
        while(A[j]==0) j++;
        int sum=0; int from=j;
        while(sum+A[j]<B[i]&&j<=n+1) sum+=A[j++];
        if(sum+A[j]==B[i]) sum+=A[j++];
        else {puts("-1"); return 0;}
        int to=j-1;
        ans+=f(i-from)+f(to-i);
    }
    cout<<ans<<endl;
    return 0;
}