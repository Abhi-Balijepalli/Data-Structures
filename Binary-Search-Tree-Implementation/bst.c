/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include<stdio.h>

#include "bst.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  struct bst* bst = (struct bst*)malloc(sizeof(struct bst));
  bst->root = NULL;
  return bst;
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
  bst_free2(bst->root);
  free(bst);
}
void bst_free2(struct bst_node* bst){
  if(bst != NULL) {
    bst_free2(bst->left);
    bst_free2(bst->right);
    //free(bst);
    bst = NULL;
  }
  //free(bst);
}

int bst_count(struct bst_node* bst){
  if(bst == NULL) {
    return 0;
  } else {
    //struct bst_node* node = bst->root;
    return(bst_count(bst->left)+1 +bst_count(bst->right)); 
  }
}
/*
 * This function should return the total number of elements stored in a given
 * BST.
 *s
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
  return bst_count(bst->root);
}



/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
  struct bst_node* N = N = bst->root;
  struct bst_node* P =  NULL;
  if (N != NULL) { 
    while(N != NULL) {
      P = N;
      if(key < N->key) {
        N = N->left;
      } else {
        N = N->right;
      }
    }
  N = (struct bst_node*)malloc(sizeof(struct bst_node));
   N->key = key;
   N->value = value;
   //printf(" Key:(%d): ", key);
   //printf(" value:(%d)\n: ", value);
   N->left = NULL;
   N->right = NULL;
    if(N->key < P->key) {
     P->left = N;
   } //else if (N->key >= P->key) {
   else {
      P->right = N;
    }
  }
  else {
    //struct bst_node* KMS = (struct bst_node *)malloc(sizeof(struct bst_node));
    bst->root = (struct bst_node *)malloc(sizeof(struct bst_node));
    bst->root->key = key;
   // printf(" Checking the Key value:(%d): ", key);
    bst->root->value = value;
    bst->root->left = NULL;
    bst->root->right = NULL;
    //bst->root = KMS;
    free(bst->root);
  }

  //return 0 ;
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
  struct bst_node* parent = NULL;
  struct bst_node* N = bst->root;
  while(N != NULL) {
    parent = N;
    if(N->key == key) {
      break;
    } else if (key < N->key) {
      N = N->left;
    } else {
      N = N->right;
    }
  }
   //printf("N(1)'s key: %d",N->key);
  // case #1 no children
  if (N->left == NULL && N->right == NULL) {
      free(N);
      return;
  } 

  //case #2 1 child
  else if (N->left !=NULL && N->right==NULL) {
      parent = N->left; 
      free(N);
  }
  else if (N->left ==NULL && N->right!=NULL) {
      parent = N->right;
      free(N);
  }

  // case #3 2 children 
  else {
      struct bst_node* S = N;
      S = N->right;
      while(S != NULL) {

        if(S->left == NULL) {
          break;
        }
        S = S->left;
      }
      struct bst_node *Ps;
      if(N != bst->root){
      Ps = N;  
      }
      else{
        Ps = N->right;
      }

      S->left = N->left;
      if (S != N->right) {
        Ps->left = S->right;
        S->right = N->right;
      }
      if(parent->left == N){
        parent->left = S;
      }
      if(bst->root == N){
        bst->root = S;
      }
      free(N);
      
      //N->right = S;
    } 
  free(N); 
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
  struct bst_node* N = bst->root;
  //printf("N's key: %d /n", N->key);
  while(N != NULL) {
    if(N->key == key) {
      return N->value;
    } else if (key < N->key) {
      N = N->left;
    } else {
      N = N->right;
    }
  }
  free(N);
  return NULL;
}


