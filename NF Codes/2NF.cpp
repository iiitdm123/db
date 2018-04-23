#include<iostream>
using namespace std;
const int N=5;
const int F=3;
int r=0;
class reln
{
    int a[N];
    int n;
    int f;
    int fd[F][N];

public:
    void init();
    void disp();
    void nf2(reln x[]);
    void disp2(reln x[]);
};
void reln::init()
{
    cout<<"\nInitialize\n---------------\n";
    int c[]={1, 1, -1, -1, -1};
    int cp[][N]={{1, 1, -1, 0, 0}, {0, 1, 0, -1, 0}, {0, 1, 0, 0, -1} };
    n=N;
    f=F;

    for(int i=0; i<n; i++)
    {
        a[i]=c[i];
    }
    for(int i=0; i<f; i++)
    {
        for(int j=0; j<n; j++)
        {
            fd[i][j]=cp[i][j];
        }

    }
}
void reln::disp()
{
    cout<<"\ndisp\n---------------\n";
    for(int i=0; i<f; i++)
    {
        for(int j=0; j<n;j++)
        {
            cout<<fd[i][j]<<"\t";//=cp[i][j];
        }
        cout<<endl;
    }

    for(int i=0; i<n; i++)
        cout<<a[i]<<"\t";
}
void reln::nf2(reln x[])
{
    cout<<"\nnf2\n---------------\n";


    for(int i=0; i<f; i++)
    {
        cout<<"fd scan\n";
        int pfd=1;
        int ppfd=0;
        int non_empty=0;
        for(int j=0; j<n; j++)
        {
            if((fd[i][j]==1)&&(a[j]!=1))
            {
                pfd=0;
                break;
            }
            if((a[j]==1)&&(fd[i][j]!=1))
                ppfd=1;
            if(fd[i][j]!=0)
                non_empty=1;
        }
            if(pfd*ppfd*non_empty==1)
            {
                //str_i=i;
                //create new reln
                cout<<"found pfd: i=\n"<<i<<endl;
                r++;
                x[r].n=n;

                for(int k=0; k<n; k++)
                {
                    x[r].a[k]=fd[i][k];
                }   //if(fd[i][k]!=0)

                //update attribute list of new relation
                 for(int k=0; k<n; k++)
                {
                    cout<<x[r].a[k]<<"\t";//=fd[i][k];
                }
                cout<<"reln created\n";

                for(int k=0; k<n; k++)
                {
                    x[r].fd[0][k]=fd[i][k];
                }
                x[r].f=1;
                cout<<"fds copied\n";
                 for(int k=0; k<n; k++)
                {
                    cout<<x[r].fd[0][k]<<"\t";//=fd[i][k];
                }
                cout<<endl;
                for(int k=0; k<n; k++)
                {
                    if(fd[i][k]==-1)
                        a[k]=0;
                }

                //remove fd
                for(int j=0; j<n; j++)
                    fd[i][j]=0;
                cout<<"fd removed in original\n";


                for(int j=i+1; j<f; j++)
                {
                    cout<<"Searching for sim pfd\n";
                    int sim_pfd=1;
                    for(int k=0; k<n; k++)
                    {
                        if((x[r].fd[0][k]==1)&&(fd[j][k]!=1))
                        {
                            sim_pfd=0;
                            break;
                        }
                        if((fd[i][k]==1)&&(x[r].fd[0][k]!=1))
                        {
                            sim_pfd=0;
                            break;
                        }

                    }
                    if(sim_pfd==1)
                    {
                        cout<<"Sim PFD found\n";
                        for(int k=0; k<n; k++)
                        {
                            x[r].fd[x[r].f][k]=fd[j][k];
                        }
                        x[r].f++;

                        for(int k=0; k<n; k++)
                        {
                            if(fd[j][k]==-1)
                                x[r].a[k]=fd[j][k];
                        }

                        for(int l=0; l<n; l++)
                            fd[j][l]=0;

                    }

                }
            }
        }

}
void reln::disp2(reln x[])
{
    for(int k=0; k<=r; k++)
    {

        for(int i=0; i<n; i++)
            cout<<x[k].a[i]<<"\t";
        cout<<endl;
        for(int i=0; i<x[k].f; i++)
        {
            for(int j=0; j<n; j++)
                cout<<x[k].fd[i][j]<<"\t";
            cout<<endl;
        }
        cout<<"=========\n";
    }


}
int main()
{
    cout<<"Hello World!\n";
    reln x[N];
    x[0].init();
    x[0].disp();
    x[0].nf2(x);
    x[0].disp2(x);
    cout<<r;
    return(0);
}
