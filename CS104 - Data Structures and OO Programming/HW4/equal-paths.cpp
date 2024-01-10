#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


int depth(Node * root){
    if (root->left == NULL && root->right == NULL){
        return 0;
    } else if (root->right == NULL){
        return depth(root->left) + 1;
    } else if (root->left == NULL){
        return depth(root->right) + 1;
    }
    int right = depth(root->right);
    int left = depth(root->left);
    if (right > left){
        return right + 1;
    } else {
        return left + 1;
    }
}


bool equalPaths(Node * root)
{
    if (root == NULL){
        return true;
    } else if ((root->left == NULL) && (root->right == NULL)){
        return true;
    } else if (root->right == NULL){
        return equalPaths(root->left);
    } else if (root->left == NULL){
        return equalPaths(root->right);
    }
    return ((equalPaths(root->left) && equalPaths(root->right)) && (depth(root->left) == depth(root->right)));

}

