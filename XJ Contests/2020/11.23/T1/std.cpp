#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

#define fo(i,j,l) for(int i=j;i<=l;i++)
#define fd(i,j,l) for(int i=j;i>=l;i--)
#define mm 'M'
#define xx 'X'
#define nn 'N'


using namespace std;
typedef long long ll;
const ll N=802,P=8,M=51e4;
int n,m,j,k,l,i,o,qq;
int a[N][N],q[N][N],f[N][N][P][P],xw[M][4],ans[M],m2[10],bl[N];
int d1[2*P],d2[2*P];
char c[M];

int read()
{
    int a=0; char ch=' ';
    for(;ch<'0'||ch>'9';)ch=getchar();
    for(;ch>='0'&&ch<='9';ch=getchar())a=a*10+ch-48;
    return a;
}

int min(int a,int b)
{if(a<b)return a;else return b;}
int max(int a,int b)
{if(a>b)return a;else return b;}

void pri(int o)
{if(!o)return; pri(o/10); putchar('0'+o%10);}
void write(int o)
{
    if(o>0)pri(o);else putchar('0'); 
    putchar('\n');
}

int main()
{
    cin>>n>>m;
    fo(i,1,n)fo(l,1,m)a[i][l]=read(),q[i][l]=q[i][l-1]+a[i][l];
    fo(i,1,n)fo(l,1,m)q[i][l]+=q[i-1][l];
    m2[0]=1; fo(i,1,9)m2[i]=m2[i-1]*2;
    for(int k=0,i=1;i<=max(n,m);i++){
        bl[i]=k;
        if(i==m2[k]*2)k=min(k+1,P-1);
    }
    fo(i,1,n){
        fo(l,1,m)f[i][l][0][0]=a[i][l];
        fo(j,1,bl[m])
        fo(l,1,m-m2[j]+1)
        f[i][l][0][j]=min(f[i][l][0][j-1],f[i][l+m2[j-1]][0][j-1]);
    }
    fo(j,1,bl[n])
    fo(i,1,n-m2[j]+1)
    fo(k,0,bl[m])
    fo(l,1,m-m2[k]+1)
    f[i][l][j][k]=min(f[i][l][j-1][k],f[i+m2[j-1]][l][j-1][k]);
    cin>>qq;
    fo(i,1,qq){
        for(c[i]='\n';c[i]=='\n';)c[i]=getchar();
        c[i]=getchar(); c[i]=getchar();
        xw[i][0]=read()+1,xw[i][1]=read()+1;
        xw[i][2]=read()+1,xw[i][3]=read()+1;
        if(c[i]==mm){
            int x1=xw[i][0]-1,x2=xw[i][2],y1=xw[i][1]-1,y2=xw[i][3];
            ans[i]=q[x2][y2]-q[x2][y1]-q[x1][y2]+q[x1][y1];
        }
        if(c[i]==nn)
        {
            ans[i]=q[n][m];
            int x1=xw[i][0],x2=xw[i][2],y1=xw[i][1],y2=xw[i][3];
            int r1=1,r2=1,o1=bl[x2-x1+1],o2=bl[y2-y1+1];
            for(d1[1]=x1;d1[r1]+m2[o1]-1<x2;r1++)d1[r1+1]=d1[r1]+m2[o1];
            d1[r1]=x2-m2[o1]+1;
            for(d2[1]=y1;d2[r2]+m2[o2]-1<y2;r2++)d2[r2+1]=d2[r2]+m2[o2];
            d2[r2]=y2-m2[o2]+1;
            fo(l,1,r1)fo(j,1,r2)
            ans[i]=min(ans[i],f[d1[l]][d2[j]][o1][o2]);
        }
    }
    fo(i,1,n){
        fo(l,1,m)f[i][l][0][0]=a[i][l];
        fo(j,1,bl[m])
        fo(l,1,m-m2[j]+1)
        f[i][l][0][j]=max(f[i][l][0][j-1],f[i][l+m2[j-1]][0][j-1]);
    }
    fo(j,1,bl[n])
    fo(i,1,n-m2[j]+1)
    fo(k,0,bl[m])
    fo(l,1,m-m2[k]+1)
    f[i][l][j][k]=max(f[i][l][j-1][k],f[i+m2[j-1]][l][j-1][k]);
    fo(i,1,qq)if(c[i]==xx)
    {
        ans[i]=0;
        int x1=xw[i][0],x2=xw[i][2],y1=xw[i][1],y2=xw[i][3];
        int r1=1,r2=1,o1=bl[x2-x1+1],o2=bl[y2-y1+1];
        for(d1[1]=x1;d1[r1]+m2[o1]-1<x2;r1++)d1[r1+1]=d1[r1]+m2[o1];
        d1[r1]=x2-m2[o1]+1;
        for(d2[1]=y1;d2[r2]+m2[o2]-1<y2;r2++)d2[r2+1]=d2[r2]+m2[o2];
        d2[r2]=y2-m2[o2]+1;
        fo(l,1,r1)fo(j,1,r2)
        ans[i]=max(ans[i],f[d1[l]][d2[j]][o1][o2]);
    }
    fo(i,1,qq)write(ans[i]);
}