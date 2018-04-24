#include <bits/stdc++.h>
using namespace  std;
struct order
{

	bool operator() (set<char> x,set<char> y)
	{
		if(x.size()==y.size())
			return x<y ;
		return x.size()<y.size();
	}

};

typedef multimap< set< char >, set< char > >::iterator  mitr;
typedef set< char >::iterator  sitr;
typedef set <multimap<set<char>,set<char> > >::iterator  mitr2;
void printfd(multimap< set< char>, set< char > > &m);
void removeduplicates(multimap<set< char >,set< char > > &m);
int rhsdecomp( multimap<set< char >,set< char> > &m);
void minimalcover(multimap< set< char>, set< char > > &m);
int lhscheck(multimap<set<char>,set<char> > &m);
bool issubset(set<char> s1,set<char> s2);
int removetransitives(multimap<set<char>,set<char> > &m);
void closure(set<char> &s,multimap<set<char>,set<char> > &m,vector<int> &d);
void union_sets(set<char> &s,set<char> &t);
int search(char q,char a[]);
void candkey(multimap<set<char>,set<char> > &m,char b[],int q);
void binary(int i,int bin[],int q);
int twonf(multimap<set<char>,set<char> > &m, set<char> &selectedck);
void getall(set<char> &t,multimap<set<char>,set<char> > &m);
void threenf(multimap<set<char>,set<char> > &m, set<char> &selectedck);

int p;
char a[100];
int n,w=0;

set <multimap<set<char>,set<char> > >m2,m3;
int main()
{
  cout<<"Enter no of attributes"<<endl;
  cin>>p;
  char b[100];
  int k;
  cout<<"Enter the attributes"<<endl;
  for(int i=0;i<p;i++)
  {
    cin>>a[i];
  }
  
  cout<<"Enter no of FD relations"<<endl;
  cin>>n;
  set< char > lhs;
  set< char > rhs;
  multimap< set< char >, set< char> > m,temp;
  int d;
  char t;
  for(int i=0;i<n;i++)
  {
    cout<<"Enter no of elements in lhs set "<<i+1<<endl;
    cin>>d;
     cout<<"Enter the elements "<<endl;
    for(int j=0;j<d;j++)
    {
     
      cin>>t;
      lhs.insert(t);
    }

    cout<<"Enter no of elements in rhs set "<<i+1<<endl;
    cin>>d;
    cout<<"Enter the elements"<<endl;
    for(int j=0;j<d;j++)
    {
      cin>>t;
      rhs.insert(t);
    }
    m.insert(pair<set< char >, set< char > > (lhs,rhs));
    lhs.clear();
    rhs.clear();
  }

  printfd(m);
  minimalcover(m);
  int no_of_changes;
    set<multimap<set<char>,set<char> > > sm;
  typedef set<multimap<set<char>,set<char> > >::iterator smitr;
  
  	//printfd(m);

  cout<<"Minimal Candidate keys"<<endl;
  candkey(m,a,p);
  string s;
  cout<<"~~~~~~~~~Second Normal Form~~~~~~~~~~~"<<endl;
  cout<<"Select Candidate key"<<endl;
  cin>>s;
  set<char> selectedck;
  for(int i=0;i<s.length();i++)
  {
  	selectedck.insert(s[i]);
  }
  no_of_changes=twonf(m,selectedck);
  set<char> get;
  cout<<"2NF:"<<endl;
  for(mitr2 m2i=m2.begin();m2i!=m2.end();)
	{
		get.clear();
		temp=*m2i;
		if(temp.size()==0)
		{
			m2.erase(m2i++);
			continue;
		}
		getall(get,temp);
		cout<<"R=( ";
		for(sitr sit=get.begin();sit!=get.end();sit++)
		{
			
			cout<<*sit<<" ";
		}
		cout<<" )"<<endl;
		
		printfd(temp);
		temp.clear();
		m2i++;
	}
		 cout<<"~~~~~~~~~Third Normal Form~~~~~~~~~~~"<<endl;
  for(mitr2 m2i=m2.begin();m2i!=m2.end();m2i++)
  {
  	temp=*m2i;
  	printfd(temp);
  	get.clear();
		
		getall(get,temp);
		k=0;
		for(sitr sit=get.begin();sit!=get.end();sit++)
		{
			
			b[k++]=(*sit);
		}
	cout<<"Minimal Candidate keys"<<endl;
  candkey(temp,b,k);
  string s;
  cout<<"Select Candidate key"<<endl;
  cin>>s;
  set<char> selectedck;
  for(int i=0;i<s.length();i++)
  {
  	selectedck.insert(s[i]);
  }
  threenf(temp,selectedck);
 	m3.insert(temp);

  }
  cout<<"3NF:"<<endl;
  for(mitr2 m2i=m3.begin();m2i!=m3.end();m2i++)
	{
		get.clear();
		temp=*m2i;
		getall(get,temp);
		cout<<"R=( ";
		for(sitr sit=get.begin();sit!=get.end();sit++)
		{
			
			cout<<*sit<<" ";
		}
		cout<<" )"<<endl;
		
		printfd(temp);
		temp.clear();
	}
return 0;
}

void removeduplicates(multimap<set< char >,set< char > > &m)
{
  int flag=0;
  multimap<set< char >,set< char> > m2;
//cout<<m.size()<<endl;
  mitr mit=m.begin();
  while(m.size()>0)
  {
    m2.insert(pair<set<char>,set<char> >(mit->first,mit->second));

    for(mitr itr=m.begin();itr!=m.end();)
    {

      if(itr->first==mit->first && itr->second==mit->second)
      {
        m.erase(itr++);
      }
      else
      itr++;
    }

    mit=m.begin();
//cout<<m.size()<<endl;
  }

  m=m2;
}
int rhsdecomp( multimap<set< char >,set< char> > &m)
{
    multimap<set< char >,set< char> > m1;
    set< char > temp;


    int  no_of_changes=0;
    for(mitr mit=m.begin();mit!=m.end();mit++)
      {
        if((mit->second).size()>1)
        {
          no_of_changes++;
          for(sitr sit=(mit->second).begin();sit!=(mit->second).end();sit++)
          {
            temp.insert(*sit);
            m1.insert(pair<set < char >,set< char >  > (mit->first,temp));
            temp.clear();
          }
        }
        else
        {
          m1.insert(pair<set< char >,set< char > > (mit->first,mit->second));
        }
      }
      m=m1;
      m1.clear();
      return no_of_changes;
}
void minimalcover(multimap< set< char>, set< char > > &m)
{
  int no_of_changes;
  do{
    no_of_changes=0;
  no_of_changes+=rhsdecomp(m);
  removeduplicates(m);
  no_of_changes+=lhscheck(m);
  removeduplicates(m);
  no_of_changes+=removetransitives(m);
  } while(no_of_changes!=0);
  cout<<"minimalcover"<<endl;
  printfd(m);
}

void printfd(multimap< set< char>, set< char > > &m)
{
  cout<<"{ ";
  for(mitr mit=m.begin();mit!=m.end();mit++)
  {
    cout<<"{ ";
    for(sitr sit=(mit->first).begin();sit!=(mit->first).end();sit++)
    {
      cout<<*sit<<" ";
    }
    cout<<"} ----> { ";
    for(sitr sit=(mit->second).begin();sit!=(mit->second).end();sit++)
    {
      cout<<*sit<<" ";
    }
    if(mit!=(--m.end()++))
    cout<<"}, ";
    else
    cout<<"} ";
  }
  //cout<<m.find(*((mit->first).begin()))->second<<endl;
  cout<<"}"<<endl;
}

int lhscheck(multimap<set<char>,set<char> > &m)
{
	int no_of_changes=0;
	multimap<set<char>,set<char> > m2;
	int flag=0;
	for(mitr mit=m.begin();mit!=m.end(); mit++)
	{
			flag=0;
		for(mitr tmit=m.begin();tmit!=m.end();tmit++)
		{
			
			if(issubset(tmit->first,mit->first) && issubset(tmit->second,mit->first) && tmit->first!=mit->first && tmit->second!=mit->first)
			{

				flag=1;
				no_of_changes++;
				m2.insert(pair<set<char>,set<char> > (tmit->first,mit->second));
		
			}
		}
		if(flag==0)
		{
			m2.insert(pair<set<char>,set<char> >(mit->first,mit->second));
			

		}	
	}
	m=m2;
	m2.clear();
	
	return no_of_changes;

}

bool issubset(set<char> s1,set<char> s2)
{
	//cout<<*s1.begin()<<endl;
	int flag=0;
	if(s1.size()>s2.size())
		return false;
	else 
	{
		for(sitr sit=s1.begin();sit!=s1.end();sit++)
		{
			for(sitr tsit=s2.begin();tsit!=s2.end();tsit++)
			{
				if(*sit==*tsit)
				{
					flag=1;
				}
			}
			if(flag==0)
				return false;
			flag=0;
		}
	}


return true;
}

int removetransitives(multimap<set<char>,set<char> > &m)
{
	int no_of_changes=0,flag=0;
	set<char> s,l;
	int i,j=0;
	vector<int> d;
 	multimap<set<char>,set<char> > m2;
	
	m2=m;
	
	
	for(mitr mit=m2.begin();mit!=m2.end();)
	{
		m2.erase(mit++);
	
		for(mitr it=m.begin();it!=m.end();it++)
		{
			for(sitr sit=(it->first).begin();sit!=(it->first).end();sit++)
			{
				i=search(*sit,a);//here
				d.push_back(i);
				
			}
			closure(l,m2,d);
			closure(s,m,d);
			if(l!=s)
			{
				
				flag=1;
				break;
				
			}
			
			
			l.clear();
			d.clear();
			s.clear();

		}
		if(flag==0)
		{
		no_of_changes++;
		m=m2;
		
		}
		else
		{
			m2=m;
			mit=m2.begin();
			for(int k=0;k<=j;k++)
			{
				mit++;
			}
			j++;
		}
	flag=0;
	}
	
	return no_of_changes;
}

void closure(set<char> &s,multimap<set<char>,set<char> > &m,vector<int> &d)
{
	set<char> olds;
	set<char> temp;
	
	for(int i=0;i<d.size();i++)
	s.insert(a[d[i]]);
	while(olds!=s)
	{
		//cout<<"old"<<endl;
		olds=s;
		for(mitr mit=m.begin();mit!=m.end();mit++)
		{
			if(issubset(mit->first,s))
			{
				union_sets(s,mit->second);
			}
		}
	}


	/*for(sitr sit=s.begin();sit!=s.end();sit++)
		cout<<*sit;
	cout<<endl;*/
}

void union_sets(set<char> &s,set<char> &t)
{
	//cout<<"union"<<endl;
	for(sitr titr=t.begin();titr!=t.end();titr++)
		s.insert(*titr);
}

int search(char q,char a[])
{
	for(int i=0;i<p;i++)
	{
		if(q==a[i])
			return i;
	}
}

void candkey(multimap<set<char>,set<char> > &m,char b[],int q)
{
	//printfd(m);
	if(m.size()==1)
	{
		for(mitr mit=m.begin();mit!=m.end();mit++)
		{
			for(sitr sit=(mit->first).begin();sit!=(mit->first).end();sit++)
			{
				cout<<*sit;
			}
			cout<<endl;
		}
		return ;
	}
set<set<char>,order > key;
set<char> s,cand,temp;
vector <int > d;
typedef set<set<char> >::iterator sitrr;
for(int k=0;k<q;k++)
{
	s.insert(b[k]);

}
int bin[q]={0},marked[q]={0};
for(int i=1;i<pow(2,q);i++)
{
	//cout<<i<<endl;
	binary(i,bin,q);
	for(int k=0;k<q;k++)
	{
		if(bin[k]==1 && marked[k]==0)
			d.push_back(k);
	}
	closure(cand,m,d);
	if(cand==s)
	{
		for(int k=0;k<d.size();k++)
		{
					marked[d[k]]=1;
				temp.insert(a[d[k]]);
		}

		key.insert(temp);
		temp.clear();
		cand.clear();
		d.clear();
	}
	else
	{
		d.clear();
		cand.clear();
	}
}

	for(sitrr kitr=key.begin();kitr!=key.end();kitr++)
	{
		
		for(sitr sit=(*kitr).begin();sit!=(*kitr).end();sit++)
		{
			
			cout<<*sit;
			
		}
		cout<<endl;
	}

}

void binary(int i,int bin[],int q)
{
	int k=q-1;
	while(i!=0 && k>=0)
	{
		bin[k]=i%2;
		i=i/2;
		k--;
	}
}
int twonf(multimap<set<char>,set<char> > &m, set<char> &selectedck)
{
	//cout<<"2NF"<<endl;
	int no_of_changes=0;
		int w=0;
		multimap<set<char>,set<char> > temp;
	if(selectedck.size()!=1)
	{
	
		for(mitr mit=m.begin();mit!=m.end();mit++)
		{
			if(issubset((mit->first),selectedck) && mit->first!=selectedck)
			{
				no_of_changes++;
				for(mitr mitt=m.begin();mitt!=m.end();)
				{
				if(mitt->first==mit->first)	
				{
				temp.insert(pair<set<char>,set<char> > (mitt->first,mitt->second));
				m.erase(mitt++);
				}
				else
					mitt++;
				}
				mit=m.begin();
			}
			m2.insert(temp);
			temp.clear();
		}
		

	
	}
	m2.insert(m);
	


	return no_of_changes;
}
void threenf(multimap<set<char>,set<char> > &m, set<char> &selectedck)
{
	int no_of_changes=0;
	multimap<set<char>,set<char> > temp;
	for(mitr mit=m.begin();mit!=m.end();mit++)
	{
		if(mit->first!=selectedck)
		{
			cout<<*((mit->first).begin())<<endl;
			for(mitr mmit=m.begin();mmit!=m.end();)
			{
				if(mmit->first==mit->first)
				{
					temp.insert(pair<set<char>,set<char> > (mmit->first,mmit->second));
					m.erase(mmit++);
					
				}
				else
					mmit++;
			}
			printfd(m);
			m3.insert(temp);
			temp.clear();
			mit=m.begin();

		}

	}
}
void getall(set<char> &t,multimap<set<char>,set<char> > &m)
{
	for(mitr mit=m.begin();mit!=m.end();mit++)
	{
		for(sitr sit=(mit->first).begin();sit!=(mit->first).end();sit++)
			t.insert(*sit);
		for(sitr sit=(mit->second).begin();sit!=(mit->second).end();sit++)
			t.insert(*sit);

	}
}