#include <iostream>
#include<fstream>
#include<vector>
#include<string.h>
using namespace std;
ifstream f("Date.txt");
///#define lambda '~'
void citire_stari(int &n,int &n2, char &q0, char *q[], char *fi[])
{
    f>>n;
    cout<<"dim: "<<n<<"\n";
    *q=new char[n+1];
    f>>(*q);

    cout<<"Stari: "<<(*q)<<"\n";

    f>>q0>>n2;

    cout<<"dim: "<<n2<<"\n";
    *fi=new  char[n2+1];
    f>>(*fi);
    cout<<"Stari fi: "<<(*fi)<<"\n";

}

void citire_simboluri(int &m, char *s[])
{
    f>>m;
    *s=new char[m];
    f>>*s;
}

struct muchie
{
 char vecin, tranz;
};

vector<muchie>* creare_automat(char *q, char *fi, int n, int n2)
{

    vector<muchie>  *aut=new vector<muchie> [n];
    char x,y,t;

    while(f>>x>>y>>t)
    {   muchie m;
        m.vecin=y; m.tranz=t;
        int j=0;
        while(q[j]!=x)
          j++;
        aut[j].push_back(m);
    }

    return aut;
}

bool verificare_expresie(char *expr, vector<muchie> *aut, char *q, char *fi, char q0, char *s)
{
    if(expr[0]=='&'&&strchr(fi,q0))
         return 1;
    if(strlen(expr)==0)
     {
        if(strchr(fi,q0))
         return 1;
        else
         return 0;
     }
    bool ok=0;
    char c=expr[0];

    if(!strchr(s,c))
      return 0;
    int j=0;
    while(q[j]!=q0)
      j++;

    for(unsigned int i=0;i<aut[j].size();i++)
    {
        if(aut[j][i].tranz==c)
             ok=verificare_expresie(expr+1,aut,q,fi,aut[j][i].vecin, s);
        else
        if(aut[j][i].tranz=='&')
             ok=verificare_expresie(expr,aut,q,fi,aut[j][i].vecin, s);

        if(ok)
            return 1;

    }
    cout<<"Ajunge aici\n";
    return ok;
}

int main()
{  int n, n2, m;
   char q0, *q, *fi, *s;
   citire_stari(n,n2,q0,&q,&fi);
   citire_simboluri(m,&s);

   vector<muchie> *aut=creare_automat(q,fi,n,n2);
   char *cuv=new char[1000];
   cout<<"Introdu cuvantul: ";
   cin>>cuv;

   bool ok=verificare_expresie(cuv,aut,q,fi,q0,s);
   if(ok)
    cout<<"\nAcceptat\n";
   else
    cout<<"Nu poate fi modelat cu acest automat";

    return 0;
}
