#include<bits/stdc++.h>
#define il inline
using namespace std;
il char gc()
{
    static char now[1<<20],*S,*T;
    if (T==S)
    {
        T=(S=now)+fread(now,1,1<<20,stdin);
        if (T==S) return EOF;
    }
    return *S++;
}
il int read()
{
    int res=0,sign=1;
    char c;
    while ((c=gc())<'0'||c>'9') if (c=='-') sign=-1;
    res=(c^48);
    while ((c=gc())>='0'&&c<='9') res=(res<<3)+(res<<1)+(c^48);
    return res*sign;
}

const int N=5000005;
int n,q,a[N];
int main(){
    n=read(); q=read();
    for(int i=1;i<=n;i++) a[i]=read();
    while(q--){
        int l=read(),r=read();
        int flag=0;
        for(int i=l+1;i<=r;i++){
            if(a[i]<a[i-1]){
                if(!flag) flag=1;
            }
            if(a[i]>a[i-1]){
                if(flag==1) flag=2;
            }
        }
        if(flag!=2) puts("Y");
        else puts("N");
    }
    return 0;
}