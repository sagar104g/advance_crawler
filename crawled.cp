#include <iostream>
#include <string.h>
#include <set>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include "MYlib.h"

using namespace std;


int main(int argc, char *argv[])
{
    if(commonfuntions::checkDepth(argv[2]) && commonfuntions::checkURL(argv[1]) && commonfuntions::checkPara(argc)){
        commonfuntions::testDir(argv[3]);
        Linklist url_driver;
        dictionary rel("relevant");
        dictionary ign("ignore");
        rel.loadWords();
        ign.loadWords();
        int depth=argv[2][0]-'0';
        url_driver.Add_Node(depth,argv[1]);
        while(1)
        {
           Node *ptr=url_driver.Visit_Nodes(); 
           if(ptr!=NULL)
           {
                cout<<"-----------------------------------------------------------------------------"<<endl<<endl;
            	cout<<ptr->get_add()->get_url()<<endl;
            	cout<<"-----------------------------------------------------------------------------"<<endl<<endl;
                commonfuntions::getPage(ptr->get_add()->get_url());
                char* buffer=page::toBuffer();
                if(page::getrelevance(buffer,rel,ign))
                    {
                    rel.updateDictionary(buffer, ign);
                    set<string>urls=page::getAllURLs(ptr->get_add()->get_url(),buffer);
                    set<string>::iterator iter;
                    for(iter=urls.begin(); iter!=urls.end(); ++iter) {
                        string a=*iter;
                        cout<<a<<endl;
                        char* url=new char[a.length()+2];
                        memset(url,0,a.length()+1);
                        int i=0;
                        for(i=0; i<a.length(); i++) {
                            url[i]=a[i];
                        }
                        url[i]='\0';
                        url_driver.Add_Node(ptr->get_add()->get_depth()-1,url);
                        delete url;
                    }
                    page::save(ptr,buffer);
                    delete buffer;
                }
                else
                cout<<"irrelavent";
           }
           else
           {    
                rel.updateFile("relevant");
                Node *ptr=url_driver.get_head();
        while(ptr!=NULL) {
               cout<<ptr->get_add()->get_url()<<endl<<ptr->get_add()->get_visit()<<endl;
               if(ptr->get_next()==NULL)
               cout<<"null"<<endl;
            ptr=ptr->get_next();
        }
                cout<<"-----------------------------------------------------------------------------"<<endl<<endl;
            	cout<<"----------------EXITED NORMALLY!---------------------------------------------------"<<endl<<endl;
            	cout<<"-----------------------------------------------------------------------------"<<endl<<endl;
                break;
           }
        }
    }
    
    else{
        cout<<"Exit Check Parameters"<<endl;
    }
    return 0;
}



