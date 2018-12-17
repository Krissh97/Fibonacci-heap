#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include<stdlib.h>
using namespace std;
struct node {
	  int data,degree;
	  struct node *next,*prev,*parent,*child;
	  bool childcut=false;
	};
void meld(node *,node *);
void inserttolist(node *);
void increasekey(node *,int);
void removemax(node *);
map<string,node*> myMap;
map<string,node *> maxtable;
map<int,node*> degreetable;
node *head=NULL; node *before;node *maxpointer;
void removemax()     //For removing the max and restructuring
{
    node *maxpointer1;
    node *gotonode,*temp;
    if(maxpointer->degree==0){      //if maxpointer has no children.
    maxpointer1=maxpointer->next;
    while(maxpointer1->next!=maxpointer){       //to traverse through root nodes
            temp=maxpointer1->next;
            maxpointer1->next=NULL;
            maxpointer1->prev=NULL;
	    maxpointer1->parent=NULL;
            map<int,node*>::iterator i = degreetable.find(maxpointer1->degree);
		if(i == degreetable.end()){
             degreetable.insert(pair<int,node*>(maxpointer1->degree, maxpointer1));
             maxpointer1=temp;
             }
             else{
                   gotonode= i->second;
                degreetable.erase(i);
             meld(maxpointer1,gotonode);
             maxpointer1=temp;
             }
    }
            map<int,node*>::iterator i = degreetable.find(maxpointer1->degree);
             maxpointer1->next=NULL;
            maxpointer1->prev=NULL;
		if(i == degreetable.end()){

             degreetable.insert(pair<int,node*>(maxpointer1->degree, maxpointer1));
             }
             else{
                   gotonode= i->second;
                degreetable.erase(i);
                gotonode->next=NULL;
                gotonode->prev=NULL;
		gotonode->parent=NULL;
             meld(maxpointer1,gotonode);
             }
             head=NULL;
             for (auto& t : myMap){
        if(maxpointer==t.second)
            {
                maxpointer->child=NULL;
                maxpointer->next=NULL;
                maxpointer->prev=NULL;
		maxpointer->parent=NULL;
            maxpointer->degree=0;
           maxtable.insert(pair<string,node *>(t.first, maxpointer));
            }
   }
             maxpointer=NULL;
             for (auto& t : degreetable){
             inserttolist(t.second);
             }
    degreetable.clear();
    }
    else{       //if maxpointer has 1 or more children
            degreetable.clear();
            head=NULL;
            before=NULL;
        node *maxpointer2=maxpointer;
        node *temp1,*temp2,*temp3,*temp4;
        temp1=maxpointer2->child;
        temp2=maxpointer2->next;
        if(maxpointer2->degree==1){     //if maxpointer has 1 child
             temp1->next=NULL;
                temp1->prev=NULL;
                temp1->parent=NULL;
           map<int,node*>::iterator i = degreetable.find(temp1->degree);
		if(i == degreetable.end()){
             degreetable.insert(pair<int,node*>(temp1->degree, temp1));
             }
             else{
                   gotonode= i->second;
                degreetable.erase(i);
                gotonode->next=NULL;
                gotonode->prev=NULL;
		gotonode->parent=NULL;
             meld(temp1,gotonode);
             }
        }
        else{           //if maxpointer has 2 or more children.
        while(temp1->next!=maxpointer2->child){     //traversing through child nodes of maxpointer.
                temp4=temp1;
        temp1=temp1->next;
                temp4->next=NULL;
                temp4->prev=NULL;
                temp4->parent=NULL;
               map<int,node*>::iterator i = degreetable.find(temp4->degree);
		if(i == degreetable.end()){
             degreetable.insert(pair<int,node*>(temp4->degree, temp4));
             }
             else{
                   gotonode= i->second;
                degreetable.erase(i);
                gotonode->next=NULL;
                gotonode->prev=NULL;
		gotonode->parent=NULL;
             meld(temp4,gotonode);
             }
        }
        temp1->parent=NULL;
                        temp1->next=NULL;
                temp1->prev=NULL;
           map<int,node*>::iterator i = degreetable.find(temp1->degree);
		if(i == degreetable.end()){

             degreetable.insert(pair<int,node*>(temp1->degree, temp1));
             }
             else{
                   gotonode= i->second;
                degreetable.erase(i);
                gotonode->next=NULL;
                gotonode->prev=NULL;
             meld(temp1,gotonode);
             }
        }
        if(temp2!=NULL){
        while(temp2!=maxpointer2){      //traversing through neighbor nodes of maxpointer.
            temp3=temp2;
            temp2=temp2->next;
                temp3->next=NULL;
                temp3->prev=NULL;
		temp3->parent=NULL;
               map<int,node*>::iterator i = degreetable.find(temp3->degree);
		if(i == degreetable.end()){
             degreetable.insert(pair<int,node*>(temp3->degree, temp3));
             }
             else{
                   gotonode= i->second;
                degreetable.erase(i);
             meld(temp3,gotonode);

             }
        }
        }
        head=NULL;
        for (auto& t : myMap){
        if(maxpointer==t.second)
            {
                maxpointer->child=NULL;
                maxpointer->next=NULL;
                maxpointer->prev=NULL;
            maxpointer->degree=0;
	    maxpointer->childcut=false;
           maxtable.insert(pair<string,node *>(t.first, maxpointer));       //inserting the removed nodes into maxtable.

            }
   }
             maxpointer=NULL;
             for (auto& t : degreetable){       //inserting all the remaining root nodes after inserting from degreetable hashmap.
             inserttolist(t.second);}
        }
}
void meld(node *maxpointer1,node *gotonode){
    node *thenode;
    node *temppp;
    node *tempppp;
if(maxpointer1->data>gotonode->data){       //condition for if 1st node is greater than 2nd node.
        maxpointer1->degree=maxpointer1->degree+1;
        gotonode->parent=maxpointer1;
        if(maxpointer1->degree==1){         //if 1st node's degree is initially 0 then just insert 2nd node as child.
        maxpointer1->child=gotonode;
        gotonode->next=gotonode;
        gotonode->prev=gotonode;
        }
        else if(maxpointer1->degree==2){     //if 1st node's degree is initially 1 then insert 2nd node to next pointer of 1st node's child node.
            maxpointer1->child->next=gotonode;
            gotonode->prev=maxpointer1->child;
            gotonode->next=maxpointer1->child;
            maxpointer1->child->prev=gotonode;
        }
        else{                           //if 1st node's degree is greater than 2, then insert 2nd node to next pointer of child
            temppp=maxpointer1->child;
            tempppp=maxpointer1->child->next;
            temppp->next=gotonode;
            gotonode->prev=temppp;
            gotonode->next=tempppp;
            tempppp->prev=gotonode;
        }
        map<int,node*>::iterator i = degreetable.find(maxpointer1->degree);
		if(i == degreetable.end()){                 //insert the node in degreetable if no other node with that degree exists.
             degreetable.insert(pair<int,node*>(maxpointer1->degree, maxpointer1));
             }
             else{              //if a node with same degree already exists in degreetable, meld that node and the new node.
                   thenode= i->second;
                degreetable.erase(i);
             meld(maxpointer1,thenode);
             }
}
else{                                   //condition for if 2nd node is greater than 1st node.
    gotonode->degree=gotonode->degree+1;
    maxpointer1->parent=gotonode;
    if(gotonode->degree==1){            //if 2nd node's degree is initially 0 then just insert 1st node as child.
        gotonode->child=maxpointer1;
        maxpointer1->next=maxpointer1;
        maxpointer1->prev=maxpointer1;
        }
        else if(gotonode->degree==2){        //if 2nd node's degree is initially 1 then insert 1st node to next pointer of 1st node's child node.
                gotonode->child->next=maxpointer1;
            maxpointer1->prev=gotonode->child;
            maxpointer1->next=gotonode->child;
            gotonode->child->prev=maxpointer1;
        }
        else{                               //if 2nd node's degree is greater than 2, then insert 1st node to next pointer of child
            temppp=gotonode->child;
            tempppp=gotonode->child->next;
            temppp->next=maxpointer1;
            maxpointer1->prev=temppp;
            maxpointer1->next=tempppp;
            tempppp->prev=maxpointer1;
        }
    map<int,node*>::iterator i = degreetable.find(gotonode->degree);
		if(i == degreetable.end()){         //insert the node in degreetable if no other node with that degree exists.

             degreetable.insert(pair<int,node*>(gotonode->degree, gotonode));
             }
             else{                      //if a node with same degree already exists in degreetable, meld that node and the new node.
                   thenode= i->second;
                degreetable.erase(i);
             meld(gotonode,thenode);

             }
}
}
void inserttolist(node *store)
{
 if(head==NULL)         //if head is NULL, insert the node and head,before and maxpointer initially point to that node.
 {
     head=store;
     before=store;
     maxpointer=before;
 }
 else{              //if head exists, the before pointer always points to last inserted node. Insert the new node after before pointer and maxpointer points to maximum value.
       before->next=store;
        store->prev=before;
        before=store;
       before->next=head;
        head->prev=before;
        if(store->data>maxpointer->data){
            maxpointer=before;
        }
 }
}
void cascadingcut(node *store){
    node *temp,*temp1;
    temp=store;
    temp1=store;
    if(temp1->parent!=NULL){		//if parent exists for node we are in.
            if(temp1->childcut==false){	//if childcut field of present node is false.
                temp1->childcut=true;
            }
            else{		//if chilldcut field of present field is true.

    temp1->parent->degree=temp1->parent->degree-1;
    temp=temp1->parent;
    if(temp->degree==0){	//if current node's degree is 0.
        temp1->next=NULL;
        temp1->prev=NULL;
        temp1->parent=NULL;
        temp1->childcut=false;
        inserttolist(temp1);
    }
    else if(temp->degree==1){	//if current node's degree is 1.
    temp1->next->next=NULL;
    temp1->next->prev=NULL;
    temp->child=temp1->next;
    temp1->next=NULL;
    temp1->prev=NULL;
    temp1->parent=NULL;
    temp1->childcut=false;
    inserttolist(temp1);
    }
    else if(temp->degree>1){	//if current node's degree is 2 or more.
    temp1->prev->next=temp1->next;
        temp1->next->prev=temp1->prev;
        if(temp->child==temp1){	//if child pointer of parent is pointing to node we are about to move.
            temp->child=temp1->next;
                    }
        temp1->next=NULL;
        temp1->prev=NULL;
        temp1->parent=NULL;
        temp1->childcut=false;
        inserttolist(temp1);}
        cascadingcut(temp);
            }
}
}
void increasekey(node *store,int n){
    node *tell=store->parent;
if(store->parent==NULL){	//if current node's parent is NULL.
    store->data=store->data+n;
    if(maxpointer->data<store->data){	//if updated node's data becomes greater than it's parent data.
        maxpointer=store;
    }
    }
else if(store->parent->degree==1){	//if degree of updated node's parent node is 1
           store->data=store->data+n;
           if(store->data>store->parent->data){		//if updated node's data is greater than that of it's parent
    store->parent->degree=0;
    store->parent->child=NULL;
    store->parent=NULL;
    store->next=NULL;
            store->prev=NULL;
            store->childcut=false;
    inserttolist(store);
    cascadingcut(tell);
	   }
}
else if(store->parent->degree==2){		//if degree of updated node's parent node is 2
store->data=store->data+n;
        if(store->data>store->parent->data){		//if updated node's data is greater than that of it's parent
        store->parent->degree=1;
        store->next->next=NULL;
                store->next->prev=NULL;
        store->parent->child=store->next;
        store->next=NULL;
        store->prev=NULL;
        store->parent=NULL;
        store->childcut=false;
        inserttolist(store);
        cascadingcut(tell);
        }
}
else if(store->parent->degree>2){	//if degree of updated node's parent node is greater than 2
    store->data=store->data+n;
    if(store->data>store->parent->data){	//if updated node's data is greater than that of it's parent
            store->parent->degree=store->parent->degree-1;
        store->prev->next=store->next;
        store->next->prev=store->prev;
        if(store->parent->child==store){	//if parent node's child pointer is pointing at node we are about to move.
            store->parent->child=store->next;
                            }
            store->next=NULL;
            store->prev=NULL;
            store->parent=NULL;
            store->childcut=false;
            inserttolist(store);
        cascadingcut(tell);
        }

}
}
node *create(int myValue)
{
		node *n=new node;
		n->data=myValue;
		n->degree=0;
		n->next=NULL;
		n->prev=NULL;
		n->parent=NULL;
		n->child=NULL;
}
int main(int argc, char **argv) {

	string myKey;
	int myValue;
	string outfile="output_filekc.txt";
	node *store;
 	ofstream outputfile;
        outputfile.open(outfile, std::ofstream::out | std::ofstream::app);
	ifstream file (argv[1]);
	if (file.is_open()){
		file>> myKey;
		while(myKey!="stop"){
		if(myKey[0]=='$')       //if 1st char of string is $
		{
			file>> myValue;
			map<string,node*>::iterator i = myMap.find(myKey.substr(1));
			if(i == myMap.end()){	//if string is new
				store=create(myValue);
				myMap.insert(pair<string,node*>(myKey.substr(1), store));
				inserttolist(store);
			}
			else{	//if string already exists
                		store=i->second;
                		increasekey(store,myValue);
			}
		}	
		else{           //if input is an integer
            		int a= stoi(myKey);
       			if(outputfile.is_open()){
        		for(int i=1;i<=a;i++){
            		degreetable.clear();
            		for (auto& t : myMap){
        		if(maxpointer==t.second && i!=a)
            		{
            			outputfile<<t.first <<",";
            		}
            		else if(maxpointer==t.second && i==a)
               		{        outputfile<<t.first <<" ";
            		}	

   		}	
           	removemax();
       	 }
        outputfile<<endl;
	}
	for (auto& t : maxtable){       //after displaying max, insert all removed nodes back into structure.
   		inserttolist(t.second);
	}
	maxtable.clear();
   }
    file>>myKey;
	}
	return 0;
	}
}
