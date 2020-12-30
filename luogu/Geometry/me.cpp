/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const double inf=1e9;
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=200005;
double sqr(double x){return x*x;}
struct Point{
    double x,y;
    Point(){}
    Point(double x,double y):x(x),y(y){}
    void read(){scanf("%lf%lf",&x,&y);}
    void print(){printf("%.3lf %.3lf\n",x,y);}
};
typedef Point Vector;
typedef vector<Point> arrP;
typedef vector<Vector> arrV;
const double eps=1e-10;
const double pi=acos(-1);
int sgn(double x){return fabs(x)<=eps ? 0 : (x<0 ? -1 : 1);}
int comp(double x,double y){return sgn(x-y);}
bool Less(double x,double y){return comp(x,y)==-1;}
bool Equal(double x,double y){return comp(x,y)==0;}
bool Bigger(double x,double y){return comp(x,y)==1;}
bool operator == (Point A,Point B){return !comp(A.x,B.x)&&!comp(A.y,B.y);}
bool operator != (Point A,Point B){return !(A==B);}
Point operator + (Point A,Point B){return Point(A.x+B.x,A.y+B.y);}
Point operator - (Point A,Point B){return Point(A.x-B.x,A.y-B.y);}
Point operator / (Point A,double d){return Point(A.x/d,A.y/d);}
Point operator * (Point A,double d){return Point(A.x*d,A.y*d);}
double operator ^ (Point A,Point B){return A.x*B.x+A.y*B.y;}
double operator * (Point A,Point B){return A.x*B.y-B.x*A.y;}
double Area(Point A,Point B,Point C){return (B-A)*(C-A);}
double Length(Vector A){return sqrt(sqr(A.x)+sqr(A.y));}
double dist(Point A,Point B){return Length(A-B);}
Vector rotate(Vector A,double rad){
    double rad1=atan(A.y/A.x);
    return Vector(Length(A)*cos(rad1+rad),Length(A)*sin(rad1+rad));
}
bool cmpx(Point A,Point B){return Equal(A.x,B.x) ? Less(A.y,B.y) : Less(A.x,B.x);}
bool cmpy(Point A,Point B){return Equal(A.y,B.y) ? Less(A.x,B.x) : Less(A.y,B.y);}
struct Circle{
    Point P; double r;
    Circle(){}
    Circle(Point P,double r):P(P),r(r){}
};
bool outCir(Point A,Circle C){return Bigger(dist(A,C.P),C.r);}
bool inCir(Point A,Circle C){return Less(dist(A,C.P),C.r);}
bool onCir(Point A,Circle C){return Equal(dist(A,C.P),C.r);}
struct Line{
    Point P; Vector v;
    Line(){}
    Line(Point P,Vector v):P(P),v(v){}
};
bool cmprad(Line A,Line B){return Less(atan2(A.v.y,A.v.x),atan2(B.v.y,B.v.x));}
bool Parellel(Line A,Line B){return !sgn(A.v*B.v);}
bool Vertical(Line A,Line B){return !sgn(A.v^B.v);}
typedef vector<Line> arrL;
Point Line_Intersection(Line A,Line B){
    double t=((B.P-A.P)*B.v)/(A.v*B.v);
    return A.P+A.v*t;
}
Circle make_Circle(Point A,Point B,Point C){
    if((A+B)/2.0==C) return Circle(C,dist(A,C)); 
    if((A+C)/2.0==B) return Circle(B,dist(A,B)); 
    if((B+C)/2.0==A) return Circle(A,dist(A,B));
    Point Mid1((A+B)/2.0);
    Point Mid2((A+C)/2.0);
    Line L1=Line(Mid1,rotate(A-B,pi/2));
    Line L2=Line(Mid2,rotate(A-C,pi/2));
    Point P=Line_Intersection(L1,L2);
    double R=dist(P,A);
    return Circle(P,R);
}
Circle Min_Circle_Cover(Point *a,int n){
    random_shuffle(a+1,a+n+1);
    Circle C=Circle(a[1],0.0);
    for(int i=2;i<=n;i++) if(outCir(a[i],C)){
        C=Circle(a[i],0.0);
        for(int j=1;j<i;j++) if(outCir(a[j],C)){
            C=Circle((a[j]+a[i])/2.0,dist(a[j],a[i])/2.0);
            for(int k=1;k<j;k++) if(outCir(a[k],C)) 
                C=make_Circle(a[i],a[j],a[k]);
        }
    }
    return C;
}
arrP Convex2(Point *a,int n){
    arrP ret1,ret2;
    sort(a+1,a+n+1,cmpx);
    ret1.push_back(a[1]); int top=0;
    for(int i=2;i<=n;i++){
        while(top>0&&sgn((ret1[top]-ret1[top-1])*(a[i]-ret1[top]))==1) 
            ret1.pop_back(),top--;
        top++; ret1.push_back(a[i]);
    } top=0;
    ret2.push_back(a[n]);
    for(int i=n-1;i>=1;i--){
        while(top>0&&sgn((ret2[top]-ret2[top-1])*(a[i]-ret2[top]))==1)
            ret2.pop_back(),top--;
        top++; ret2.push_back(a[i]);
    }
    ret2.pop_back(); reverse(ret2.begin(),ret2.end()); ret2.pop_back();
    while(!ret2.empty()) ret1.push_back(ret2.back()),ret2.pop_back();
    return ret1;
}
double Point_Area(arrP &a){
    if(a.empty()) return 0;
    double ret=0;
    for(int i=0;i<sz(a);i++){
        int j=(i+1)%sz(a);
        ret+=a[i]*a[j];
    }
    return ret/2.0;
}
namespace Half_Plane{
    Line q[N]; Point Cross[N]; int st=0,ed=0;
    arrP main(Line *v,int n){
        sort(v+1,v+n+1,cmprad);
        st=ed=1; q[1]=v[1];
        for(int i=2;i<=n;i++){
            while(st<ed&&sgn(v[i].v*(Cross[ed-1]-v[i].P))==-1) ed--;
            while(st<ed&&sgn(v[i].v*(Cross[st]-v[i].P))==-1) st++;
            q[++ed]=v[i]; 
            if(Parellel(q[ed],q[ed-1])){
                ed--; 
                if(sgn(q[ed].v*(v[i].P-q[ed].P))==1) q[ed]=v[i];
            }
            if(st<ed) Cross[ed-1]=Line_Intersection(q[ed],q[ed-1]);
        }
        while(st<ed&&sgn(q[st].v*(Cross[ed-1]-q[st].P))==-1) ed--;//the last may not alive
        arrP ret; ret.clear();
        if(ed-st<=1) return ret; 
        Cross[ed]=Line_Intersection(q[st],q[ed]);
        for(int i=st;i<=ed;i++) ret.push_back(Cross[i]);
        return ret;
    }
}

Line a[N];
int main()
{
    arrP P; 
    int n=read(),cnt=0; 
    for(int i=1;i<=n;i++){
        int m=read(); P.resize(m);
        for(int j=0;j<m;j++){
            P[j].read();
            if(j) a[++cnt]=Line(P[j-1],P[j]-P[j-1]);
        }
        a[++cnt]=Line(P[m-1],P[0]-P[m-1]);
    }
    arrP ans=Half_Plane::main(a,cnt);
    printf("%.3lf\n",Point_Area(ans));
    return 0;
}