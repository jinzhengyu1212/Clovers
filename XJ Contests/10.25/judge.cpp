#include<bits/stdc++.h>
using namespace std;
const int N=5005;
const int M=2500;
int dx[]={1,0,0,-1};
int dy[]={0,-1,1,0};
int a[N][N],bl;
int main(){
    int x,y,z;
    int tot=0;
    while(scanf("%d%d%d",&x,&y,&z)!=EOF){
        tot++;
        x+=M; y+=M; 
        int vis[5]; memset(vis,0,sizeof(vis));
        for(int i=1;i<=4;i++){
            if(z-i<=0) continue;
            int flag=0;
            for(int j=0;j<4;j++){
                int xx=x+dx[j],yy=y+dy[j];
                // if(z-a[xx][yy]<0||z-a[xx][yy]>4){
                //     cout<<tot<<endl;
                //     puts("Exceed!");
                //     return 0;
                // }
                if(a[xx][yy]+i==z) flag=1;
            }
            if(!flag){
                cout<<tot<<endl;
                puts("Wrong!");
                return 0;
            }
        }
        a[x][y]=z;
    }
    puts("Accepted!");
    return 0;
}