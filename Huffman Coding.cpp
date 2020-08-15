#include<bits/stdc++.h>
using namespace std;
#define fast ios::sync_with_stdio(0);

class node                                  //node
{
  public:
  int v;
  char c;
  node * lft,* rht;

  node(int a,char b){v=a;c=b;lft=rht=NULL;}
    node(){}
  
};
class writingob
{
  public:
    unsigned int byte4;
    writingob(int t)
    {
      byte4=t;
    }
    writingob()
    {

    }
};

struct greaters                         // comparator
{
  bool operator()(const node *a,const node * b) 
  {
    return a->v<b->v;
  }
};


class huff                              // huffman ds
{
    public:
    node *root;
    string s,ens;
    multiset<node *,greaters> v1;
    map<char,string> hfcd;
    map<char, int> cnt;

    node * root1(){return root;}
    huff(){s="geeksforgeeks";ens="";root=NULL;}
    void get();
    void getByfile(string);
    void count();
    void buildtree();
    void printhfcd();
    void printens();
    string printdes(node * root);
    void printPaths(node* root);
    void printArray(int ints[], int len,char c);
    void printPathsRecur(node* node, int path[], int pathLen);
    void clear();
};
void huff::clear()
{
    root=NULL;
    hfcd.clear();
    v1.clear();
    cnt.clear();
    s="",ens="";

}
void huff::get()
{
    cin>>s;
}
string huff::printdes(node * root)           //// print decoded string
{   
    string ans = ""; 
    node* curr = root;
    int l=ens.length(); 
    for(int i=0;i<l;i++) 
    { 
        if (ens[i] == '0') 
           curr = curr->lft; 
        else
           curr = curr->rht; 
  
        // reached leaf node 
        if (curr->lft==NULL and curr->rht==NULL) 
        { 
            ans += curr->c; 
            curr = root; 
        } 
    } 
    cout<<"\ndecoded string \n";
    cout<<ans<<endl; 
    return ans; 
}
void huff::printens()              // print encoded string
{
    int slen=s.length();
    cout<<"\nEncoded string\n";   //      encoded string    
    //string ens="";
    for (int i = 0; i < slen; ++i)
    {
        ens+=hfcd[s[i]];
    }
    cout<<ens<<"\n";
}
void huff::printhfcd()       // printing  Huffman coded value for charecters 
{
    buildtree();
    printPaths(root);
    
    cout<<"\nHuffman coded value for charecters\n";   // huffman cooded value for characters
    
    cout<<"\n***************\n";
    for(auto it=hfcd.begin();it!=hfcd.end();it++)
    {  
      cout<<it->first<<" "<<it->second<<"\n";
    }
    
}
void huff::buildtree()               //      Huffman coded value for charecters
{
     int l=cnt.size();

    //cout<<"\ntraversal for Huffman coding\n";   // traversal of hfcd
    while(l>1)
    {   
        /*
        for(auto i =v1.begin();i!=v1.end();i++)
        cout<<(*i)->v<<" ";
        */
        multiset<node *>::iterator it; 
        it=v1.begin();
        node * t1=*(it);
        node * new1=new node();
        new1->lft= t1;

        
        v1.erase(it);

        it=v1.begin();
        node * t2=*(it);
        new1->rht= t2;
    
        
        v1.erase(it);
        new1->v=t1->v+t2->v;
    
    
        v1.insert(new1);
    
        
    l--;
    }
    root=*(v1.begin());
    //cout<<(*(v1.begin()))->v<<"\n";
}
void huff::count()              //      count
{
    
    int slen=s.length();
    for (int i = 0; i < slen; ++i)
    {
        cnt[s[i]]++;
    }

    for(auto it=cnt.begin();it!=cnt.end();it++)
    {  
        node * x=new node(it->second,it->first);
        v1.insert(x);
    }
    
    cout<<"\nFrequency count\n";          //  frequency count
    
    for(auto i =v1.begin();i!=v1.end();i++)
        cout<<(*i)->v<<" "<<(*i)->c<<"\n";
    
}

void huff::printArray(int ints[], int len,char c)  // print paths from root
{
    int i;
    string s="";
    for (i = 0; i <= len; i++)
    {
       // cout << ints[i] << " ";
        if(ints[i]==0)  s+='0';
        else    s+='1';
        
    }
    hfcd[c]=s;
    
}
void huff:: printPathsRecur(node* node, int path[], int pathLen)  // print paths from root
{
    if (node == NULL)
        return;

    if (node->lft == NULL && node->rht == NULL)
    {
       // cout<<node->c<<" char\n";
        printArray(path, pathLen,node->c);
    }
    else
    {
     
        pathLen++;path[pathLen] = 0;
        printPathsRecur(node->lft, path, pathLen);  path[pathLen] = 1;
        printPathsRecur(node->rht, path, pathLen);  
    }
}
void huff:: printPaths(node* node)     // print all paths from root
{
    int path[1000];
    printPathsRecur(node, path, -1);
}

void f1()
{
    #ifndef ONLINE_JUDGE
    // for getting input from input.txt
    freopen("input.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output.txt", "w", stdout);
    #endif  
}
void huff::getByfile(string fn)
{
    //file should exist
    ifstream filehandler;
    filehandler.open("input.txt");
    string res="";
    while(filehandler)
    {
      string ts;
      getline(filehandler,ts);
      res=res+'\n'+ts;
    }
    s=res;
    filehandler.close();
}
unsigned int cnv_stringbyte_to_int(string s)
{
    unsigned int a=0;
    int l=s.length();
    for(int i=0;i<l;i++)
    {
        if(s[i]=='1')
        {
            a=(a|1);
        }
        if(i<(l-1))
            a=(a<<1);
    }
    
    return a;
}

string cnv_intto_bytestring(unsigned int a,int l,int cs)
{
    string res="";
    int t=cs+32;
    
    if(t>l)
        l=l-cs;
    else  
        l=32;
    for(int i=0;i<l;i++)
    {
        int t=(a&1);
        if(t)res=res+'1';
        else res=res+'0';
        a=(a>>1);
    }

    reverse(res.begin(),res.end());
    return res;
}

int main()
{
  
    huff ob;
    writingob wo;

    int l=1,ch;
    while(l==1)
    {
        cout<<"Enter 1:to convert string to Huffman code\nEnter 2:to convert file data to Huffman code\nEnter 0:to exit()\n";
        cin>>ch;
        switch(ch)
        {
            case 0:exit(0);break;
            case 1:
                ob.get();
                ob.count();
                ob.printhfcd();
                ob.printens();
                ob.printdes(ob.root1());
                ob.clear();
                break;
            case 2:
              {
                string fn;
                cout<<"Enter file name"<<endl;
                cin>>fn;
                ob.getByfile(fn);
                ob.count();
                ob.printhfcd();
                ob.printens();
                ob.printdes(ob.root1());
                
                
                int l=ob.ens.length();
                fstream fio; 
                fio.open("encoded_file.txt", ios::out | ios::in|ios::binary); 
                
                for(int i=0;i<l;i+=32)
                {
                    string s;
                    if(i+32>l)
                     s=ob.ens.substr(i,min(l-i,32));
                    else
                        s=ob.ens.substr(i,32);
        
                    unsigned int t=cnv_stringbyte_to_int(s);
        
                    wo.byte4=t;
                    fio.write((char *) &wo,sizeof(writingob)); 
                }

                
                fio.seekg(0, ios::beg); 
                string byteString="";
                writingob ro;
                for(int i=0;i<l;i+=32)
                {
                    fio.read((char *) &ro,sizeof(writingob));
                    string ret=cnv_intto_bytestring(ro.byte4,l,i);
                    byteString+=ret;
                }
                ob.ens=byteString;
                string des=ob.printdes(ob.root1());
                fio.close();
                ofstream fout;
                fout.open("decodded_file.txt");
                fout<<des;
                fout.close();
                ob.clear();
              }
        }
    }
  return 0;
}
