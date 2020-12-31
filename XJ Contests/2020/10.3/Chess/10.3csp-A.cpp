#include<bits/stdc++.h>
using namespace std;
const int N=201;

int n,xx,AA,BB,CC;
int getid(){return xx=(1ll*xx*AA+BB)%CC;}
struct Chess
{
    int attack,Hp;
    char race[2],feature[2];
};
vector<Chess> used_S,used_R,S,R;
int ansS=0,ansR=0;
bool end_game(){return S.empty()||R.empty();}
void calc_result(){
    ansS+=(int)S.size();
    ansR+=(int)R.size();
}
void readygame(){
    S.clear(); R.clear();
    S=used_S; R=used_R;
}

void Leader(vector<Chess> &V){
    for(int i=0;i<(int)V.size();i++) if(V[i].feature[0]=='L') {
        for(int j=0;j<(int)V.size();j++) 
            if(j!=i&&V[j].race[0]=='M') V[j].attack+=20;
    }
}
void dead_Leader(vector<Chess> &V){
    for(int i=0;i<(int)V.size();i++) {
        if(V[i].race[0]=='M') V[i].attack-=20;
    }
}
void dead_King(vector<Chess> &V,int id){
    for(int i=0;i<(int)V.size();i++) if(V[i].race[0]=='M'&&i!=id) {
        V[i].Hp+=20;
        V[i].attack+=20;
    }
}
void attack_Captain(vector<Chess> &V,int id){
    for(int i=0;i<(int)V.size();i++) if(i!=id) {
        if(V[i].feature[0]=='C') V[id].attack+=20, V[id].Hp+=20;
    }
}
void dead_Ghost(vector<Chess> &V){
    for(int i=0;i<(int)V.size();i++){
        if(V[i].feature[0]=='G') V[i].attack+=50;
    }
}

void recycle(vector<Chess> &V){
    vector<Chess> tmp;
    for(int i=0;i<(int)V.size();i++){
        Chess u=V[i];
        if(u.Hp<=0){
            if(u.feature[0]=='K') dead_King(V,i);
            if(u.race[0]=='P') dead_Ghost(V);
            if(u.feature[0]=='L') dead_Leader(V);
        }
    }
    for(int i=0;i<(int)V.size();i++){
        Chess u=V[i];
        if(u.Hp>0) tmp.push_back(u);
    }
    V.clear();
    for(int i=0;i<(int)tmp.size();i++){
        V.push_back(tmp[i]);
    }
}

bool Play_Round(){
    int nS=(int)S.size(),nR=(int)R.size();
    int x=getid()%nS, y=getid()%nR;
    if(S[x].race[0]=='P') attack_Captain(S,x);
    if(R[y].race[0]=='P') attack_Captain(R,y);
    S[x].Hp-=R[y].attack; R[y].Hp-=S[x].attack;
    recycle(S); recycle(R);
    if(end_game()){calc_result(); return 0;}
    else return 1;
}

void init(){
    scanf("%d%d%d%d%d",&n,&xx,&AA,&BB,&CC);
    for(int i=1;i<=n+n;i++){
        Chess tmp;
        scanf("%d%d",&tmp.attack,&tmp.Hp);
        scanf("%s",tmp.race); scanf("%s",tmp.feature);
        if(i<=n) used_S.push_back(tmp);
        else used_R.push_back(tmp);
    }
}

void solve(){
    for(int i=1;i<=500;i++){
        readygame();
        Leader(S); Leader(R);
        while(Play_Round());
    }
    printf("%d %d\n",ansS,ansR);
}

int main(){
    init();
    solve();
    return 0;
}