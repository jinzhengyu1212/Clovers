#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=132000;
const int MOD=998244353;
inline int read(){
    int x=0,f=0; char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return f==0 ? x : -x;
}
inline void write(int x){
	if(x<0) {x=~(x-1); putchar('-');}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
typedef vector<int> Poly;
void read_Poly(Poly &A,int n){
    A.resize(n);
    for(register int i=0;i<n;++i) A[i]=read();
}
void write_Poly(Poly A){
    for(register int i=0;i<(int)A.size();++i) write(A[i]),printf(" ");
    puts("");
}
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
#define mul(a,b) (ll)(a)*(b)%MOD
void ADD(int &x,int y){x+=y; if(x>=MOD) x-=MOD;}
void SUB(int &x,int y){x-=y; if(x<0) x+=MOD;}
void MUL(int &x,int y){x=1ll*x*y%MOD;}
int qpow(int x,int y){
    int ret=1;
    while(y){
        if(y&1) ret=mul(ret,x);
        x=mul(x,x);
        y>>=1;
    }
    return ret;
}
int Inv(int x){return qpow(x,MOD-2);}
int inv[N];

namespace FFT{
    int rev[N<<1],G[N<<1],IG[N<<1];
    int init(int n){
        int len=1;
        while(len<n) len<<=1;
        rev[0]=0; rev[len-1]=len-1;
        for(register int i=1;i<len-1;++i) rev[i]=(rev[i>>1]>>1)+(i&1 ? len>>1 : 0);
        for(register int i=1;i<=len;i<<=1){
            G[i]=qpow(3,(MOD-1)/i);
            IG[i]=qpow(G[i],MOD-2);
        }
        return len;
    }
    void ntt(int *a,int len,int flag){
        for(register int i=0;i<len;++i) if(i<rev[i]) swap(a[i],a[rev[i]]);
        for(register int h=1;h<len;h<<=1){
            int wn=(flag==1 ? G[h<<1] : IG[h<<1]);
            for(register int i=0;i<len;i+=(h<<1)){
                int W=1,tmp1,tmp2;
                for(register int j=i;j<i+h;++j){
                    tmp1=a[j], tmp2=mul(a[j+h],W);
                    a[j]=add(tmp1,tmp2);
                    a[j+h]=sub(tmp1,tmp2);
                    W=mul(W,wn);
                }
            }
        }
        if(flag==-1){
            int invlen=qpow(len,MOD-2);
            for(register int i=0;i<len;++i) a[i]=mul(a[i],invlen);
        }
    }
    void multi(int *a,int *b,int len)
    {
        ntt(a,len,1); ntt(b,len,1);
        for(register int i=0;i<len;++i) a[i]=mul(a[i],b[i]);
        ntt(a,len,-1);
    }
}

Poly operator + (Poly A,Poly B){
    int len=max((int)A.size(),(int)B.size());
    A.resize(len); B.resize(len);
    for(register int i=0;i<len;++i) ADD(A[i],B[i]);
    return A;
}

Poly operator - (Poly A,Poly B){
    int len=max((int)A.size(),(int)B.size());
    A.resize(len); B.resize(len);
    for(register int i=0;i<len;++i) SUB(A[i],B[i]);
    return A;
}

Poly operator * (Poly A,Poly B){
    static int a[N<<1],b[N<<1];
    int M=(int)A.size()+(int)B.size()-1;
    int len=FFT::init(M);
    A.resize(len); B.resize(len);
    for(register int i=0;i<len;++i) a[i]=A[i],b[i]=B[i];
    FFT::multi(a,b,len);
    A.resize(M);
    for(register int i=0;i<M;++i) A[i]=a[i];
    return A;
}

void reverse(Poly &A){
    for(register int i=0;i<(int)A.size()/2;++i){
        swap(A[i],A[(int)A.size()-1-i]);
    }
}

void Inverse(Poly A,Poly &B,int n){
    static int a[N<<1],b[N<<1];
    if(n==1){
        B[0]=Inv(A[0]);
        return;
    }
    int mid=(n+1)/2;
    Inverse(A,B,mid);
    int len=FFT::init(n<<1);
    for(register int i=0;i<len;++i) a[i]=b[i]=0;
    for(register int i=0;i<n;++i) a[i]=A[i];
    for(register int i=0;i<mid;++i) b[i]=B[i];
    FFT::ntt(a,len,1); FFT::ntt(b,len,1);
    for(register int i=0;i<len;++i){
        b[i]=mul(b[i],sub(2,mul(a[i],b[i])));
    }
    FFT::ntt(b,len,-1);
    for(register int i=0;i<n;++i) B[i]=b[i];
}
Poly Polynomial_Inverse(Poly A){
    Poly B; B.resize(A.size());
    Inverse(A,B,(int)A.size());
    return B;
}

Poly operator / (Poly A,Poly B){
    reverse(A); reverse(B);
    int Len=A.size()-B.size()+1;
    A.resize(Len); B.resize(Len);
    B=Polynomial_Inverse(B);
    Poly D=A*B; D.resize(Len);
    reverse(D);
    return D;
}

Poly operator % (Poly A,Poly B){
    Poly D=A/B; D=D*B;
    Poly R=A-D;
    R.resize((int)B.size()-1);
    return R;
}

Poly Integral(Poly A){//jifen
    A.resize(A.size()+1);
    for(register int i=(int)A.size()-1;i>=1;i--) A[i]=mul(inv[i],A[i-1]);
    A[0]=0;  
    return A;
}

Poly Derivate(Poly A){//qiudao
    for(register int i=0;i<(int)A.size()-1;++i) A[i]=mul(i+1,A[i+1]);
    A.resize(A.size()-1);
    return A;
}

Poly Polynomial_ln(Poly A){
    Poly AA=Derivate(A);
    A=Polynomial_Inverse(A);
    Poly B=A*AA;
    B.resize(AA.size());
    B=Integral(B);
    return B;
}

void EXP(Poly A,Poly &B,int n){
    static int a[N<<1],b[N<<1],lnb[N<<1];
    if(n==1){
        B.push_back(1);
        return;
    }
    int mid=(n+1)/2;
    EXP(A,B,mid);
    B.resize(n); Poly lnB=Polynomial_ln(B);
    int len=FFT::init(n+n);
    for(register int i=0;i<len;++i) a[i]=0,b[i]=0,lnb[i]=0;
    for(register int i=0;i<n;++i) a[i]=A[i],lnb[i]=lnB[i];//important!! "ln in MOD x^n" 
    for(register int i=0;i<mid;++i) b[i]=B[i];
    FFT::ntt(a,len,1); FFT::ntt(b,len,1); FFT::ntt(lnb,len,1);
    for(register int i=0;i<len;++i){
        b[i]=mul(b[i],sub(a[i]+1,lnb[i]));
    }
    FFT::ntt(b,len,-1);
    for(register int i=0;i<n;++i) B[i]=b[i];
}
Poly Polynomial_Exp(Poly A){
    Poly B;
    EXP(A,B,A.size());
    return B;
}

Poly Polynomial_Pow(Poly A,int k){
    A=Polynomial_ln(A);
    for(register int i=0;i<(int)A.size();++i) A[i]=mul(A[i],k);
    A=Polynomial_Exp(A);
    return A;
}

int flag=0;
Poly Generalized_Pow(Poly A,int k1,int k2){
    int t=0,sz=A.size(); while(A[t]==0) t++;
    for(register int i=t;i<sz;++i) A[i-t]=A[i];
    A.resize(sz-t); 
    int D=A[0],invD=Inv(D);
    for(register int i=0;i<(int)A.size();++i) A[i]=mul(A[i],invD);
    A=Polynomial_Pow(A,k1); 
    D=qpow(D,k2);
    for(register int i=0;i<(int)A.size();++i) A[i]=mul(A[i],D);
    if(t&&flag||1ll*t*k1>sz){
        A.resize(sz);
        for(register int i=0;i<sz;++i) A[i]=0;
        return A;
    }
    t*=k1;
    A.resize(sz); 
    for(register int i=sz-1;i>=t;i--) A[i]=A[i-t];
    for(register int i=0;i<min(t,sz);++i) A[i]=0;
    return A;
}

int w;
struct Complex{
    int x,y;
    Complex(){}
    Complex(int x,int y):x(x),y(y){}
    Complex operator * (const Complex &rhs) const{
        return Complex(add(mul(x,rhs.x),mul(w,mul(y,rhs.y))),
                    add(mul(x,rhs.y),mul(y,rhs.x)));
    }
};
int Complex_pow(Complex x,int y){
    Complex ret(1,0);
    while(y){
        if(y&1) ret=ret*x;
        x=x*x;
        y>>=1;
    }
    return ret.x;
}
int Cipolla(int n){//find x^2==n(MOD 998244353)
    srand(time(NULL));
    while('H'+'C'+'Y'+'A'+'K'+'I'+'O'+'I'){
        int a=rand()%MOD;
        w=sub(mul(a,a),n);
        if(qpow(w,(MOD-1)/2)!=1){
            int ret=Complex_pow(Complex(a,1),(MOD+1)/2);
            return min(ret,MOD-ret);
        }
    }
}

void Sqrt(Poly A,Poly &B,int n){
    static int a[N<<1],b[N<<1],invb[N<<1];
    if(n==1){
        B.push_back(Cipolla(A[0]));
        return;
    }
    int mid=(n+1)/2;
    Sqrt(A,B,mid);
    B.resize(n); Poly invB=Polynomial_Inverse(B);
    int len=FFT::init(n+n);
    for(register int i=0;i<len;++i) a[i]=b[i]=invb[i]=0;
    for(register int i=0;i<n;++i) a[i]=A[i],invb[i]=invB[i];
    for(register int i=0;i<mid;++i) b[i]=B[i];
    FFT::ntt(a,len,1); FFT::ntt(b,len,1); FFT::ntt(invb,len,1);
    for(register int i=0;i<len;++i){
        b[i]=mul(mul(inv[2],invb[i]),add(a[i],mul(b[i],b[i])));
    }
    FFT::ntt(b,len,-1);
    for(register int i=0;i<n;++i) B[i]=b[i];
}
Poly Polynomial_Sqrt(Poly A){
    Poly B;
    Sqrt(A,B,A.size());
    return B;
}

int n,k1,k2;
Poly Challenge(Poly A){
    Poly Tmp=A; Tmp.resize(A.size()+1);
    A=Polynomial_Sqrt(A);
    A=Polynomial_Inverse(A);
    A=Integral(A);
    A=Polynomial_Exp(A);
    A=Tmp-A; A[0]=1;
    A=Polynomial_ln(A); A[0]=1;
    A=Generalized_Pow(A,k1,k2);
    A=Derivate(A);
    A.resize(A.size()-1);
    return A;
}

void readk(){
    int x=0,y=0; char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9'){
        x=add(mul(10,x),ch^48);
        y=(10ll*y%(MOD-1)+(ch^48))%(MOD-1);
        ch=getchar();
        if(x!=y) flag=1;
    }
    k1=x; k2=y;
}

signed main(){
    inv[0]=1; inv[1]=1; for(register int i=2;i<N;++i) inv[i]=mul(MOD-MOD/i,inv[MOD%i]);
    n=read(); readk();
    Poly A;
    read_Poly(A,n+1);
    write_Poly(Challenge(A));
    return 0;
}