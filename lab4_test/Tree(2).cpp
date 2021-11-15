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

/****************************************************************
 *                                  Write your code below
 ****************************************************************/

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

/*TreeNode* BinaryDimonTree::buildtree(TreeNode* m,int size,TreeNode *&T){
    int high=T->height;
    if (size == 0){
        return NULL;
    }
    else{
        TreeNode *Left = new TreeNode[size/2];
        TreeNode *Right = new TreeNode[size-size/2-1];
        int sizeleft,sizeright;
        sizeleft = size/2;
        sizeright = size - size/2 - 1;

        if (high%2 == 0){
            sort(m,m+size,cmp1);
        }
        else{
            sort(m,m+size,cmp2);
        }

    for (int i=0;i<=size/2-1;++i){
        Left[i].data[0] = m[i].data[0];
        Left[i].data[1] = m[i].data[1];
    }
    for (int i=size/2+1;i<=size-1;++i){
        Right[i - size/2 - 1].data[0] = m[i].data[0];
        Right[i - size/2 - 1].data[1] = m[i].data[1];
    }
    T = new TreeNode(m[size/2].data[0],m[size/2].data[1]);
    T->left=new TreeNode;
    T->left->height=T->height+1;
    T->right= new TreeNode;
    T->left->height=T->height+1;
    T->left = buildtree(Left,sizeleft,T->left);
    T->right = buildtree(Right,sizeright,T->right);
    delete [] Left;
    delete [] Right;
    return T;
}
}*/
TreeNode*BinaryDimonTree:: buildtree(TreeNode* n,int size,TreeNode *&a,int &high){
    int hight = high+1;
    if (size == 0){
        return NULL;
    }
    else{

        int counter;
        if (high%2 == 0){
            sort(n,n+size,cmp1);

            for (counter=0;counter<=size - 2;++counter){
                if (n[counter].data[0] == n[size/2].data[0] && n[counter+1].data[0] != n[size/2].data[0]){
                    break;
                }
            }
        }
        else{
            sort(n,n+size,cmp2);
            for (counter=0;counter<=size - 2;++counter){
                if (n[counter].data[1] == n[size/2].data[1] && n[counter+1].data[1] != n[size/2].data[1]){
                    break;
                }
            }
        }
    TreeNode *w = new TreeNode[counter];
    TreeNode *e = new TreeNode[size-counter-1];
    int sizeleft,sizeright;
    sizeleft = counter;
    sizeright = size-counter-1;

    for (int i = 0;i <= counter-1;++i){
        w[i] = n[i];
    }


    for (int i=counter+1;i<=size-1;++i){
        e[i - counter - 1] = n[i];
    }
    a = new TreeNode(n[counter].data[0],n[counter].data[1],high);
    a->left = buildtree(w,sizeleft,a->left,hight);
    hight = high + 1;
    a->right = buildtree(e,sizeright,a->right,hight);
    delete [] w;
    delete [] e;
    return a;
}
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
    tree.root=new TreeNode(m[0].data[0],m[0].data[1],0);
    tree.buildtree(m,num,tree.root,high);
    return in;
}
long long int BinaryDimonTree:: distance(TreeNode *a,TreeNode *b){
    return ((a->data[0]-b->data[0])*(a->data[0]-b->data[0])+(a->data[1]-b->data[1])*(a->data[1]-b->data[1]));
}

TreeNode *  BinaryDimonTree::find_nearest_node(int x, int y){
    TreeNode* guess=NULL;
    long long int min_distance=100000;
    TreeNode* cur;
    cur=root;
    recur_search(cur,  x,  y,  min_distance, guess);
    return guess;
}
void BinaryDimonTree::recur_search(TreeNode *cur, int x, int y, long long int &min_distance, TreeNode *&guess){
    bool flag=false;
    if(cur==NULL){
        return;
    }
    TreeNode* target=new TreeNode(x,y,0);

    if(distance(cur,target)<min_distance){
        min_distance=distance(cur,target);
        guess=cur;
    }
    else {
             if(distance(cur,target)==min_distance){
                if(cur->getX()<guess->getX()  ){
                    guess=cur;
                }
                else if(cur->getX()==guess->getX() ){
                           if(cur->getY()<guess->getY() ){
                               guess=cur;
                           }
                }
        }
    }

    if((cur->height%2)==0)  {
            if(x<cur->getX()){
                recur_search(cur->left,x,y,min_distance,guess);
                flag=true;
            }
            else recur_search(cur->right,x,y,min_distance,guess);
        }
     else{
            if(y<cur->getY()){
                recur_search(cur->left,x,y,min_distance,guess);
                flag=true;
            }
            else recur_search(cur->right,x,y,min_distance,guess);
        }



    if (cur->height%2 == 0){
        if((cur->getX() - x)*(cur->getX() - x) < min_distance){
            if (flag){
                recur_search(cur->right,x,y,min_distance,guess);
            }
            else{
                recur_search(cur->left,x,y,min_distance,guess);
            }
        }
    }
    else{
        if((cur->getY() - y)*(cur->getY() - y) <min_distance){
            if (flag){
                recur_search(cur->right,x,y,min_distance,guess);
            }
            else{
                recur_search(cur->left,x,y,min_distance,guess);
            }
        }
    }
}






