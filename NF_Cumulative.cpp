//g++ -std=c++0x fds.cpp
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct fd{
    string X;
    string Y;
};

class fds
{
        vector <fd> a;
        string R;
    public:
        fds(vector <fd> , string r);
        fds(){}
        fds(const fds &p){ a = p.a; R = p.R;}
        void uniona();
        void decompose();
        string closure(string);
        void closurefd();
        void mincover();
        string key();
        void display();
        void mincover2();
        void checkloss(vector <string> D);
        vector <string> twonf(string ck);
        vector <string> threenf(string ck);
};
 fds::fds(vector <fd> b, string r)
 {
     a = b;
     R = r;
 }
 void fds::display()
 {
    cout<<"\nR = "<<R<<"\n";
    for(auto x: a)
        cout<<x.X<<"->"<<x.Y<<"\n";

 }
 void fds::uniona()
{
    int i, j;
    for(i=0;i< a.size(); ++i)
    {
         for(j=0;j<a.size(); ++j)
        {
            if(a[i].X == a[j].X && i != j)
            {
                string k, f;
                sort(a[i].Y.begin(), a[i].Y.end());
                sort(a[j].Y.begin(), a[j].Y.end());
                auto it = set_union(a[i].Y.begin(), a[i].Y.end(), a[j].Y.begin(), a[j].Y.end(), k.begin());
                for(auto l = k.begin(); l!= it; ++l)
                f = f + *l;
                a[i].Y = f;
                a.erase(a.begin() + j);
                j--;
            }
        }
    }
}
 void fds::decompose()
{
    fd p;
    vector <fd> b;
    for(auto x: a)
    {
        if(x.Y.length() > 1)
        {
            int k = x.Y.length();
            p.X = x.X;
            while(k--)
            {
                p.Y = x.Y[k];
                b.push_back(p);
            }
        }
        else
            b.push_back(x);
    }
    a = b;
}
string fds::closure(string b)
{
    string r = b, prev;
    /*cout<<"\nInside Closure";
    cout<<a.size(); */
    int i;
    fd x;
    do
      {
        prev = r;
        for(i=0;i<a.size();++i)
        {
            x = a[i];
            //cout<<"\nI value at beg "<<i;
            string k, f;
            sort(r.begin(), r.end());
            sort(x.X.begin(), x.X.end());
            /*
            cout<<"\nr and x.X->x.Y ";
            cout<<r<<" "<<x.X<<"->"<<x.Y<<"\n"; */
            auto it = set_difference(x.X.begin(), x.X.end(), r.begin(), r.end(), k.begin());
            for(auto l = k.begin(); l!= it; ++l)
                f = f + *l;
            //cout<<"\nF value "<<f<<"\t";
            if( f.length() == 0)
            {
                /*
                string y, kp;
                sort(x.Y.begin(), x.Y.end());
                sort(r.begin(), r.end());
                //cout<<"\nx.Y and r "<<x.Y<<" "<<r;
                auto itaf = set_union(x.Y.begin(), x.Y.end(), r.begin(), r.end(), kp.begin());
                kp.resize(itaf - kp.begin());
             //   cout<<"\ncheck123";
                r = kp;
                //cout<<"\nY value "<<y<<"\t";
                */int c;
                for(auto p: x.Y)
                {
                    c = 0;
                    for(auto q: r)
                        if( p != q )
                            c++;
                    if(c == r.size())
                        r.push_back(p);
                }
            }
           /* cout<<"R value "<<r<<"\n";
            cout<<"\nI value at end "<<i;
          */

        }
      //  cout<<"\nOUTSIdE1";
      }while(prev != r);
    //cout<<"\nOUTSIDE";
    return r;
}
 bool isequal(vector <fd> a, vector <fd> b)
 {
     if(a.size() != b.size())
        return false;
    else
    {
        int c = 0;
        for(int i=0;i<a.size();++i)
        {
            c = 0;
            for(int j=0;j<b.size();++j)
                if(a[i].X == b[j].X && a[i].Y == b[j].Y)
                    c++;
            if(c == 0)
                return false;
        }
        return true;
    }
 }
 vector<string> getAllSubsets(string set1)
{
    vector< string > subset;
    string empty;
    subset.push_back( empty );

    for (int i = 0; i < set1.size(); i++)
    {
        vector<string> subsetTemp = subset;

        for (int j = 0; j < subsetTemp.size(); j++)
            subsetTemp[j].push_back( set1[i] );

        for (int j = 0; j < subsetTemp.size(); j++)
            subset.push_back( subsetTemp[j] );
    }
    return subset;
}

 void fds::closurefd()
{
    uniona();
    fd q;
    vector <fd> f;
    for(auto x: a)
    {
        string p = closure(x.X);
        q.X = x.X;
        q.Y = p;
        f.push_back(q);
    }
    a = f;
}

 void fds::mincover()
{
    vector <fd> f = a, prev;
    fds p;
    int i, j;
    do{
    prev = f;
    p.a = f;
    p.uniona();
    //p.display();
    f = p.a;
    for(i = 0; i<f.size(); ++i)
    {
        for(j=0;j<f[i].X.length(); ++j)
        {
            string gamma = f[i].X, q, m;
            gamma.erase(remove(gamma.begin(), gamma.end(), f[i].X[j]), gamma.end());
            fds temp = fds(f, R);
            temp.a[i].Y = gamma;
            string gammaPlus = temp.closure(gamma);
            sort(gammaPlus.begin(), gammaPlus.end());
            string y = f[i].Y;
            sort(y.begin(), y.end());
            auto it = set_difference(y.begin(), y.end(), gammaPlus.begin(), gammaPlus.end(), q.begin());
            for(auto l = q.begin(); l != it; ++l)
                m = m + *l;
            if(m.length() == 0)
            {
                f[i].X = gamma;
                j--;
            }
        }
        for(j=0;j<f[i].Y.length();++j)
        {
            fds f1 = fds(f, R);
            string gamma = f[i].Y;
            int m;
            gamma.erase(remove(gamma.begin(), gamma.end(), f[i].Y[j]), gamma.end());
            f1.a[i].Y = gamma;
            string alphaPlus = f1.closure(gamma);
            for(auto m: alphaPlus)
                if(m == f[i].Y[j])
                {
                    f[i].Y = gamma;
                    j--;
                }
        }
    }
    }while(!isequal( prev, f));
    /*fds q;
    vector <fd> lmo;
    for(int i = 0;i < f.size(); ++i)
    {
        lmo = f;
        lmo.erase(lmo.begin() + i);
        q.a = lmo;
        q.closurefd();
        if(isequal(q.a, f))
           {f = q.a;
            i--;
            }
    }
    cout<<"CHECK";
    for(auto x: f)
    {
        cout<<x.X<<" "<<x.Y<<"\n";
    }
    */
        fds q;
    q.a = f;
    //q.display();
    for(i=0;i<f.size();++i)
    {
        p.a = f;
        q.a = f;
        p.a.erase(p.a.begin() + i);
        auto x = p.closure(f[i].X);
        auto y = q.closure(f[i].X);
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());
        if(x == y)
            f = p.a;
    }
    a = f;
}
void fds::mincover2()
{
    vector <fd> f = a;
    fds p;
    int i, j;
    p.a = f;
    p.decompose();
    f = p.a;
    for(i = 0; i<f.size(); ++i)
    {
        for(j=0;j<f[i].X.length(); ++j)
        {
            if(f[i].X.length() !=1)
            {string gamma = f[i].X, q, m;
            gamma.erase(remove(gamma.begin(), gamma.end(), f[i].X[j]), gamma.end());
            fds temp = fds(f, R);
            temp.a[i].X = gamma;
            string gammaPlus = temp.closure(gamma);
            sort(gammaPlus.begin(), gammaPlus.end());
            string y = f[i].Y;
            sort(y.begin(), y.end());
            auto it = set_difference(y.begin(), y.end(), gammaPlus.begin(), gammaPlus.end(), q.begin());
            for(auto l = q.begin(); l != it; ++l)
                m = m + *l;
            if(m.length() == 0)
            {
                f[i].X = gamma;
                j--;
            }
            }
        }
    }
    fds q;
    q.a = f;
    for(i=0;i<f.size();++i)
    {
        p.a = f;
        q.a = f;
        p.a.erase(p.a.begin() + i);
        auto x = p.closure(f[i].X);
        auto y = q.closure(f[i].X);
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());
        if(x == y)
        {
            f = p.a;
            i--;
        }
    }

    a = f;

}
string fds::key()
{
    int i;
    string k = R, p;
    sort(k.begin(), k.end());
    sort(R.begin(), R.end());

    for(i=0;i<k.size();++i)
    {

        sort(k.begin(), k.end());
        p = k;
        p.erase(remove(p.begin(), p.end(), k[i]), p.end());
        auto x = closure(p);
        sort(x.begin(),x.end());
        if(x == R)
        {
            k = p;
            i--;
        }
    }
    return k;
}
vector <string> fds::threenf(string ck)
{
    int i, j;
    bool yck = false;
    fds minf = fds(a, R);
    minf.mincover();
    //minf.uniona();
    minf.display();
    vector <string> r;
    for(auto x: minf.a)
    {
        r.push_back(x.X+x.Y);
        string rcheck = x.X + x.Y, k, fp;
        sort(rcheck.begin(), rcheck.end());
        sort(ck.begin(), ck.end());
        auto it = set_difference(ck.begin(), ck.end(), rcheck.begin(), rcheck.end(), k.begin());
        for(auto l = k.begin(); l != it; ++l)
            fp = fp + *l;
        if(fp.length() == 0)
            yck = true;
    }

    if(!yck)
        r.push_back(ck);

    for(i =0; i<r.size();++i)
    {
        for(j=i+1;j<r.size();++j)
        {
            string fp, k;
            sort(r[i].begin(), r[i].end());
            sort(r[j].begin(), r[j].end());
            auto it = set_difference(r[j].begin(), r[j].end(), r[i].begin(), r[i].end(), k.begin());
            for(auto l = k.begin(); l != it; ++l)
            fp = fp + *l;
            if(fp.length() == 0)
            {
                r.erase(r.begin()+j);
                j--;
            }
        }
    }
    return r;
}
 vector <string> fds::twonf(string ck)
{
    int i, c;
    vector <string> r;
    string temp = R;
    for(i=0;i<a.size();++i)
    {
        c = 0;
        for(auto x: ck)
        {
            for(auto y: a[i].X)
                if(y == x)
            {
                c++;
                break;
            }

        }
        if(c > 0 && c < ck.length())
        {
            string k, f;
            sort(a[i].X.begin(), a[i].X.end());
            sort(a[i].Y.begin(), a[i].Y.end());
            auto it = set_union(a[i].X.begin(), a[i].X.end(), a[i].Y.begin(), a[i].Y.end(), k.begin());
            for(auto l= k.begin(); l != it; ++l)
                f = f + *l;
            r.push_back(f);
            string wo, mo;
            sort(temp.begin(), temp.end());
            sort(a[i].Y.begin(), a[i].Y.end());
            auto it2 = set_difference(temp.begin(), temp.end(), a[i].Y.begin(), a[i].Y.end(), wo.begin());
            for(auto l=wo.begin(); l!= it2; ++l)
                mo = mo + *l;
            temp = mo;
        }

    }
    r.push_back(temp);
    return r;
}

void fds::checkloss(vector <string> D)
{
    int n = R.size();
    int m = D.size();
    int i, j, ck;
    int S[m][n], prev[m][n];
    for(i=0;i<m;++i)
        for(j=0;j<n;++j)
            S[i][j] = -1;

    for(i=0;i<m;++i)
        for(auto x: D[i])
            S[i][x-'a'] = 1;
    do{
    for(i=0;i<m;++i)
        for(j=0;j<n;++j)
            prev[i][j] = S[i][j];
    for(auto x: a)
    {
        int k, c = 0;
        for(i=0;i<m;++i)
        {
            c = 0;
            for(j=0;j<x.X.size();++j)
                if(S[i][x.X[j] - 'a']  == 1)
                    c += 1;
            if(c == x.X.size())
            {
                for(k=0;k<m;++k)
                {
                    c = 0;
            for(j=0;j<x.X.size();++j)
                if(S[k][x.X[j] - 'a']  == 1)
                    c += 1;
            if(c == x.X.size())
            {
                for(int l = 0;l<x.Y.size();++l)
                {
                    if(S[i][x.Y[l] - 'a'] != -1)
                        S[k][x.Y[l] - 'a'] = S[i][x.Y[l] - 'a'];
                }
            }
                }
            }
        }
        /*
        for(k=i+1;k<m;++k)
        {
            c = 0;
            for(j=0;j<x.X.size();++j)
                if(S[k][x.X[j] - 'a']  == 1)
                    c += 1;
            if(c == x.X.size())
            {
                for(int l = 0;l<x.Y.size();++l)
                {
                    if(S[i][x.Y[l] - 'a'] != -1)
                        S[k][x.Y[l] - 'a'] = S[i][x.Y[l] - 'a'];
                }
            }
        } */
        cout<<"\nState of matrix S after "<<x.X<<"->"<<x.Y<<"\n";
        for(i=0;i<m;++i)
    {
        for(j=0;j<n;++j)
            cout<<S[i][j]<<" ";
        cout<<"\n";
    }
        for(i=0;i<m;++i)
        {
            c = 0;
            for(j=0;j<n;++j)
                if(S[i][j] == 1)
                    c++;
            if(c == n)
            {cout<<"\n\nYES, lossless\n\n";
                return;
            }
        }

    }
    ck = 0;
    for(i=0;i<m;++i)
        for(j=0;j<n;++j)
            if(S[i][j] != prev[i][j])
                ck = 1;
    }while(ck);
    int c;
    for(i=0;i<m;++i)
        {
            c = 0;
            for(j=0;j<n;++j)
                if(S[i][j] == 1)
                    c++;
            if(c == n)
            {
                cout<<"\n\nYES, lossless\n\n";
                return;
            }
        }

    cout<<"\n\nNO, Lossy\n\n";
}
int main()
{
    fds F;
    int ch;
    do{
        cout<<"Enter choice\n 1. Input\n 2. Mincover\n 3. Candidate key\n 4. 2nf\n 5. 3nf\n 6. Check Lossless\n 7. Display\n 8. Exit\n";
        cin>>ch;
        if(ch == 1)
        {
            int n , i;
            fd p;
            string r;
            vector <fd> a;
            cout<<"Enter the R\n";
            cin>>r;
            cout<<"Enter the number of fds";
            cin>>n;
            cout<<"Enter the fds in the order (X - > Y)\n";
            for(i=1;i<=n;++i)
            {
                cin>>p.X;
                cin>>p.Y;
                a.push_back(p);
            }
            F = fds(a, r);
        }
        else if(ch == 2)
        {
            fds Q = F;
            Q.mincover();
            Q.display();
        }
        else if(ch == 3)
        {
                auto l = F.key();
                cout<<"Candidate key = "<<l<<"\n";
        }
        else if(ch == 4)
        {
            string ck;
            fds Q = F;
            cout<<"\nEnter candidate key to compute 2nf\n";
            cin>>ck;
            auto no = Q.twonf(ck);
            cout<<"\n 2nf decomposition\n";
            for(auto mno : no)
                cout<<mno<<"\n";
        }
        else if(ch == 5)
        {
            string ck;
            fds Q = F;
            cout<<"\nEnter candidate key to compute 3nf\n";
            cin>>ck;
            auto qwe = Q.threenf(ck);
            cout<<"\n R\n";
            for(auto mno : qwe)
                cout<<mno<<"\n";
        }
        else if(ch == 6)
        {
                fds Q = F;
                string relqs;
                vector <string> rels;
                int relofno;
                cout<<"\nEnter the #relations";
                cin>>relofno;
                for(int i = 0;i<relofno;++i)
                {
                    cin>>relqs;
                    rels.push_back(relqs);
                }
                Q.checkloss(rels);
        }
        else if(ch == 7)
            F.display();
    }while(ch < 8 && ch >= 1);
/*
    fds Q = fds(a, r);
    F.display();
    //a = decompose(a);
   // a = uniona(a);
      /* for(auto x: a)
        cout<<x.X<<"->"<<x.Y<<"\n";
        cout<<"\n"; */
      //  cout<<"otha\n";
    /*cout<<closure(a, "cg");
    auto y = closurefd(a);
    cout<<"\n\n\n";
    for(auto x: y)
        cout<<x.X<<"->"<<x.Y<<"\n";
    return 0;
    */
    //F.closurefd();
 /*   F.display();
    F.mincover();
    F.display();
    cout<<"\nMINCOVEr 2\n";
    Q.mincover2();
    Q.display();
    cout<<"\n KEY\n";
//    cout<<F.closure("jsdpqv");
    auto l = F.key();
    cout<<l;

    cout<<"\n running 2nf\n";
    auto no = F.twonf(l);
    for(auto mno : no)
        cout<<mno<<"\n";
    auto lwe = Q.key();
    cout<<"KEY\n"<<lwe;
    cout<<"\n running 3nf\n";
    auto qwe = Q.threenf(lwe);
    cout<<"\n R\n";
    for(auto mno : qwe)
        cout<<mno<<"\n";

    string relqs;
    vector <string> rels;
    int relofno;
    cout<<"\nEnter the #relations";
    cin>>relofno;
    for(int i = 0;i<relofno;++i)
    {
        cin>>relqs;
        rels.push_back(relqs);
    }
    F.checkloss(rels);
    /*
    auto x = getAllSubsets("ABCD");
    for(auto y: x)
        cout<<y<<"\n";
    */
}
/*
a b
a c
cg h
cg i
b h

abcdef
3
a b
c de
ac f

a cde
b fg
ab cdefg


c csjdpqv
sd p
jp c
j s

a d
ab c
ad c
b c
d a
d b

a bc
b c
a b
ab c
*/




