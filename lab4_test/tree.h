//
// Created by Smile on 2019/4/8.
//

#ifndef C_BINARYDIMEN_TREE_H
#define C_BINARYDIMEN_TREE_H

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/

class TreeNode
{
  friend ostream &operator<<(ostream &out, const TreeNode &b);
  friend class BinaryTree;
  friend class BinaryDimonTree;

private:
  /* data */

public:
  /* methods */
  TreeNode *left,*right;
  int level;
  int data[2];
  TreeNode(int x =0,int y=0,int lev=0,TreeNode *l=nullptr,TreeNode *r=nullptr):left(l),right(r){
      data[0] = x;
      data[1] = y;
      level = lev;
  }
  int getX();  /* DO NOT CHANGE */
  int getY();  /* DO NOT CHANGE */
  ~TreeNode(); /* DO NOT CHANGE */
};


class BinaryDimonTree
{
friend istream &operator>>(istream &in, BinaryDimonTree &tree); /* DO NOT CHANGE */
friend int distance(TreeNode *a,TreeNode*b);
private:
  /* data */
  TreeNode *root;

public:
  /* methods */

  BinaryDimonTree();          /* DO NOT CHANGE */
  TreeNode *find_nearest_node(int x, int y);  /* DO NOT CHANGE */
  TreeNode* build(TreeNode * i,int l,int r,TreeNode *&t,int lev);
  /*void insert(int &x,int &y){
      insert(x,y,root,0);
  }
  void insert(int &x,int &y,TreeNode *&t,int i){
      if(t==nullptr) {t = new TreeNode(x,y,i); return;}
      if(i%2==0){
          if(x<t->getX()) insert(x,y,t->left,i+1);
          else insert(x,y,t->right,i+1);
      }
      else{
          if(y<t->getY()) insert(x,y,t->left,i+1);
          else insert(x,y,t->right,i+1);
      }
  }*/
  void Empty(TreeNode *t);
  void recur_search(TreeNode *cur, int x, int y, long long int &min_distance, TreeNode *&guess);
 ~BinaryDimonTree();
};

int distance(TreeNode *a,TreeNode*b);
#endif //C_BINARYDIMEN_TREE_H
