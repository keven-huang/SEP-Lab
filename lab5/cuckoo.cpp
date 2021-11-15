#include "cuckoo.h"
#include<iostream>
using namespace std;
Hash_map::Hash_map(){
        size = 8;
        table0 = new Node [size];
        table1 = new Node [size];
    }
Hash_map::~Hash_map(){
    delete []table0;
    delete []table1;
}
void Hash_map::kick(node t){
    for(int i = 0;i < size;i++){
        int pos1 = h1(t.key);
        if(table0[pos1].state == 0){
            table0[pos1].data = t;
            table0[pos1].state =1;
            return;
        }
        node th1 = table0[pos1].data;
        table0[pos1].data = t;
        cout<<"Kick "<<th1.key<<" with "<<t.key<<" in table 0 "<<pos1<<endl;
        int pos2 = h2(th1.key);
        if(table1[pos2].state == 0){
            table1[pos2].data =th1;
            table1[pos2].state = 1;
            return;
        }
        else{
            node th1h2 = table1[pos2].data;
            table1[pos2].data = th1;
            cout<<"Kick "<<th1h2.key<<" with "<<th1.key<<" in table 1 "<<pos2<<endl;
            t = th1h2;
        }
    }
    cout<<"Loop Detect"<<endl;
    rehash(t);
}
