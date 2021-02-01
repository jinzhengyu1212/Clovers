#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
const int M=1e6+100;
long long  tr[M],ls[M],rs[M],m[M];//m记录区间最大值，ls,rs记录区间从左数多少个相同，rs右数，tr记录原数列
 void pushup(int i,int l,int r)
 {
     int mid=l+r>>1;
     ls[i]=ls[i*2];
     rs[i]=rs[i*2+1];
     if(ls[i]==mid-l+1)
     {
         if(tr[mid]==tr[mid+1])
            ls[i]+=ls[i*2+1];
     }
     if(rs[i]==r-mid)
     {
         if(tr[mid]==tr[mid+1])
            rs[i]+=rs[i*2];
     }
     m[i]=max(m[i*2],m[i*2+1]);
      if(tr[mid]==tr[mid+1])
        m[i]=max(m[i],ls[i*2+1]+rs[i*2]);
 }
 void build(int i,int l,int r)
 {
     if(l==r)
     {
         scanf("%lld",&tr[l]);
         ls[i]=rs[i]=m[i]=1;
         return;
     }
      int mid=(l+r)>>1;
    build(i*2,l,mid);
    build(i*2+1,mid+1,r);
    pushup(i,l,r);
 }
 void update(int i,int l,int r,int x,long long  t)
 {
     if(l==r)
    {
        tr[l]=t;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid)update(i*2,l,mid,x,t);
    else update(i*2+1,mid+1,r,x,t);
    pushup(i,l,r);
 }
 int query(int i,int l,int r,int x,int y)
 {
      if(l>=x&&r<=y)
    {
        return m[i];
    }
    int mid=l+r>>1;
//注意下列操作，对于相邻两区间进行的维护。
     int sum1=0,sum2=0;
    if(mid>=x) sum1=query(i*2,l,mid,x,y);
    if(mid<y) sum2=query(i*2+1,mid+1,r,x,y);
    if(sum1==0) return sum2;
    if(sum2==0) return sum1;
    int l1=min(mid-x+1,(int)rs[i*2]);
    int r1=min(y-mid,(int)ls[i*2+1]);
    if(tr[mid+1]==tr[mid]) return max(sum1,max(sum2,l1+r1));
    else return max(sum1,sum2);
 }
int main()
{
    int t,n,m,o;
    long long  x,y;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        build(1,1,n);
        while(m--)
        {
            scanf("%d%lld%lld",&o,&x,&y);
            if(o==1)
            {
                update(1,1,n,(int)x,y);
            }
            else
            {
                printf("%d\n",query(1,1,n,(int)x,(int)y));
            }
        }
    }
    return 0;
}