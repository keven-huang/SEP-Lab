#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>

#include "tree.h"

using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/
ostream &operator<<(ostream &out, const TreeNode &b){
    out<<b.data[0]<<" "<<b.data[1]<<endl;
    return out;
}
int TreeNode::getX(){
    return data[0];
}
int TreeNode::getY(){
    return data[1];
}
bool cmp1(TreeNode a,TreeNode b){
    return a.data[0]<b.data[0];
}
bool cmp2(TreeNode a,TreeNode b){
    return a.data[1]<b.data[1];
}
TreeNode * BinaryDimonTree::build(TreeNode * i,int l,int r,TreeNode *&t,int lev){
    if (l-r > 0) return nullptr;
    int counter = (l+r)/2;
    if (lev%2 == 0) sort(i+l,i+r+1,cmp1);
    else sort(i+l,i+r+1,cmp2);
    t = new TreeNode(i[counter].data[0],i[counter].data[1],lev);
    t->left = build(i,l,counter-1,t->left,lev+1);
    t->right = build(i,counter+1,r,t->right,lev+1);
    return t;
}
istream &operator>>(istream &in, BinaryDimonTree &tree){
    int N;
    in>>N;
    TreeNode *input = new TreeNode[N];
    for (int i=0;i<N;++i){
            in>>input[i].data[0];
            in>>input[i].data[1];
        }
    tree.build(input,0,N-1,tree.root,0);
    return in;
}

BinaryDimonTree::BinaryDimonTree(){
    root = nullptr;
}
long long distance(TreeNode *a,int x,int y){
    return pow(a->getX()-x,2)+pow(a->getY()-y,2);
}
TreeNode* BinaryDimonTree::find_nearest_node(int x, int y){
    long long int max = distance(root,x,y)+10;
    TreeNode *ans = nullptr;
    recur_search(root,x,y,max,ans);
    return ans;
}

void BinaryDimonTree::recur_search(TreeNode *cur, int x, int y, long long int &min_distance, TreeNode *&guess){
    if(cur == nullptr) return;
    if(distance(cur,x,y)<min_distance){
        min_distance = distance(cur,x,y);
        guess = cur;
    }
    if(distance(cur,x,y)==min_distance){
        if(guess->getX()>cur->getX()) guess = cur;
        else if(guess->getX()==cur->getX()&&cur->getY()<guess->getY())
            guess = cur;
    }
    int i = cur->level;
    bool flag = false;
    if(i%2==0){
        if(x<cur->getX()) {
            recur_search(cur->left,x,y,min_distance,guess);flag = true;
        }
        else recur_search(cur->right,x,y,min_distance,guess);
    }
    else{
        if(y<cur->getY()) {recur_search(cur->left,x,y,min_distance,guess);flag = true;}
        else recur_search(cur->right,x,y,min_distance,guess);
    }
    if (i%2 == 0){
            if((cur->getX()-x)*(cur->getX()-x) < min_distance){
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
void BinaryDimonTree::Empty(TreeNode *t){
    if(t==nullptr) return;
    Empty(t->left);
    Empty(t->right);
    delete t;
}
BinaryDimonTree::~BinaryDimonTree(){
    Empty(root);
}
TreeNode::~TreeNode(){
}
