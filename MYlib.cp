#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <set>
#include <string.h>
#include "MYlib.h"

using namespace std;


//----------------------------------------------------URL Class----------------------------------------------------------------
URL::URL(char *url,int depth) {
    this->set_url(url);
    this->set_visit(0);
    this->set_depth(depth);
}

char* URL::get_url() {
    return this->url;
}

void URL::set_url(char *url) {
    int i=0,len=0;
    for(int p=0; url[p]!='\0'; p++) {
        len++;
    }
    this->url=new char[len+2];
    memset(this->url,0,len+1);
    for(i=0; url[i]!='\0'; i++) {
        this->url[i]=url[i];
    }
    this->url[i]='\0';
 }

 int URL::get_depth() {
    return this->depth;
 }

 void URL::set_depth(int depth) {
    this->depth=depth;
 }

 int URL::get_visit() {
    return this->visit;
 }

 void URL::set_visit(int visit) {
    this->visit=visit;
 }

//------------------------------------------------------------NODE Class----------------------------------------------------------

 Node::Node(int depth,int key,char *url) {
    URL *n=new URL(url,depth);
    this->set_add(n);
    file_name=NULL;
    this->set_key(key);
    this->set_next(NULL);
}

void Node::set_add(URL *add) {
    this->add=add;
}

URL* Node::get_add() {
    return this->add;
}

int Node::get_key() {
    return this->key;
}

void Node::set_key(int key) {
    this->key=key;
}

void Node::set_next(Node *next) {
    this->next=next;
}

Node* Node::get_next() {
    return this->next;
}

char* Node::get_file_name() {
    return this->file_name;
}

void Node::set_file_name(char *file_name) {
    int len=0,i=0;
    for(i=0; file_name[i]!='\0'; i++) {
        len++;
    }
    this->file_name= new char[len+2];
    memset(file_name,0,len+1);
    for(i=0; file_name[i]!='\0'; i++) {
        this->file_name[i]=file_name[i];
    }
    this->file_name[i]='\0';
}

//------------------------------------------------------Hash Class----------------------------------------------------------------

Hash::Hash() {
    this->set_hash();
}

void Hash::set_hash() {
    for(int i=0; i<100; i++) {
        this->set_table(i,NULL);
    }    
}

void Hash::set_table(int i,Node *ptr) {
    this->table[i]=ptr;
}

Node* Hash::get_table(int i) {
    return this->table[i];
}

int Hash::key(char *a) {
    int len=0;
    for(int i=0; a[i]!='\0'; i++) {
        len++;
    }
    return len%100;
}

//--------------------------------------------------------Linklist Class--------------------------------------------------------

Linklist::Linklist(){
    head=NULL;
    h1=new Hash();
}

void Linklist::set_head(Node *head) {
    this->head=head;
}

Node* Linklist::get_head() {
    return this->head;
}

void Linklist::Add_Node(int depth ,char *url) {
    if(depth!=0&&page::getSpider(url)) 
    {
        int key=h1->key(url);
        if(this->get_head()==NULL) {
            Node *n=new Node(depth,key,url);
            h1->set_table(key,n);
            this->set_head(n);
        } else {
            if(this->get_head()->get_key()>key) {
                Node *n=new Node(depth,key,url);
                h1->set_table(key,n);
                n->set_next(this->get_head());
                this->set_head(n);
            } else {
                Node *ptr=this->get_head();
                for(int i=0; i<=key; i++) {
                    if(h1->get_table(i)!=NULL) {
                        ptr=h1->get_table(i);
                    }
                }
                if(h1->get_table(key)==NULL) {
                    Node *n=new Node(depth,key,url);
                    h1->set_table(key,n);
                    if(ptr->get_next()!=NULL) {
                        while(ptr->get_next()!=NULL) {
                            if(ptr->get_next()->get_key()>key) {
                                break;
                            }
                            ptr=ptr->get_next();
                        }
                        n->set_next(ptr->get_next());
                        ptr->set_next(n);
                    } else {
                        ptr->set_next(n);
                    }
                } else {
                    if(ptr->get_next()==NULL) {
                        if(strcmp(url,ptr->get_add()->get_url())==0) {
                            //ptr->get_add()->set_visit(2);
                        } else {
                            Node *n=new Node(depth,key,url);
                            ptr->set_next(NULL);
                        }
                    } else {
                        int flag=0;
                        while (ptr->get_next()!=NULL) {
                            if(strcmp(url,ptr->get_add()->get_url())==0) {
                                flag=1;
                              //  ptr->get_add()->set_visit(2);
                            } else {
                                if(ptr->get_next()->get_key()>key) {
                                    break;
                                }
                            }
                            ptr=ptr->get_next();
                        }
                        if(flag==0) {
                            if(strcmp(url,ptr->get_add()->get_url())!=0) {
                                Node *n=new Node(depth,key,url);
                                n->set_next(ptr->get_next());
                                ptr->set_next(n);
                            }else{
                              //ptr->get_add()->set_visit(2);
                            }
                        }
                    }
                }
            }
        }
    }
}
/*
Node* Linklist::Visit_Nodes() {
    while(1){
        Node *ptr=this->get_head();
        int flag=0;
        while(ptr!=NULL) {
            if(ptr->get_add()->get_visit()==0&&ptr->get_add()->get_depth()>0) {
                ptr->get_add()->set_visit(1);
                return ptr;
            }
            ptr=ptr->get_next();
        }
        ptr=this->get_head();
        while(ptr!=NULL) {
            if(ptr->get_add()->get_visit()==2&&ptr->get_add()->get_depth()>0) {
                ptr->get_add()->set_visit(1);
                flag=1;
                return ptr;
            }
            ptr=ptr->get_next();
        }
        if(flag==0){
            break;
        }
    }
  return NULL;
}
*/

Node* Linklist::Visit_Nodes() {
        Node *ptr=this->get_head();
        while(ptr!=NULL) {
            if(ptr->get_add()->get_visit()==0&&ptr->get_add()->get_depth()>0) {
                ptr->get_add()->set_visit(1);
                return ptr;
            }
            ptr=ptr->get_next();
        }
        return NULL;
    }
//------------------------------------------------------Dictionary Class----------------------------------------------------

dictionary::dictionary(string type){
    if(type=="relevant")
        file.open("/root/crawlerdir/dictionary.txt",ios::in | ios::binary);
    else if(type=="ignore")
        file.open("/root/crawlerdir/ignore.txt",ios::in | ios::binary);
    loadWords();
}
    
    
void dictionary::addWord(string word){
    d.insert(word);
}
    
int dictionary::findWord(string word)
{
    if(d.find(word)==d.end())
        return 0;
    return 1;
}
    
void dictionary::loadWords(){
    for (string line; getline(file, line);) {
      d.insert(line);
    }
}
    
void dictionary::updateFile(string word){
    file.close();
    ofstream nfile;
    if(word=="relevant")
        nfile.open("/root/crawlerdir/dictionary.txt");
    else if(word=="ignore")
        nfile.open("/root/crawlerdir/ignore.txt");
    set <string>::iterator it;
    for(it=d.begin();it!=d.end();it++)
       {
           char *c = new char[(*it).length() + 1];
           strcpy(c, (*it).c_str());
           nfile<<c<<endl;
           delete [] c;
       }
}
    
void dictionary::updateDictionary(char* buffer, dictionary& ign){
    char* content = page :: getContentBuffer(buffer);
    const char s[8] = " ,|-:/\\";
    char *token;
    token = strtok(content, s);
    while( token != NULL ) 
    {
        for(int i=0;i<strlen(token);i++)
        token[i]=tolower(token[i]);
        if(!ign.findWord(token))
            this->addWord(token);
        token = strtok(NULL, s);
    }
}

//-----------------------------------------Page Class--------------------------------------------------------------
char* page::getContentBuffer(char *buffer)
{
    string b=buffer;
    string content="";
    size_t pos=b.find("<title>");
    size_t pos2,endp=b.length();
    
    pos+=7;
    while(b[pos]!='<')
        content+=b[pos++];
    pos=0;
    while(pos<endp)
        {
            content+=" ";
            pos=b.find("<meta",pos);
            if(pos>endp)
                break;
            pos2=b.find(">",pos);
            if(b.find("description",pos)<pos2||b.find("keywords",pos)<pos2||b.find("Description",pos)<pos2||b.find("Keywords",pos)<pos2)
            {
                pos=b.find("content",pos);
                pos+=10;
                while(b[pos]<'"')
                    content+=b[pos++];
            }
            pos=pos2;
        }
    char *c = new char[content.length() + 1];
    strcpy(c, content.c_str());
return c;
}

int page::getrelevance(char* buffer, dictionary& rel, dictionary& ign)
{
	int weight=0;
	char* content= page::getContentBuffer(buffer);
	const char s[3] = " |";
    char *token;
    token = strtok(content, s);
    while(token != NULL ) 
    {
        for(int i=0;i<strlen(token);i++)
            token[i]=tolower(token[i]);
        cout<<token<<" ";
        if(!ign.findWord(token))
                if(rel.findWord(token))
                    weight++;
        token = strtok(NULL, s);
        if(weight>=0)
		    return 1;
    }
		
return 0;
}




int page::getSpider(char *url)
{
    char s[URL_LENGTH+20];
    memset(s,0,URL_LENGTH+20);
    strcat(s,"wget -q --spider -T 10 --timeout=10 ");
    strcat(s,url);
    std::cout<<s<<std::endl;
    if(!system(s))
    return 1;
    else
    return 0;
}

char* page::toBuffer() {
    std::ifstream file;
    file.open("/root/crawlerdir/temp.txt",std::ios::in | std::ios::binary);
    file.seekg(0,std::ios::end);
    int len=file.tellg();
    char *s=new char[len+1];
    memset(s,0,len+1);
    file.seekg(0,std::ios::beg);
    int i=0;
    while(!file.eof()) {
        char temp;
        file>>std::noskipws>>temp;
        s[i++]=temp;
    }
    s[i-1]='\0';
    return s;
}

void page::save(Node *ptr,char* temp_data) {
    static int num;
    char name[100]="/root/crawlerdir/";
    char temp[10];
    if(ptr->get_file_name()==NULL) {
        sprintf(temp,"%d",num);
        strcat(name,"file");
        strcat(name,temp);
        strcat(name,".txt");
        std::ofstream file;
        file.open(name);
        file<<ptr->get_add()->get_url()<<std::endl;
        file<<ptr->get_add()->get_depth()<<std::endl;
        file<<temp_data;
        num++;
        file.close();
    }
    else {
        strcat(name,ptr->get_file_name());
        std::ofstream file;
        std::ifstream temp_file,old_file;
        temp_file.open("/root/crawlerdir/temp.txt");
        old_file.open(name);

        if(isChanged(temp_file, old_file))
        {
            old_file.close();
            temp_file.close();
            file.open(name,std::ios::trunc);
            file<<ptr->get_add()->get_url()<<std::endl;
            file<<ptr->get_add()->get_depth()<<std::endl;
            file<<temp_data;
            file.close();
        }
        else {
            old_file.close();
            temp_file.close();
        }
    }
}

void page::normalizeUrl(string &s)
{
    int len=s.length(),i;
    i=len-1;
    while(s[i--]=='.');
    string l="";
    while(i<len)
        l+=s[i++];
    if(!(l!=".php"||l!=".jsp")||s[0]=='?'||!s.find("timeanddate",0)|| !s.find("mail",0)||!s.find("ftp",0)||!s.find("blog",0)||!s.find("_",0)||!s.find("accounts",0)||!s.find("account",0)||!s.find("Account",0)||!(s.find(".",0)<len))
    {
        s="NAN";
    }
}


int page::isChanged(std::ifstream& newfile, std::ifstream& oldfile)
{
    std::string nbuffer,obuffer;
    int npos,opos;
    npos=opos=0;
    getBufferFromFile(newfile, nbuffer);
    getBufferFromFile(oldfile, obuffer);
    if(titleChanged(nbuffer, obuffer, &npos, &opos))
        return 1;
    else if(metaChanged(nbuffer, obuffer, &npos, &opos))
        return 1;
    return 0;
}

int page::metaChanged(std::string nbuffer, std::string obuffer, int* npos, int* opos)
{
    while(nbuffer[*npos]!=EOF||obuffer[*opos]!=EOF)
    {
        *npos = nbuffer.find("<meta", *npos);
        *opos = nbuffer.find("<meta", *npos);
        while(nbuffer[*npos]!='>'||obuffer[*opos]!='>')
            if(nbuffer[*npos++]!=obuffer[*opos++])
                return 1;
    }
    return 0;
}

int page::titleChanged(std::string nbuffer, std::string obuffer, int* npos, int* opos)
{
    *npos = nbuffer.find("<title", *npos);
    *opos = nbuffer.find("<title", *npos);
    while(nbuffer[*npos]!='<'||obuffer[*opos]!='<')
        if(nbuffer[*npos++]!=obuffer[*opos++])
            return 1;
    return 0;
}

void page::getBufferFromFile(std::ifstream& f,std::string &s) {
    char a;
    while(!f.eof()) {
        f>>std::noskipws>>a;
        s+=a;
    }
}

//this function return a set with all the
//urls contained in a file
std::set<std::string> page::getAllURLs(std::string currentUrl,char* b)
{
    std::set<std::string> urls;
    std::string buffer;
    for(int in=0; in<strlen(b); in++)
        buffer+=b[in];
    std::size_t pos = 0,endp= buffer.length();
    //position of the first anchor tag
    pos=(buffer.find("<a",pos))<(buffer.find("<A",pos))?(buffer.find("<a",pos)):(buffer.find("<A",pos));
    int count=0;
    while(buffer[pos]!=EOF&&pos<endp)
    {
        std::string result="";
        //Now we don't know if the href in the anchor tag we've got is lower case or not so..
        pos=(buffer.find("href",pos))<(buffer.find("HREF",pos))?(buffer.find("href",pos)):(buffer.find("HREF",pos));
        int tpos=(buffer.find("</a",pos))<(buffer.find("</A",pos))?(buffer.find("</a",pos)):(buffer.find("</A",pos));
        if(tpos>pos)
        {
            while(buffer[pos]!='"'&&buffer[pos]!='\'')
                pos++;
            pos++;
            std::string testUrl="";

            while(buffer[pos]!='"'&&buffer[pos]!='\'')
                testUrl+=buffer[pos++];

            if(testUrl!="")
            {
                if(testUrl[0]=='/'&&testUrl[1]=='/')
                {
                    result+="https:";
                    result+=testUrl;
                }
                else if(testUrl[0]=='/')
                {
                    int i;
                    for(i=8; i<currentUrl.length(); i++)
                        if(currentUrl[i]=='/')
                            break;
                    for(int j=0; j<i; j++)
                        result+=currentUrl[j];
                    result+=testUrl;
                }
                else
                {
                    result+=testUrl;
                }
                //the url we've recieved is not necessarily in the standard form in which we want to save our urls so we
                //normalise it
                normalizeUrl(result);
                if(result!="NAN")//&&check_page(result))
                    urls.insert(result);
                if(urls.size()>20)
                    break;
            }
        }
        pos=(buffer.find("<a",pos))<(buffer.find("<A",pos))?(buffer.find("<a",pos)):(buffer.find("<A",pos));

    }
    return urls;
}

//-------------------------------------------------------Common Fuctions---------------------------------------------------------

void commonfuntions::testDir(char *dir)
{
    struct stat statbuf;
    if ( stat(dir, &statbuf) == -1 )
    {
        fprintf(stderr, "-----------------\n");
        fprintf(stderr, "Invalid directory\n");
        fprintf(stderr, "-----------------\n");
        exit(1);
    }

    //Both check if there's a directory and if it's writable
    if ( !S_ISDIR(statbuf.st_mode) )
    {
        fprintf(stderr, "-----------------------------------------------------\n");
        fprintf(stderr, "Invalid directory entry. Your input isn't a directory\n");
        fprintf(stderr, "-----------------------------------------------------\n");
        exit(1);
    }

    if ( (statbuf.st_mode & S_IWUSR) != S_IWUSR )
    {
        fprintf(stderr, "------------------------------------------\n");
        fprintf(stderr, "Invalid directory entry. It isn't writable\n");
        fprintf(stderr, "------------------------------------------\n");
        exit(1);
    }
}

//|Checks whether the given parameters are the correct amount 
int commonfuntions::checkPara(int a)
{
    if(a!=4)
        return 0;
    else
        return 1;
}

//|Checks depth given in the argv
int commonfuntions::checkDepth(char a[])
{
    int i=a[0];
    int b=a[0]-48;
    if(b>4||i<48||i>57)
        return 0;
    else
        return 1;
}

//|Checks if given URL is matches the BASEURL
int commonfuntions::checkURL(char a[])
{
    int i,flag=0;
    for(i=0; i<strlen(a); i++)
    {
        if(a[i]!=BASE_URL[i]||a[i]=='\0') //| Checking URL per character
        {
            //cout<<BASE_URL<<endl;
            //cout<<a<<endl;
            return 0;
        }
    }
    return 1;
}

//| Gets page from the internet using wget and stores in a temporary file
void commonfuntions::getPage(char *url)
{
    char urlbuffer[URL_LENGTH+300]={0};
    strcat(urlbuffer, "wget ");
    strcat(urlbuffer, url);
    strcat(urlbuffer," -O /root/crawlerdir/temp.txt ");
    system(urlbuffer); //| Calls the system fucntion to execute wget command
}

