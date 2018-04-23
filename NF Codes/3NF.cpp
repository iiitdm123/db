#include<iostream>
using namespace std;
const int N=7;
const int F=4;
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
    void nf3(reln x[]);
    void disp2(reln x[]);
};
void reln::init()
{
    cout<<"\nInitialize\n---------------\n";
    int c[]={1, 1, -1, -1, -1, -1, -1};
    int cp[][N]={{1, 1, -1, -1, 0, 0, 0}, {0, 0, 1, 0, -1, 0, 0}, {0, 0, 1, 0, 0, -1, 0}, {0, 0, 0, 1, 0, 0, -1}};
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
    cout<<"-----\nCK: \n";

    for(int i=0; i<n; i++)
        cout<<a[i]<<"\t";

    cout<<"\ndisp\n---------------\n";
    for(int i=0; i<f; i++)
    {
        for(int j=0; j<n;j++)
        {
            cout<<fd[i][j]<<"\t";//=cp[i][j];
        }
        cout<<endl;
    }


}
void reln::nf3(reln x[])
{
    cout<<"\nnf3\n---------------\n";


    for(int i=0; i<f; i++)
    {
        cout<<"fd scan\n";
        int lsk=1;//is the LHS a superkey?
        int nf3fd=0;//rhs has only prime attributes
        //int ppfd=0;
        int non_empty=0;
        for(int j=0; j<n; j++)
        {
            if((a[j]==1)&&(fd[i][j]!=1))
            {
                lsk=0;
                break;
            }

        }
        if(lsk==0)
        {
            for(int j=0; j<n; j++)
                if((fd[i][j]==-1)&&(a[j]!=1))
                 {
                     nf3fd=1;
                     break;
                 }

        }

        if(nf3fd==1)
        {
            cout<<"found nf3fd: i=\n"<<i<<endl;
            r++;
            x[r].n=n;

            //create new relation
             for(int k=0; k<n; k++)
             {
                   x[r].a[k]=fd[i][k];
             }
             //copy fd
             for(int k=0; k<n; k++)
                {
                    x[r].fd[0][k]=fd[i][k];
                }
                x[r].f=1;
            //remove attributes on LHS of fd from original relation
             for(int k=0; k<n; k++)
                {
                    if(fd[i][k]==-1)
                        a[k]=0;
                }
            //wipe fd in original relation
                for(int j=0; j<n; j++)
                    fd[i][j]=0;

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
                        for(int k=0; k<n; k++)
                            if(fd[j][k]==-1)
                                a[k]=0;

                        for(int l=0; l<n; l++)
                            fd[j][l]=0;



                    }

                }

        }
    }
/*
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
*/

}
void reln::disp2(reln x[])
{
    for(int k=0; k<=r; k++)
    {

        cout<<"-----\nCK: \n";
        for(int i=0; i<n; i++)
            cout<<x[k].a[i]<<"\t";
        cout<<endl;

        cout<<"FDs: \n";
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
    x[0].nf3(x);
    x[0].disp2(x);
    cout<<r;
    return(0);
}
