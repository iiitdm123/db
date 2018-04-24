#include <bits/stdc++.h>
using namespace std;
struct fd
{
	string lhs, rhs;
	void read();
	bool operator< (fd other) const;
};

struct table
{
	string keys;
	set< char > columns;
};

set< fd > org_set, set2;
string chosen_key;
vector< set< char > > tables;
vector< table > thirdnf;
int done[256];

void fd::read()
{
	cin>>lhs>>rhs;
}

bool fd::operator< (fd other) const
{
	if (lhs == other.lhs)
		return rhs < other.rhs;
	return lhs < other.lhs;
}

void input(set< fd > *s)
{
	int n;
	cout<<"Enter the number of FD's: ";
	cin>>n;
	cout<<"Enter the FD's:\n";
	for (int i = 0; i < n; i++)
	{
		fd temp;
		temp.read();
		s->insert(temp);
	}
}

void decomp_right()
{
	set< fd >::iterator iter = org_set.begin();
	while (iter != org_set.end())
	{
		if ((*iter).rhs.size() == 1)
		{
			iter++;
			continue;
		}
		fd to_decomp = *iter;
		org_set.erase(iter);
		for (int i = 0; i < to_decomp.rhs.size(); i++)
		{
			fd to_ins;
			to_ins.lhs = to_decomp.lhs; to_ins.rhs = to_decomp.rhs[i];
			org_set.insert(to_ins);
		}
		iter = org_set.begin();
	}
}

void output(set< fd > s)
{
	set< fd >::iterator iter = s.begin();
	cout<<"FDs:\n";
	while (iter != s.end())
	{
		cout<<(*iter).lhs<<" -> "<<(*iter).rhs<<endl;
		iter++;
	}
	cout<<endl<<endl;
}

bool subset_check(string a, string b)
{
	for (int i = 0; i < a.size(); i++)
	{
		int flag = 0;
		for (int j = 0; j < b.size(); j++)
		{
			if (b[j] == a[i])
			{
				flag = 1;
				break;
			}
		}
		if (!flag)
			return false;
	}
	return true;
}

string merge(string a, string b)
{
	for (int i = 0; i < a.size(); i++)
	{
		int flag = 0;
		for (int j = 0; j < b.size(); j++)
		{
			flag += (b[j] == a[i]);
		}
		if (!flag)
			b += a[i];
	}
	return b;
}

string closure(set< fd > *s, string attr)
{
	string curr_clos = "";
	curr_clos += attr;
	while (true)
	{
		int prev_s = curr_clos.size();
		set< fd >::iterator iter = s->begin();
		for (int i = 0; i < s->size(); i++)
		{
			if (subset_check((*iter).lhs, curr_clos))
			{
				curr_clos = merge((*iter).rhs, curr_clos);
			}
			iter++;
		}
		if (curr_clos.size() == prev_s)
			break;
	}
	return curr_clos;
}

bool equivalent(set< fd > *s1, set< fd > *s2)
{
	set< fd >::iterator iter1 = s1->begin();
	set< fd >::iterator iter2 = s2->begin();
	for (int i = 0; i < s1->size(); i++)
	{
		string temp = closure(s2, (*iter1).lhs);
		if (!subset_check((*iter1).rhs, temp))
			return false;
		iter1++;
	}

	for (int i = 0; i < s2->size(); i++)
	{
		string temp = closure(s1, (*iter2).lhs);
		if (!subset_check((*iter2).rhs, temp))
			return false;
		iter2++;
	}

	return true;
}

void minimal_cover(set< fd > *s) //Check
{
	set< fd >::iterator iter = s->begin();
	set< fd > s_new = *s;
	for (int i = 0; i < s->size() and iter != s->end(); i++)
	{
		fd temp = *iter, temp1;
		temp1.rhs = temp.rhs;
		if (temp.lhs.size() == 1)
		{
			iter++;
			continue;
		}
		s_new.erase(temp);
		string req = "";
		for (int j = 0; j < temp.lhs.size(); j++)
		{
			if (j == temp.lhs.size()-1 and req == "")
			{
				req += temp.lhs[j];
				break;
			}
			string curr_try = req;
			for (int k = j+1; k < temp.lhs.size(); k++)
				curr_try += temp.lhs[k];
			temp1.lhs = curr_try;
			s_new.insert(temp1);
			if (!equivalent(&s_new, s))
				req += temp.lhs[j];
			s_new.erase(temp1);
		}

		if (req != temp.lhs)
		{
			iter = s->erase(iter);
			temp.lhs = req;
			s->insert(temp);
		}
		iter++;
	}

	s_new = *s;
	iter = s->begin();
	for (int i = 0; i < s->size() and iter != s->end(); i++)
	{
		fd temp = *iter;
		s_new.erase(temp);
		if (equivalent(&s_new, s))
		{
			iter = s->erase(iter);
		}
		else
			s_new.insert(temp);
		iter++;
	}
}

string keys(set< fd > *s) //Deprecated
{
	string curr_keys = "";
	set< fd >::iterator iter = s->begin();
	for (int i = 0; i < s->size(); i++)
	{
		curr_keys = merge((*iter).lhs, curr_keys);
		curr_keys = merge((*iter).rhs, curr_keys);
		iter++;
	}
	string req = "";
	for (int i = 0; i < curr_keys.size(); i++)
	{
		string temp = req;
		for (int j = i+1; j < curr_keys.size(); j++)
			temp += curr_keys[j];
		string x = closure(s, temp), y = closure(s, curr_keys);
		if (!(subset_check(x, y) and subset_check(y, x)))
			req += curr_keys[i];
	}
	return req;
}

void keys2(set< fd > *s)
{
	string possb_set = "";
	set< fd >::iterator iter = s->begin();
	for (int i = 0; i < s->size() and iter != s->end(); i++)
	{
		possb_set = merge((*iter).lhs, possb_set);
		iter++;
	}

	vector<int> v;

	for (int i = 1; i < (1<<possb_set.size()); i++)
	{
		string curr = "";
		for (int j = 0; j < possb_set.size(); j++)
		{
			if (i & (1<<j))
			{
				curr += possb_set[j];
			}
		}
		string x = closure(s, curr), y = closure(s, possb_set);
		if (subset_check(x, y) and subset_check(y, x))
		{
			int flag1 = 0;
			for (int j = 0; j < v.size(); j++)
			{
				if ((v[j]&i) == v[j])
					flag1++;
			}
			if (!flag1)
			{
				v.push_back(i);
				cout<<curr<<endl;
			}
		}
	}
}

void second_nf(set< fd > *s)
{
	for (int i = 0; i < (1<<chosen_key.size()); i++)
	{
		set< char > temp;
		tables.push_back(temp);
	}
	for (int i = 0; i < chosen_key.size(); i++)
	{
		done[int(chosen_key[i])] = 1;
	}
	for (int i = 1; i <= chosen_key.size(); i++)
	{
		for (int j = 1; j < (1<<chosen_key.size()); j++)
		{
			int c1 = 0;
			string curr = "";
			for (int k = 0; k < chosen_key.size(); k++)
			{
				if (j&(1<<k))
				{
					c1++;
					curr += chosen_key[k];
				}
			}
			if (c1 == i)
			{
				string temp = closure(s, curr);
				string not_done = "";
				int c2 = 0;
				for (int k = 0; k < temp.size(); k++)
				{
					if (!done[int(temp[k])])
					{
						c2++;
						not_done += temp[k];
					}
				}
				if (c2 > 0)
				{
					for (int k = 0; k < not_done.size(); k++)
					{
						done[int(not_done[k])] = 1;
						tables[j].insert(not_done[k]);
					}
					for (int k = 0; k < curr.size(); k++)
					{
						tables[j].insert(curr[k]);
					}
				}
			}
		}
	}
}

void output_2nf()
{
	for (int i = 1; i < (1<<chosen_key.size()); i++)
	{
		if (tables[i].size() > 0)
		{
			string curr = "";
			for (int k = 0; k < chosen_key.size(); k++)
			{
				if (i&(1<<k))
				{
					curr += chosen_key[k];
				}
			}
			cout<<"Table with primary key(s) "<<curr<<endl;
			cout<<"Columns:\n";
			set< char >::iterator iter = tables[i].begin();
			while (iter != tables[i].end())
			{
				cout<<*iter<<" ";
				iter++;
			}
			cout<<endl;
		}
	}
}

void find_and_insert(string key, char to_ins)
{
	int flag = 0;
	for (int i = 0; i < thirdnf.size(); i++)
	{
		if (thirdnf[i].keys == key)
		{
			thirdnf[i].columns.insert(to_ins);
			return;
		}
	}
	table temp;
	temp.keys = key;
	temp.columns.insert(to_ins);
	for (int i = 0; i < key.size(); i++)
		temp.columns.insert(key[i]);
	thirdnf.push_back(temp);
}

void third_nf()
{
	for (int i = 1; i < (1<<chosen_key.size()); i++)
	{
		if (tables[i].size() > 0)
		{
			string curr = "";
			for (int k = 0; k < chosen_key.size(); k++)
			{
				if (i&(1<<k))
				{
					curr += chosen_key[k];
				}
			}
			table temp;
			temp.keys = curr;
			temp.columns = tables[i];

			vector< char > to_rem;
			set< char >::iterator iter = temp.columns.begin();

			while (iter != temp.columns.end())
			{
				set< fd >::iterator iter2 = org_set.begin();
				while (iter2 != org_set.end())
				{
					if ((*iter2).rhs[0] == *iter)
					{
						if ((*iter2).lhs != curr)
						{
							to_rem.push_back(*iter);
							find_and_insert((*iter2).lhs, *iter);
						}
					}
					iter2++;
				}
				iter++;
			}

			for (int k = 0; k < to_rem.size(); k++)
			{
				temp.columns.erase(to_rem[k]);
			}

			thirdnf.push_back(temp);
		}
	}
}

void output_3nf()
{
	for (int i = 0; i < thirdnf.size(); i++)
	{
		cout<<"Table with primary key(s) "<<thirdnf[i].keys<<endl;
		cout<<"Columns: "<<endl;
		set< char >::iterator iter = thirdnf[i].columns.begin();
		while (iter != thirdnf[i].columns.end())
		{
			cout<<*iter<<" ";
			iter++;
		}
		cout<<endl;
	}
}

int main()
{
	input(&org_set);
	decomp_right();
	minimal_cover(&org_set);
	output(org_set);
	cout<<"Possible choices for primary keys:\n";
	keys2(&org_set);
	cout<<endl;
	cout<<"Enter the keys: ";
	cin>>chosen_key;
	cout<<chosen_key<<endl<<endl;
	cout<<"After Second Normal Form:\n\n";
	second_nf(&org_set);
	output_2nf();
	third_nf();
	cout<<"After Third Normal Form:\n\n";
	output_3nf();
	return 0;
}
