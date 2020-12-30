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
int n,q,a[N],nxt[N],pre[N];
int main(){
    n=read(); q=read();
    for(int i=1;i<=n;i++) a[i]=read();
    pre[1]=1;
    for(int i=2;i<=n;i++){
        pre[i]=(a[i]<=a[i-1] ? pre[i-1] : i);
    }
    nxt[n]=n;
    for(int i=n-1;i>=1;i--){
        nxt[i]=(a[i]<=a[i+1] ? nxt[i+1] : i);
    }
    int l,r,pos1,pos2;
    while(q--){
        l=read(); r=read();
        pos1=nxt[l]; pos2=pre[r];
        if(pos1>=pos2) puts("Y");
        else puts("N");
    }
    return 0;
}