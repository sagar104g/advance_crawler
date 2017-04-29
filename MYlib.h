

#ifndef _MYLIB_H_
#define _MYLIB_H_
#define HASH_SIZE 100
#define URL_LENGTH 1000
#define BASE_URL "http://www.youtube.com/"
#define BASE_LENGTH 23


class URL {
private:
    char *url;
    int visit;
    int depth;
public:
    URL( char*, int);
	char* get_url();
    void set_url( char*);
    int get_depth();
    void set_depth( int);
    int get_visit();
	void set_visit( int);
};

class Node {
private:
    URL *add;
    char *file_name;
    int key;
    Node *next;
public:
    Node( int, int, char*);
    void set_add( URL*);
    URL* get_add();
    int get_key();
    void set_key( int);
    void set_next( Node*);
    Node* get_next();
    char* get_file_name();
    void set_file_name( char*);
};

class Hash {
private:
    Node *table[100];
public:
    Hash();
    void set_hash();
    void set_table( int, Node*);
    Node* get_table( int);
    int key( char*);
};

class Linklist {
private:
    Hash *h1;
    Node *head;
public:
    Linklist();
    void set_head( Node*);
    Node* get_head();
    void Add_Node( int, char*); 
    Node* Visit_Nodes();
};

//-------------------------------------------------------------------------------------------------

//| Class Dictionary: Maintains a dictionary of words
class dictionary{
private:
    std::set <std::string> d;                    //| Set of all words in dictionary
    std::ifstream file;                          //| Dictionary in the sec. memory
    
public:
    dictionary(std::string);                     //| Initializes and constructs disctionary based on string parameter
    void addWord(std::string);                   //| Adds a word to the dictionary
    int findWord(std::string);                   //| Finds the given word in the dictionary and return true or false
    void loadWords();                            //| Reads from sec. memory and loads in a set datastructure
    void updateFile(std::string);                //| Updates the file with new words after execution
    void updateDictionary(char*, dictionary&);   //| Updates the set with new words during execution
};

//------------------------------------------------------------------------------------------------

//| Class Page: Page manipulation functions are preset in the class
class page {                 
public:
    static char* toBuffer();                                       //| Creates and returns buffer from temp file downloaded
    static void save(Node*,char*);                                 //| Saves the relevant file in the sec.memory
    static void normalizeUrl(std::string&);                        //| Normalizes URL to check if valid or not
    static int isChanged(std::ifstream&, std::ifstream&);          //| Checks if page structure has been changed since we last visited
    static int metaChanged( std::string, std::string, int*, int*); //| Helping functions for isChanged() and checks if meta has changed
    static int titleChanged( std::string, std::string, int*, int*);//| Helping functions for isChanged() and checks if title has changed
    static void getBufferFromFile( std::ifstream&, std::string&);  //| Gets buffer from file for other functions to use
    static std::set<std::string> getAllURLs(std::string, char*);   //| Returns a set of normalized URLS extracted from a page
    static int getrelevance(char*, dictionary&, dictionary&);      //| Return if page is relevant or not
    static char* getContentBuffer(char *);                         //| Returns a buffer with content from title and meta tags
    static int getSpider(char*);                                   //| Checks if page is valid or not through spider
};


//-------------------------------------------------------------------------------------------------

//| Utility class to be used by other classes
class commonfuntions{

public:
    static void testDir(char*);          //|Tests the directory given by user in argv is existing and writable
    static int checkPara(int);           //| Checks the number of parameters in argv
    static int checkDepth(char*);        //| Checks the depth given by user
    static int checkURL(char*);          //| Checks whether given URL is equal to BASEURL
    static void getPage(char *);         //| Downloads the page from given URL
};

#endif
