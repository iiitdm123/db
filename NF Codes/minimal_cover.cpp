#include<iostream>
#include<cmath>

using namespace std;
const unsigned int N=5;//no. of attributes
const unsigned int F=4+10;//no. of FDs plus 10 extra for decomposition
int r=4;
int inf=100;//F must be loss than inf

class fdset
{
    int f;
    int n;
    int g[N];
    int p[N];
    int fd[F][N];

    public:
        void init();
        void closure(int marked);
        //void set_prime(int i);
        void calc_ck();
        void disp();
        void min_cover();

};
void fdset::init()
{
    f=r;//fill no of FDs
    n=N;

    int a[F][N]={{1, -1, -1, 0, 0}, {1, 1, 0, -1, 0}, {0, 0, 0, 1, -1}, {1, 0, 0, 0, -1}};// -1, 0}};//, {-1, 0, 1}, {1, 1, -1}};

    for(int i=0; i<f; i++)
    {
        for(int j=0; j<N; j++)
        {
            fd[i][j]=a[i][j];
        }
    }
    for(int i=0; i<n; i++)
    {
        g[i]=-1;
        p[i]=-1;
    }
}
void fdset::disp()
{
    cout<<"Display\n";
    for(int i=0; i<f; i++)
    {
        for(int j=0; j<N; j++)
        {
            cout<<fd[i][j]<<"\t";//=a[i][j];
        }
        cout<<endl;
    }
    cout<<endl;

    cout<<"g array:\n";
    for(int i=0; i<n; i++)
    {
        cout<<g[i]<<"\t";//=-1;
    }
    cout<<endl;

    cout<<"p array:\n";
   for(int i=0; i<n; i++)
    {
        cout<<p[i]<<"\t";//=-1;
    }
    cout<<endl;

}
/*
void fdset::set_prime(int i)
{
    p[i]=1;
    g[i]=1;
}
*/
/*
void fdset::calc_ck()
{
    for(int i=0; i<n; i++)
    {
        if (g[i]!=1)
        {
            for(int j=0; j<f; j++)
            {
                if (fd[j][i]==-1)
                {
                    for(int k=0; k<n; k++)
                    {
                        if ((fd[j][k]==1)&&(g[k]!=1))
                        {
                           //set_prime(k);
                           p[k]=g[k]=1;
                        }
                    }
                    for(int k=0; k<n; k++)
                    {
                        if ((fd[j][k]==-1)&&(g[k]!=1))
                        {
                             g[k]=1;
                        }
                    }
                    break;
                }

             }
            if(g[i]!=1)
                set_prime(i);
        }
    }
    for(int i=0; i<f; i++)
    {
        int flag=0;
        for(int j=0; j<n; j++)
        {
            if ((fd[i][j]==1)&&(p[j]!=1))
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
                for(int k=0; k<n; k++)
                {
                    if((fd[i][k]==-1)&&(p[k]==1))
                        p[k]=-1;
                }
        }

    }

}
*/
void fdset::min_cover()
{
    //step 1
    for(int i=0; i<f; i++)
    {
        int mul_lhs=0;

        for(int j=0; (j<n)&&(mul_lhs<=1); j++)
        {
            if (fd[i][j]==-1)
            {
                mul_lhs++;
            }
        }
        if (mul_lhs==2)
        {
            cout<<"Multiple lhs found\n";

            cout<<f;
            int j=0;

            while (fd[i][j]!=-1)
            {
                    fd[f][j]=fd[i][j];
                    j++;
            }
            fd[f][j]=0;
            j++;

            while(j<n)
            {
                    fd[f][j]=fd[i][j];

                    if(fd[i][j]==-1)
                        fd[i][j]=0;
                    j++;
            }
            f++;

        }
    }
    cout<<"Step 1 complete\n";

    disp();
    /*
    p[0]=g[0]=1;
    closure();
    disp();
    */
    //step 2
/*
    int v[]={1, 0, 0};
    for(int i=0; i<n; i++)
        g[i]=v[i];

    closure(2);
    cout<<"Disp after closure:\n";
    disp();

*/
    for(int i=0; i<f; i++)
    {
        cout<<i<<"  step 2\n";
        int n1=0;
        int a[N];
        for(int j=0; j<N; j++)
            a[j]=0;
        for(int j=0; j<n; j++)
            if(fd[i][j]==1)
                n1++;

        cout<<"n1=  "<<n1<<endl;

        if(n1==1)
            continue;

        for(int c=1; c<pow(2, n1); c++)
        {
            for(int j=0; j<n1; j++)
            if(c%int(pow(2, j+1))==0)
                a[j]=!a[j];

            cout<<"subset array\n";
                for(int j=0; j<n; j++)
                    cout<<a[j]<<"\t";

        for(int k=0; k<n; k++)
        {
            g[k]=-1;
            p[k]=-1;
        }

        for(int j=0, k=0; j<n; j++)
            if(fd[i][j]==1)
            {
                p[j]=a[k];
                g[j]=a[k];
                k++;
            }
        closure(inf);

        cout<<"\nDisplay after closure:\n";
        disp();

        int rhs=1;
        for(int j=0; j<n; j++)
            if((fd[i][j]==-1)&&(g[j]!=1))
            {
                rhs=0;
                break;
            }

        if(rhs==1)
        {
            for(int j=0; j<n; j++)
                if((fd[i][j]==1)&&(p[j]!=1))
                {
                    fd[i][j]==0;
                }

        }

        for(int j=0; j<n; j++)
        {
            if((g[j]==1)&&(p[j]!=1)&&(fd[i][j]==1))
                fd[i][j]=0;
        }

        }

    }
    cout<<"Display after step 2:\n";
    disp();

    //step 3

    for(int i=0; i<f; i++)
    {
        int flag=0;

        for(int j=0; j<n; j++)
            if(fd[i][j]==1)
            {
                g[j]=1;
                flag=1;
            }
            else
            {
                g[j]=0;
            }

        if(flag==1)
        {
            closure(i);
        }
        else
            continue;
        int j;
        for( j=0; j<n; j++)
            if(fd[i][j]==-1)
                break;
        if(g[j]==1)
        {
            for(int k=0; k<n; k++)
                fd[i][k]=0;
        }
    }

    cout<<"Disp after mock step 3:\n";
    disp();

}

void fdset::closure(int marked=inf)
{
    int flag=1;

    while(flag==1)
    {
        flag=0;
        for(int i=0; i<f; i++)
        {
            if (i==marked)
                continue;
            int na=0;
            for(int j=0; j<n; j++)//checking if an FD can be applied
            {
                if((fd[i][j]==1)&&(g[j]!=1))
                {
                    na=1;
                    break;
                }
            }
            if(na==0)
            {
                for(int j=0; j<n; j++)
                {
                    if((fd[i][j]==-1)&&(g[j]!=1))
                    {
                        g[j]=1;
                        flag=1;
                    }
                }
            }
        }
    }

}
int main()
{
    cout<<"Hello World!\n";

    fdset x;
    x.init();
    x.disp();
    x.min_cover();
    x.disp();
return(0);
}


  /*start
                cout<<"----\n";
                for(int i=0; i<n; i++)
                {
                    cout<<g[i]<<"\t";//=-1;
                }

                cout<<endl;
                for(int i=0; i<n; i++)
                {
                    cout<<p[i]<<"\t";//=-1;
                }
                cout<<endl;
end*/
