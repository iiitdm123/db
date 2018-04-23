#include<iostream>
using namespace std;
const int R=3;
const int N=6;
const int F=4;
class reln
{
    int s[R][N];
    int fd[F][N];
    int r, n, f;
    int chk[N];
public:
    void init();
    void disp();
    int lossless();
};
void reln::init()
{
    cout<<"----\nx.init()\n";
    r=R;
    n=N;
    f=F;

    int a[][N]={{1, 1, 1, 0, 0, 1}, {0, 1, 0, 1, 0, 0}, {0, 0, 1, 0, 1, 0}};//relations
    int b[][N]={{1, 0, 0, 0, 0, -1}, {0, 1, -1, 0, 0, 0}, {1, 0, 0, -1, 0, 0}, {0, 0, 0, 1, -1, 0}};//FDs

    for(int i=0; i<r; i++)
    {
        for(int j=0; j<n; j++)
        {
            s[i][j]=a[i][j];
        }
    }
    for(int i=0; i<f; i++)
    {
        for(int j=0; j<n; j++)
        {
            fd[i][j]=b[i][j];
        }
    }
    for(int j=0; j<n; j++)
    {
           chk[j]=0;
    }
}

void reln::disp()
{
    cout<<"----\nx.disp()\n";
    cout<<"Schema\n";
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<s[i][j]<<'\t';//=a[i][j];
        }
        cout<<endl;
    }
    cout<<"Fds\n";
    for(int i=0; i<f; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<fd[i][j]<<'\t';//=a[i][j];
        }
        cout<<endl;
    }

    cout<<"Check:\n";
    for(int i=0; i<n; i++)
        cout<<chk[i]<<'\t';
    cout<<endl;
}
/*
int reln::lossless()
{
    cout<<"----\nx.lossless()\n";
    for(int i=0; i<n; i++)
    {
        chk[i]=s[0][i];
    }

    int m[R];
   // int m[R];
    for(int i=0; i<r; i++)
        m[i]=0;
    m[0]=1;
    int toggle=1;
    while(toggle==1)
    {
        toggle=0;
        int flag=0;
        //int i;//=0;
        for(int i=0; i<r; i++)
        {
            if(m[i]==0)
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            for(int i=0; i<r; i++)
            {
                if (m[i]==0)
                {
                    for(int j=0; j<n; j++)
                    {
                        if ((chk[j]==1)&&(s[i][j]==1))
                        {
                            for(int k=0; k<n; k++)
                            {
                               if(chk[k]==0)
                                    chk[k]=s[i][k];

                            }
                            m[i]=1;
                            toggle=1;
                            break;
                        }
                    }

                }
            }
        }
        else break;
    }

    int i=0;
    for(i=0; i<n; i++)
    {
        if (chk[i]!=1)
            break;
    }
    if(i==n)
        return(1);
    else
    {
        cout<<"----\ncheck\n";
        for(int i=0; i<n; i++)
            cout<<chk[i]<<"\t";
        cout<<endl;
        return (0);
    }
}
*/
int reln::lossless()
{
    int change=1;
    while(change==1)
    {
        change=0;
        int m[R];
        for(int i=0; i<f; i++)
        {
            for(int j=0; j<r; j++)
                m[j]=1;

            for(int j=0; j<n; j++)
                chk[j]=0;

            for(int j=0; j<r; j++)
            {
                for(int k=0; k<n; k++)
                    if((fd[i][k]==1)&&(s[j][k]!=1))
                        m[j]=0;
                if(m[j]!=0)
                    for(int k=0; k<n; k++)
                        if(fd[i][k]==-1)
                            chk[k]=1;

            }
            for(int j=0; j<r; j++)
                if(m[j]==1)
                    for(int k=0; k<n; k++)
                        if ((chk[k]==1)&&(s[j][k]!=1))
                        {
                            s[j][k]=1;
                            change=1;
                        }


        }
    }
   // int lossless=0;
    for(int i=0; i<r; i++)
    {
        int lossless=1;
        for(int j=0; j<n; j++)
            if(s[i][j]!=1)
            {
                lossless=0;
                break;
            }
        if(lossless==1)
        {
            cout<<"Lossless Decomposition\n";
            return(1);
        }
    }
    cout<<"Lossy Decomposition";
    return(0);
}
int main()
{
    cout<<"Hello World!\n";
    reln x;
    x.init();
    x.disp();
    cout<<x.lossless();
    return(0);
}
