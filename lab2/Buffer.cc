#include <fstream>
#include <iostream>
#include "Buffer.h"
#include<algorithm>
//TODO: your code here
//implement the functions in ListBuffer

Buffer::Buffer() {
    head = new node;
    head->next = nullptr;
    currentLineNum = CurrentLen = 0;
}

Buffer::~Buffer() {
    node *p = head ->next;
    while(p!=nullptr){
        node *tmp = p;
        p=p->next;
        delete tmp;
    }
    head->next = nullptr;
}

void Buffer::writeToFile(const string &filename) const {
    if(filename.empty()) throw "Filename not specified";
    else{
        std::ofstream outfile(filename);
        size_t bitnum = 0;
        node *p = head->next;
        while (p!=nullptr) {
            outfile<<p->data<<std::endl;
            bitnum+=p->data.size();
            p=p->next;
        }
        bitnum+=CurrentLen;
        outfile.close();
        std::cout<<bitnum<<" byte(s) written"<<std::endl;
    }
}

void Buffer::showLines(int from, int to) {
    if(from > to) throw std::range_error("Number range error");
    else if(to > CurrentLen||from<=0) throw std::out_of_range("Line number out of range");
    else{
        node *p = head;
        currentLineNum = from;
        int tmp = to - from;
        while (from-->=1) p = p->next;
        while(tmp-->=0){
            std::cout<<currentLineNum++<<'\t'<<p->data<<std::endl;
            p = p->next;
        }
        currentLineNum = to;
    }
}

void Buffer::deleteLines(int from, int to){
    if(from > to) throw std::range_error("Delete range error");
    else if(to > CurrentLen||from<=0) throw std::out_of_range("Line number out of range");
    else{
        if(CurrentLen==to-from+1) currentLineNum = 0;
        else if(to==CurrentLen) currentLineNum = from-1;
        else currentLineNum = from;
        node *p = head;
        int tmp = to - from;
        while (from -- >= 2) p = p->next;
        while(tmp-->=0){
            node * deltmp = p->next;
            p->next = p->next->next;
            delete deltmp;
            --CurrentLen;
         }
    }
}

void Buffer::insertLine(const string &text){
    if(currentLineNum==0) currentLineNum = 1;
    int tmp = currentLineNum;
    node *p=head;
    while(tmp-->=2) p=p->next;
    node *new_n = new node;
    new_n->data = text;
    new_n->next = p->next;
    p->next = new_n;
    ++CurrentLen;
}

void Buffer::appendLine(const string &text){
    int tmp = currentLineNum;
    node *p=head;
    while(tmp-->=1) p=p->next;
    node *new_n = new node;
    new_n->data = text;
    new_n->next = p->next;
    p->next = new_n;
    CurrentLen+=1;
    currentLineNum +=1;
}

const string &Buffer::moveToLine(int idx) {
    if(idx<=0||idx>CurrentLen) throw std::out_of_range("Line number out of range");
    currentLineNum = idx;
    node *p = head;
    while(idx-->=1) p=p->next;
    return p->data;
}
