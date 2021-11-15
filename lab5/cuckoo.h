#ifndef CUCKOO_H
#define CUCKOO_H
using namespace std;
#include <iostream>
struct node{
    int key,value;
    node(int k ,int v){key = k;value =v;}
    node(){}
};
class Hash_map{
    struct Node{
        node data;
        int state;
        Node(){state = 0;}
    };
    int size;
    Node *table0,*table1;
    int h1(int key){return key%size;}
    int h2(int key){return (key/size)%size;}
public:
    Hash_map();
    ~Hash_map();
    void rehash(node t){
        Node *t0 = table0;
        Node *t1 = table1;
        size *= 2;
        table0 = new Node [size];
        table1 = new Node [size];
        for(int i = 0;i<size/2;i++){
            if(t0[i].state!=0) insert(t0[i].data.key,t0[i].data.value);
        }
        for(int i = 0;i<size/2;i++)
            if(t1[i].state!=0) insert(t1[i].data.key,t1[i].data.value);
        insert(t.key,t.value);
    }
    void kick(node t);
    void insert(int k,int v){
        node t(k,v);
        int pos1 = h1(k);
        if(table0[pos1].state == 0){
            table0[pos1].data = t;
            table0[pos1].state = 1;
            return;
        }
        int pos2 = h2(k);
        if(table1[pos2].state == 0){
            table1[pos2].data = t;
            table1[pos2].state = 1;
            return;
        }
        kick(t);
        return;
    }
    void find(int k){
        int pos1 = h1(k),pos2 = h2(k);
        if(table0[pos1].state==1&&table0[pos1].data.key == k){
            cout<<table0[pos1].data.value<<endl;
            return;
        }
        else if(table1[pos2].state==1&&table1[pos2].data.key==k){
            cout<<table1[pos2].data.value<<endl;
            return;
        }
        else{
            cout<<"Key Not Found"<<endl;
            return;
        }
    }
    void delet(int k){
        int pos1 = h1(k),pos2 = h2(k);
        if(table0[pos1].state==1&&table0[pos1].data.key == k){
            table0[pos1].state = 0;
            return;
        }
        else if(table1[pos2].state==1&&table1[pos2].data.key==k){
            table1[pos2].state = 0;
            return;
        }
        else{
            cout<<"Key Not Found"<<endl;
            return;
        }
    }
};

#endif // CUCKOO_H
