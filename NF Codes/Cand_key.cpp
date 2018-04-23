#include<iostream>

using namespace std;
const unsigned int N=3;
const unsigned int F=3;
class fdset
{
    int f, n;
    int g[N], p[N];
    int fd[F][N];

    public:
        void init();
        void set_prime(int i);
        void calc_ck();
        void disp();

};
void fdset::init()
{
    f=F;
    n=N;

    int a[F][N]={{-1, 1, 0}, {-1, 0, 1}, {1, 1, -1}};

    for(int i=0; i<f; i++)
    {
        for(int j=0; j<N; j++)
        {
            fd[i][j]=a[i][j];
        }
    }
    for(int i=0; i<n; i++)
    {
        p[i]=g[i]=-1;
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
}
void fdset::set_prime(int i)
{
    p[i]=1;
    g[i]=1;
}
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
int main()
{
    cout<<"Hello World!\n";

    fdset x;
    x.init();
    x.disp();
    x.calc_ck();
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
