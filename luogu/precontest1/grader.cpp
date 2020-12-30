#include <string>
#include <iostream>
using namespace std;
char s[2];
string my_ans="";
int a[100];
int main() {
	string my_ans=
        "ABCBACABCBDBACD"
        "FTTTBA"
        "FFTTAA"
        "FFFTCC"
        "CDDAC"
        "CBDCB";
    string ans   ="ABCDABCDABCDABCTFTFAATFTFAATFTFAAABCDABCDAB";
	for (int i=1;i<=15;++i) a[i]=2;
	for (int i=34;i<=43;++i) a[i]=3;
	for (int i=16;i<=19;++i) a[i]=2;
	for (int i=20;i<=21;++i) a[i]=3;
	for (int i=22;i<=25;++i) a[i]=2;
	for (int i=26;i<=27;++i) a[i]=3;
	for (int i=28;i<=31;++i) a[i]=2;
	for (int i=32;i<=33;++i) a[i]=3;
	a[16]=a[17]=1; a[20]=4; a[22]=1; a[28]=1; a[32]=4;
	int tot=0;
	for (int i=1;i<=43;++i) if (my_ans[i-1]==ans[i-1]) tot+=a[i];
	printf("%d\n",tot);
    return 0;
}