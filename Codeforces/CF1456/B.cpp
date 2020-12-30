#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=100005;
int a[N],sum[N],n,ans=1000000000;

int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read(),sum[i]=sum[i-1]^a[i];
    if(n>=200){
        puts("1");
        return 0;
    }
    for(int i=1;i<n;i++){
        for(int j=i-1;j>=0;j--){
            for(int k=i+1;k<=n;k++){
                if((sum[i]^sum[j])>(sum[k]^sum[i])){
                    ans=min(ans,k-j-2);
                }
            }
        }
    }
    if(ans>n) puts("-1");
    else printf("%d\n",ans);
    return 0;
}