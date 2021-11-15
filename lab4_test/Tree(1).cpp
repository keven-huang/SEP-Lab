#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>
#include "Tree.h"
using namespace std;

TreeNode::TreeNode(int m,int n,int H){
    data[0]=m;
    data[1]=n;
    height=H;
}
int TreeNode::getX(){
    return data[0];
}
int TreeNode::getY(){
    return data[1];
}
ostream &operator<<(ostream &out, const TreeNode &b){
    out<<b.data[0]<<" "<<b.data[1]<<endl;
    return out;
}
BinaryDimonTree::BinaryDimonTree(){}
BinaryDimonTree::~BinaryDimonTree(){
    queue<TreeNode*>que;
    que.push(root);
    TreeNode * cur;
    TreeNode *del;
    while(!que.empty()){
        cur=que.front();
        que.pop();
        if(cur->left!=NULL) que.push(cur->left);
        if(cur->right!=NULL) que.push(cur->right);
        del=cur;
        delete del;
    }
}

bool cmp1(TreeNode a,TreeNode b){
    return a.data[0]<b.data[0];
}
bool cmp2(TreeNode a,TreeNode b){
    return a.data[1]<b.data[1];
}

TreeNode*BinaryDimonTree:: buildtree(TreeNode* n,int l,int r,TreeNode *&a,int &high){
    int hight = high+1;
    if (l-r > 0) return NULL;
    int counter = (l+r)/2;
    if (high%2 == 0) sort(n+l,n+r+1,cmp1);
    else sort(n+l,n+r+1,cmp2);
    a = new TreeNode(n[counter].data[0],n[counter].data[1],high);
    a->left = buildtree(n,l,counter-1,a->left,hight);
    a->right = buildtree(n,counter+1,r,a->right,hight);
   // cout<< a->getX()<<' '<<a->getY()<<' '<<high<<endl;//a->left->getX()<<' '<<a->left->getY()<<'  '<<a->right->getX()<<' '<<a->right->getY()<<endl;
    return a;
}


istream &operator>>(istream &in, BinaryDimonTree &tree){
    int num;
    in>>num;
    TreeNode *m = new TreeNode[num];
    for (int i=0;i<num;++i){
        in>>m[i].data[0];
        in>>m[i].data[1];
    }
    int high=0;
    tree.buildtree(m,0,num-1,tree.root,high);
    //cout<<tree.root->getX()<<' '<<tree.root->getY()<<' '<<tree.root->height<<endl;
    return in;
}

long long BinaryDimonTree:: distance(TreeNode *a,TreeNode *b){
    return ((long long)(a->data[0]-b->data[0])*(a->data[0]-b->data[0])+(long long)(a->data[1]-b->data[1])*(a->data[1]-b->data[1]));
}

TreeNode *  BinaryDimonTree::find_nearest_node(int x, int y){
    TreeNode* guess=NULL;
    long long min_distance=(long long)(root->getX()-x)*(root->getX()-x)+(long long)(root->getY()-y)*(root->getY()-y)+100;
    TreeNode* cur;
    cur=root;
    recur_search(cur,  x,  y,  min_distance, guess);
    return guess;
}

void BinaryDimonTree::recur_search(TreeNode *cur, int x, int y, long long &min_distance, TreeNode *&guess){
    bool flag=false;
    if(cur==NULL) return;
    TreeNode* target=new TreeNode(x,y,0);

    //cout<<cur->getX()<<' '<<cur->getY()<<endl;
    if(distance(cur,target)<min_distance)
    {
        //cout<<distance(cur,target)<<endl;
        //cout<<min_distance<<endl;
        min_distance=distance(cur,target);
        guess=cur;
    }
    else if(distance(cur,target)==min_distance)
    if ((cur->getX()<guess->getX())||(cur->getX()==guess->getX() && cur->getY()<guess->getY())) guess=cur;
    if((cur->height%2)==0){
    if(x<cur->getX())
    {
        recur_search(cur->left,x,y,min_distance,guess);
        flag=true;
    }
    else recur_search(cur->right,x,y,min_distance,guess);}

    if((cur->height%2)==1){
    if(y<cur->getY())
    {
        recur_search(cur->left,x,y,min_distance,guess);
        flag=true;
    }
    else recur_search(cur->right,x,y,min_distance,guess);}


    if (cur->height%2 == 0){
        //cout<<cur->getX()<<' '<<cur->getY();cout<<flag<<endl;
        if((cur->getX() - x)*(cur->getX() - x) < min_distance){
            if (flag) recur_search(cur->right,x,y,min_distance,guess);
            //cout<<cur->getX()<<' '<<cur->getY();cout<<'u'<<endl;
            else recur_search(cur->left,x,y,min_distance,guess);
        }
    }
    else{
        if((cur->getY() - y)*(cur->getY() - y) < min_distance){
            if (flag) recur_search(cur->right,x,y,min_distance,guess);
            else recur_search(cur->left,x,y,min_distance,guess);
        }
    }
    delete target;
}






