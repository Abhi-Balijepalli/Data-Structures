## Implement a binary search tree

Your main task for this assignment is to implement a [binary search tree](https://en.wikipedia.org/wiki/Binary_search_tree) (BST).  A BST is a tree-structured data type that allows fast insertions, lookups, and removals by structuring itself in a way that encodes the behavior of binary search.  Specifically, each node in a BST has at most two children, a left child and a right child, and every node satisfies the BST property, which requires that all values stored in a node's left subtree must be less than that node's value, while all values stored in a node's right subtree must be greater than or equal to that node's value.

For this assignment, the interface for the BST you'll implement (i.e. the structures and the prototypes of functions a user of the BST interacts with) is already defined for you in the file `bst.h`.  Your first task in this assignment is to implement definitions for the functions that comprise this interface in `bst.c`.

**Note that you may not modify the interface definition with which you are provided.**  Specifically, do not modify any of the already-defined BST function prototypes.  We will use a set of tests to verify your implementation, and if you change the BST interface, it will break these tests, thereby (negatively) affecting your grade.  You may also not modify any of the existing structures defined in the starter code (i.e. `struct bst` and `struct bst_node`).  Beyond these things, though, feel free to add any additional functions or structures your BST implementation needs.

The BST functions you'll need to implement are outlined briefly below.  All of these functions use a type called `struct bst`, which is defined in `bst.c` and represents the BST itself.  For more details, including information on function parameters and expected return values, see the documentation provided in `bst.c`.

  * **`bst_create()`** - This function should allocate, initialize, and return a pointer to a new BST structure.

  * **`bst_free()`** - This function should free the memory held within a BST structure created by `bst_create()`.  Note that this function only needs to free the memory held by the BST itself.  It does not need to free the individual elements stored in the BST.  This is the responsibility of the calling function.

  * **`bst_size()`** - This function should return the total number of elements stored in a given BST.  Importantly, because you can't modify the fields of `struct bst` or `struct bst_node`, you'll have to calculate a BST's size each time this function is called.  *It could be helpful to think recursively here.*  Feel free to write any helper functions you need to make this work.

  * **`bst_insert()`** - This function should insert a new key/value pair into a given BST.  The BST should be ordered based on the specified key value.  In other words, your BST must always maintain the BST property among all keys stored in the tree.

  * **`bst_remove()`** - This function should remove the value with a specified key from a given BST.  If multiple values are stored in the tree with the same key, the first one encountered (i.e. the one closest to the root of the tree) should be removed.

  * **`bst_get()`** - This function should return the value associated with a specified key in a given BST.  If multiple values are stored in the tree with the same key, the first one encountered (i.e. the one closest to the root of the tree) should be returned.

## Storing key/value pairs

It is important to note that each data element stored in your BST will actually consist of two parts: a key and a value.  Under this scheme, the key will serve as a unique identifier for the data element, while the value will represent the rest of the data associated with that element.  For example, if you were storing information about OSU students in your BST, the key for each student element might be that student's OSU ID number, while the corresponding value might be a struct containing all other data related to that student (e.g. name, email address, GPA, etc.).  Storing data as key/value pairs is a common approach that we'll see in other data structures we explore in this course.

For your BST implementation, each data element's key will be represented as an integer value, while the associated value will be a void pointer.  This is reflected in the structure you must use to represent a single node in your BST:
```C
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};
```

Your BST should be organized *based on the keys* of the elements.  In other words, the BST property must always hold among all *keys* in the tree.  For example, when a new data element is inserted into your BST, decisions about whether to insert that element within a node's left subtree or its right subtree should be based on comparisons between the key of the element being inserted and the keys stored in the tree.  Similarly, when a user wants to lookup or remove data elements stored in your BST, they will do so by specifying the key to be found/removed.
