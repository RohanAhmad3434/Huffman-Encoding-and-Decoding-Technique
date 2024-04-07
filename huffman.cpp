#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class node
{
public:
	char data;
	int freq;
	node* c0, * c1;
	node()
	{
		data = '\0';
		freq = 0;
		c0 = c1 = NULL;
	}
	node(char d)
	{
		data = d;
		freq = 0;
		c0 = c1 = NULL;
	}
	node(char d, int f)
	{
		data = d;
		freq = f;
		c0 = c1 = NULL;
	}

};

void selection_sort(node *p,int size)
{
	for (int i = 0;i < size;i++)
	{
		int min = i;
		for (int j = i + 1;j < size;j++)
		{
			if (p[min].freq > p[j].freq)
			{
				min = j;
			}
		}
		if (min != i)
		{
			swap(p[min], p[i]);
		}
	}
	
}

string duplicate_remove(string s)
{
	string d;
	bool q;
	for (int i = 0; s[i] != '\0'; i++)
	{
		q = false;
		for (int j = 0; d[j] != '\0'; j++)
		{
			if (s[i] == d[j])
			{
				q = true;
			}

		}
		if (!q)
		{
			d = d + s[i];
		}
	}

	return d;
}
node* find_two_min(node* ptr)
{
	node* min = new node[2];
	min[0] = ptr[0];
	min[1] = ptr[1];
	return min;

}
class huffman
{
public:
	node* root;
	huffman()
	{
		root = NULL;
	}
	void huffman_tree(node* ptr, int create_nodes)
	{
		node* min = new node[2];
		if (create_nodes == 1)
		{
			node* newnode = new node('$');
			min[0] = ptr[0];
			min[1] = *new node(' ',0);
			newnode->freq= min[0].freq + min[1].freq;
			newnode->c0 = new node(min[0]);
			newnode->c1 = new node(min[1]);
			root = newnode;
		}
		else
		{

			while (create_nodes > 1)
			{
				min = find_two_min(ptr);
				/*for (int i = 0; i < 2; i++)
				{
					cout << "Min " << i + 1 << ":  -->" << min[i].data << " freq : -->" << min[i].freq << "     ";
				}
				cout << endl;*/
				node* z = new node('$');
				z->freq = min[0].freq + min[1].freq;
				if (min[0].freq == min[1].freq)
				{
					z->c0 = new node(min[1]);
					z->c1 = new node(min[0]);

				}
				else
				{
					z->c0 = new node(min[0]);
					z->c1 = new node(min[1]);
				}
				for (int i = 0; i < create_nodes - 2; i++)
				{
					ptr[i] = ptr[i + 2];
				}
				ptr[create_nodes - 2] = *z;
				create_nodes--;
				selection_sort(ptr, create_nodes);
				//for (int j = 0; j < create_nodes; j++)
				//{
				//	cout << ptr[j].data << " freq : " << ptr[j].freq << "   ";
				//}
				//cout << endl << endl;
			}
			root = new node(ptr[0]);
		}

	}
	void preorder(node* temp)
	{
		if (temp == NULL)
		{
			return;
		}
		cout << temp->data << "   ";
		preorder(temp->c0);
		preorder(temp->c1);
	}
	 string code;
	void generate_code(node* temp,char r,string s="")
	{
		if (temp == NULL)
		{
			return;
		}
		if (temp->data == r)
		{
			code = s;
			//cout << "Code for : " << c->data << " freq : " << c->freq << " --> " << s << endl;
			return;
		}
		generate_code(temp->c0, r,s + '0');
		generate_code(temp->c1,r, s + '1');
	}
	string decode(string s)
	{
		node* temp = root;
		string str;
		for (int i = 0;i < s.length();i++)
		{
			
				if (s[i] == '0')
				{
					temp = temp->c0;
				}
				else if (s[i] == '1')
				{
					temp = temp->c1;
				}
				if (temp != NULL && (temp->c0 == NULL && temp->c1 == NULL))
				{
					str = str + temp->data;
					temp = root;
				}
			
		}
		return str;
	}
};
int main()
{
	huffman h;
	ifstream file;
	file.open("wordfile.txt");
	if (file.is_open())
	{
		string sum;
		string s="";
		while (getline(file, sum))
		{
			s = s + sum;
		}
		if (s=="")
		{
			cout << "wordfile.txt is empty!" << endl;
			exit(0);
		}
		file.close();
		string w = duplicate_remove(s);
	/*	cout << "duplicate remove str  :    ";
			for (int i = 0; w[i] != '\0'; i++)
			{
				cout << w[i];
			}
			cout << endl << endl;*/
			int create_nodes = 0;
			for (int i = 0; w[i] != '\0'; i++)
			{
				create_nodes++;
			}
			node* ptr = new node[create_nodes];
			for (int i = 0; w[i] != '\0'; i++)
			{
				int count = 0;
				for (int j = 0; s[j] != '\0'; j++)
				{
					if (s[j] == w[i])
					{
						count++;
					}
				}
				ptr[i].data = w[i];
				ptr[i].freq = count;
				cout << w[i] << "  freq : " << count << endl;
			}
			cout << endl << endl;
			selection_sort(ptr, create_nodes);
			/*cout << "after s sort" << endl;
			for (int i = 0;i < create_nodes;i++)
			{

				cout << ptr[i].data << "  freq : " << ptr[i].freq << "    ";
			}
			cout << endl;*/
			h.huffman_tree(ptr, create_nodes);
			cout << "Huffman tree : " << endl;
			h.preorder(h.root);
			cout << endl << endl << endl;
			file.close();
			file.open("wordfile.txt");
			string getfile;
			ofstream filee;
			filee.open("encode.txt");
			while (getline(file, getfile))
			{
				string toencode;
				for (int i = 0;getfile[i] != '\0';i++)
				{
					h.generate_code(h.root, getfile[i]);
					cout << "char : " << getfile[i] << "     encode is : " << h.code << endl;
					toencode = toencode + h.code;
					h.code.clear();
				}
				if (filee.is_open())
				{
					filee << toencode << endl;
				}
				else
				{
					cout << "encode.txt not open" << endl;
				}
				getfile.clear();
			}
			file.close();
			filee.close();
	}
	else
	{
		cout << "word file is not open" << endl;
	}
	ifstream filed;
	filed.open("encode.txt");
	if (filed.is_open())
	{
		string encode_str;
		cout << endl << endl;
		while (getline(filed, encode_str))
		{
			cout << "decode is :  " << h.decode(encode_str) << endl;
		}
	}
	else
	{
		cout << "encode file cannot open" << endl;
	}
	filed.close();
	return 0;
}