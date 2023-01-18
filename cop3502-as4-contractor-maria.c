// Maria Contractor, 5150901
// COP3502 Summer 2022
// PA4- Making and searching trees through recursion

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "leak_detector_c.h"

// Struct for the upper half of the tree
struct tree_name_node_struct
{
  char treeName[32];
  struct tree_name_node_struct *parent, *left, *right;
  struct item_node_struct *theTree;
};

typedef struct tree_name_node_struct tree_name_node;

// Struct for the bottom half of the tree
struct item_node_struct
{
  char name[32];
  int count;
  struct item_node_struct *iparent, *left, *right;
  struct tree_name_node_struct *tparent;
};

typedef struct item_node_struct item_node;

// Class Library Function: Go through s and clobber all newline characters to thr right with NULL.
void remove_crlf(char *s)
{
  char *end = s + strlen(s);
  end--;

  while((end >= s) && (*end == '\n' || *end == '\r')) {
      *end = '\0';
      end--;
  }
}

// Class Library Function: Reads the next line from ifp that isn't blank into buf, removing newlines.
int get_next_nonblank_line(FILE *ifp, char *buf, int max_length)
{
    buf[0] = '\0';

    while(!feof(ifp) && (buf[0] == '\0'))
    {

        fgets(buf, max_length, ifp);
        remove_crlf(buf);
    }

    if(buf[0] == '\0')
    {
        return 0;
    } else {
        return 1;
    }
}

/* Tree name node constructor: Creates space for the tree_name_node struct.
                               Returns the new tree_name_node struct. */
tree_name_node *new_tree_name_node(char *treename)
{
  tree_name_node *name_ptr = NULL;
  name_ptr = malloc(sizeof(tree_name_node));
  strcpy(name_ptr->treeName, treename);

  name_ptr->parent = NULL;
  name_ptr->left = NULL;
  name_ptr->right = NULL;
  name_ptr->theTree = NULL;
  return name_ptr;
}

// Function written in class.
/* Sets the left child to parent in the tree_name_node struct. */
void name_set_left_child(tree_name_node *parent, tree_name_node *child)
{
  parent->left = child;
  child->parent = parent;
}

// Function written in class.
/* Sets the right child.  Similar to set_left_child(). */
void name_set_right_child(tree_name_node *parent, tree_name_node *child)
{
  parent->right = child;
  child->parent = parent;
}

/* Fully inserts the nodes at the upper half of the tree in order. */
tree_name_node *name_bst_insert(tree_name_node *parent, tree_name_node *new_node)
{
  if (strcmp(new_node->treeName, parent->treeName) < 0)
  {  // value <; go LEFT
      if (parent->left)
      { // already a left child; RECURSIVE case.
        return name_bst_insert(parent->left, new_node);
      }
      else
      { // no left child; BASIS case.
        name_set_left_child(parent, new_node);
        return new_node;
      }
  }
  else
  { // value >=, go RIGHT
      if (parent->right)
      { // already a right child; RECURSIVE case.
        return name_bst_insert(parent->right, new_node);
      }
      else
      { // no right child; BASIS case.
        name_set_right_child(parent, new_node);
        return new_node;
      }
  }
}

/* Item node constructor: Creates space for the item_node struct.
                          Returns the new item_node struct. */
item_node *new_item_node(char *name, int count)
{
  item_node *item_ptr = NULL;
  item_ptr = malloc(sizeof(item_node));
  strcpy(item_ptr->name, name);

  item_ptr->iparent = NULL;
  item_ptr->left = NULL;
  item_ptr->right = NULL;
  item_ptr->tparent = NULL;
  item_ptr->count = count;
  return item_ptr;
}

// Function written in class.
/* Sets the left child to parent in the item_node struct. */
void item_set_left_child(item_node *iparent, item_node *child)
{
  iparent->left = child;
  child->iparent = iparent;
}
/* Sets the right child.  Similar to set_left_child(). */
void item_set_right_child(item_node *iparent, item_node *child)
{
  iparent->right = child;
  child->iparent = iparent;
}

/* Fully inserts the nodes at the lower half of the tree in order. */
item_node *item_bst_insert(item_node *iparent, item_node *new_node)
{
  if (strcmp(new_node->name, iparent->name) < 0)
  { // value <; go LEFT
      if (iparent->left)
      { // already a left child; RECURSIVE case.
        return item_bst_insert(iparent->left, new_node);
      }
      else
      { // no left child; BASIS case.
        item_set_left_child(iparent, new_node);
        return new_node;
      }
  }
  else if (strcmp(new_node->name, iparent->name) > 0)
  { // value >=, go RIGHT
      if (iparent->right)
      { // already a right child; RECURSIVE case.
        return item_bst_insert(iparent->right, new_node);
      }
      else
      { // no right child; BASIS case.
        item_set_right_child(iparent, new_node);
        return new_node;
      }
  }
}

// Helper search functions for both upper and lower half of the trees.
// Different from the ones used when processing commands.
tree_name_node *search_for_tree_node(tree_name_node *curr_tree_node, char *treeName)
{
  if (curr_tree_node == NULL)
  {
    return NULL;
  }
  int val = strcmp(treeName, curr_tree_node->treeName);
  if (val == 0)
  {
    return curr_tree_node;
  }
  else if (val < 0)
  {
    if (curr_tree_node->left != NULL)
    {
      return search_for_tree_node(curr_tree_node->left, treeName);
    }
    else
    {
      return curr_tree_node;
    }
  }
  else
  {
    if (curr_tree_node->right != NULL)
    {
      return search_for_tree_node(curr_tree_node->right, treeName);
    }
    else
    {
      return curr_tree_node;
    }
  }
}

// Item node search (Different from the one used when processing commands)
item_node *search_for_item_node(item_node *curr_item_node, char *item)
{
  if (curr_item_node == NULL)
  {
    return NULL;
  }
  int val = strcmp(item, curr_item_node->name);
  if (val == 0)
  {
    return curr_item_node;
  }
  else if (val < 0)
  {
    if (curr_item_node->left != NULL)
    {
      return search_for_item_node(curr_item_node->left, item);
    }
    else
    {
      return curr_item_node;
    }
  }
  else
  {
    if (curr_item_node->right != NULL)
    {
      return search_for_item_node(curr_item_node->right, item);
    }
    else
    {
      return curr_item_node;
    }
  }
}

/* Helper function to insert the lower half of the trees. */
void item_bst_insert_tree(tree_name_node *theTree, char *treeName, item_node *curr_item_node)
{
  tree_name_node *curr_tree_node = NULL;
  // Calls helper search function for upper half.
  curr_tree_node = search_for_tree_node(theTree, treeName);
  if (curr_tree_node->theTree == NULL)
  {
    curr_tree_node->theTree = curr_item_node;
    curr_item_node->tparent = curr_tree_node;
    return;
  }
  // Calls insert function for the lower half of trees
  item_bst_insert(curr_tree_node->theTree, curr_item_node);
}

// Prints the names in the upper half of the tree
void n_print_bintree_node(FILE *ofp, tree_name_node *b)
{
  fprintf(ofp, "%s ", b->treeName);
}

// Prints the names of the upper half of the tree for the nodes to be sorted
void n_print_bintree_node_for_nodes(FILE *ofp, tree_name_node *b)
{
  fprintf(ofp, "===%s===\n", b->treeName);
}

// Prints the names of the bottom half of the tree
void print_bintree_node(FILE *ofp, item_node *b)
{
  fprintf(ofp, "%s ", b->name);
}

// Official print function for the upper half of the tree
// Calls the helper function.
void traverse_in_order(FILE *ofp, tree_name_node *t)
{
    if(t->left) traverse_in_order(ofp, t->left);
    n_print_bintree_node(ofp, t);
    if(t->right) traverse_in_order(ofp, t->right);
}

// Helper function to print the bottom half of the tree
void traverse_in_order_node(FILE *ofp, item_node *t)
{
    if(t->left) traverse_in_order_node(ofp, t->left);
    print_bintree_node(ofp, t);
    if(t->right) traverse_in_order_node(ofp, t->right);
}

// Official print function for the bottom half of the tree
void traverse_in_order_with_node(FILE *ofp, tree_name_node *t)
{
    if(t->left) traverse_in_order_with_node(ofp, t->left);
    n_print_bintree_node_for_nodes(ofp, t);
    traverse_in_order_node(ofp, t->theTree);
    fprintf(ofp, "\n");
    if(t->right) traverse_in_order_with_node(ofp, t->right);
}

/* Shallow destructor for item node. */
void dispose_item_node(item_node *t)
{
  free(t);
}
/* Recursive destructor for item node. */
void dispose_item(item_node *t)
{
  if(t->left)
  {
    dispose_item(t->left);
  }
  if(t->right)
  {
    dispose_item(t->right);
  }
  dispose_item_node(t);
}


/* Shallow destructor for tree_name_node. Calls the item_node destructor */
void dispose_tree_node(tree_name_node *t)
{
  if (t->theTree != NULL)
  {
    dispose_item(t->theTree);
  }
  free(t);
}
/* Recursive destructor for tree_name_node. */
void dispose_tree(tree_name_node *tree)
{
  if(tree->left)
  {
    dispose_tree(tree->left);
  }
  if(tree->right)
  {
    dispose_tree(tree->right);
  }
  dispose_tree_node(tree);
}

// Beginning of Command Processing

/* Search function to find an item on the bottom half given a subtree on the upper half */
item_node *search_in_name_node(FILE *ofp, tree_name_node *curr_tree_node, item_node *curr_item_node, char *tree, char *item)
{
  if (curr_item_node == NULL)
  {
    fprintf(ofp, "%s not found in %s\n", item, curr_tree_node->treeName);
    return curr_item_node;
  }
  // Compares the name of the strings for the items
  int val = strcmp(item, curr_item_node->name);
  // match
  if (val == 0)
  {
    fprintf(ofp, "%d %s found in %s\n", curr_item_node->count, curr_item_node->name, curr_tree_node->treeName);
    return curr_item_node;
  }
  else if (val < 0)
  {
    return search_in_name_node(ofp, curr_tree_node, curr_item_node->left, tree, item);
  }
  else
  {
    return search_in_name_node(ofp, curr_tree_node, curr_item_node->right, tree, item);
  }
}

/* Search function to find an item on the upper half of the tree */
tree_name_node *search_for_name_node(FILE *ofp, tree_name_node *curr_tree_node, item_node *curr_item_node, char *tree, char *item)
{
  if (curr_tree_node == NULL)
  {
    return NULL;
  }
  // Compares the name of the strings for the tree
  int val = strcmp(tree, curr_tree_node->treeName);
  // match
  if (val == 0)
  {
    search_in_name_node(ofp, curr_tree_node, curr_tree_node->theTree, tree, item);
    return curr_tree_node;
  }
  else if (val < 0)
  {
    return search_for_name_node(ofp, curr_tree_node->left, curr_item_node, tree, item);
  }
  else
  {
    return search_for_name_node(ofp, curr_tree_node->right, curr_item_node, tree, item);
  }
}

/* Finds the amount of items lexographically before the item in the tree */
int item_before(tree_name_node *curr_tree_node, item_node *curr_item_node, char *item)
{
  int return_val = 1;
  if (curr_item_node->left)
  {
    // match
    if (strcmp(curr_item_node->left->name, item) == 0)
    {
      return return_val;
    }
    else
    {
      return_val += item_before(curr_tree_node, curr_item_node->left, item);
    }
  }
  if (curr_item_node->right)
  {
    return_val += item_before(curr_tree_node, curr_item_node->right, item);
  }
  return return_val;
}

/* Checks the height of the tree and adds to the height */
int height_tree_balance(item_node *t)
{
  // NULL reference
  if (t == NULL)
  {
    return -1;
  }
  // The height of a leaf is zero
  int left = 0;
  int right = 0;
  if(t->left)
  {
    left = height_tree_balance(t->left) + 1;
  }
  if(t->right)
  {
    right = height_tree_balance(t->right) + 1;
  }
  if(left > right)
  {
    return left;
  }
  return right;
}

/* Calls the height_tree_balance function and calculates the difference in the
   left and right heights */
int height_calculations(FILE *ofp, tree_name_node *curr_tree_node, char *tree)
{
  int left = 0;
  int right = 0;
  int difference = 0;
  // Compares the strings of the tree
  int val = strcmp(tree, curr_tree_node->treeName);

  // match
  if (val == 0)
  {
    left = height_tree_balance(curr_tree_node->theTree->left);
    right = height_tree_balance(curr_tree_node->theTree->right);

    // Difference calculation
    difference = (left - right);
    if (difference < 0)
    {
      difference *= -1;
    }
    if (difference > 1)
    {
      fprintf(ofp, "%s: left height %d, right height %d, difference %d, not balanced\n", tree, left, right, difference);
    }
    else
    {
      fprintf(ofp, "%s: left height %d, right height %d, difference %d, balanced\n", tree, left, right, difference);
    }
  }
  if (val < 0)
  {
    height_calculations(ofp, curr_tree_node->left, tree) + 1;
  }
  if (val > 0)
  {
    height_calculations(ofp, curr_tree_node->right, tree) + 1;
  }
}

/* Counts the number of items in the tree. Recurively adds and returns the value */
int count_item(item_node *curr_item_node)
{
  int val = curr_item_node->count;
  if (curr_item_node->left)
  {
    val += count_item(curr_item_node->left);
  }
  if (curr_item_node->right)
  {
    val += count_item(curr_item_node->right);
  }
  return val;
}

/* Official function to count the number of items in the tree */
int count_tree(FILE *ofp, tree_name_node *curr_tree_node, char *tree)
{
  int val = 0;
  // String is a match
  if (strcmp(curr_tree_node->treeName, tree) == 0)
  {
    // val -> number of items
    val = count_item(curr_tree_node->theTree);
    fprintf(ofp, "%s count %d\n", curr_tree_node->treeName, val);
  }
  if (curr_tree_node->left)
  {
    val += count_tree(ofp, curr_tree_node->left, tree);
  }
  if (curr_tree_node->right)
  {
    val += count_tree(ofp, curr_tree_node->right, tree);
  }
}

/* Deletes the item from the tree and adjusts each of the nodes accordingly */
void delete_item(item_node *curr_item_node)
{
  item_node *left_temp = NULL;
  item_node *right_temp = NULL;
  item_node *temp_after = NULL;
  if (curr_item_node == NULL)
  {
    return;
  }
  temp_after = curr_item_node;
  if (curr_item_node->left == NULL)
  {
    curr_item_node->left = curr_item_node->right;
  }
  else
  {
    temp_after = left_temp = curr_item_node->left;
    while(temp_after != NULL)
    {
      if (temp_after->right != NULL)
      {
        temp_after = temp_after->right;
      }
      else if (temp_after->left != NULL)
      {
        break;
      }
      else
      {
        break;
      }
    }
  }
  temp_after->right = curr_item_node->right;
  // adjusts the parent
  if (curr_item_node->right != NULL)
  {
    curr_item_node->right->iparent = temp_after;
  }
  if (curr_item_node->iparent == NULL)
  {
    if (curr_item_node->left != NULL)
    {
      curr_item_node->left->iparent = NULL;
      curr_item_node->tparent->theTree = curr_item_node->left;
    }
  }
  else
  {
    if (curr_item_node->iparent->left == curr_item_node)
    {
      curr_item_node->iparent->left = curr_item_node->left;
      if (curr_item_node->left != NULL)
      {
        curr_item_node->left->iparent = curr_item_node->iparent;
      }
    }
    else if (curr_item_node->iparent->right == curr_item_node)
    {
      curr_item_node->iparent->right = curr_item_node->left;
      if (curr_item_node->left != NULL)
      {
        curr_item_node->left->iparent = curr_item_node->iparent;
      }
    }
  }
  // frees the node that is deleted
  free(curr_item_node);
}
/* Deletes the item through the tree node. Searches for the appropriate tree name
   and item name. Calls the delete_item function */
void delete_tree_for_item(tree_name_node *curr_tree_node, char *item, char *tree)
{
  int count = 0;
  tree_name_node *tree_find = NULL;
  item_node *item_find = NULL;

  if (curr_tree_node == NULL)
  {
    return;
  }
  // searches for the appropriate tree name
  tree_find = search_for_tree_node(curr_tree_node, tree);
  if (tree_find == NULL)
  {
    return;
  }
  if (tree_find->theTree == NULL)
  {
    return;
  }
  // searches for the appropriate item name
  item_find = search_for_item_node(tree_find->theTree, item);
  if (item_find == NULL)
  {
    return;
  }
  // Calls the delete item function
  delete_item(item_find);
}

/* Deletes the whole tree and adjusts accordingly */
void delete_tree_official(tree_name_node *curr_tree_node)
{
  tree_name_node *left_temp = NULL;
  tree_name_node *right_temp = NULL;
  tree_name_node *temp_after = NULL;
  if (curr_tree_node == NULL)
  {
    return;
  }
  temp_after = curr_tree_node;
  if (curr_tree_node->left == NULL)
  {
    curr_tree_node->left = curr_tree_node->right;
  }
  else
  {
    temp_after = left_temp = curr_tree_node->left;
    while(temp_after != NULL)
    {
      if (temp_after->right != NULL)
      {
        temp_after = temp_after->right;
      }
      else if (temp_after->left != NULL)
      {
        temp_after = temp_after->left;
      }
      else
      {
        break;
      }
    }
  }
  temp_after->right = curr_tree_node->right;
  // adjusts the parent
  if (curr_tree_node->parent == NULL)
  {
    if (curr_tree_node->left != NULL)
    {
      curr_tree_node->left->parent = NULL;
    }
  }
  else
  {
    if (curr_tree_node->parent->left == curr_tree_node)
    {
      curr_tree_node->parent->left = curr_tree_node->left;
      if (curr_tree_node->left != NULL)
      {
        curr_tree_node->left->parent = curr_tree_node->parent;
      }
    }
    else if (curr_tree_node->parent->right == curr_tree_node)
    {
      curr_tree_node->parent->right = curr_tree_node->left;
      if (curr_tree_node->left != NULL)
      {
        curr_tree_node->left->parent = curr_tree_node->parent;
      }
    }
  }
  // frees the items from the deleted tree
  dispose_item(curr_tree_node->theTree);
  // frees the deleted tree accordingly
  free(curr_tree_node);
}


/* Looks for the commands and if matches, do that command. Calls all the command processing functions */
void command_cases(FILE *ofp, item_node *curr_item_node, tree_name_node *theTree, char *command, char *tree, char *item)
{
  tree_name_node *search_return = NULL;
  item_node *item_search_return = NULL;

  int return_val;
  int height_return;
  // search command
  if (strcmp(command, "search") == 0)
  {
    search_return = search_for_name_node(ofp, theTree, curr_item_node, tree, item);
    if (search_return == NULL)
    {
      fprintf(ofp, "%s does not exist\n", tree);
    }
  }
  // item_before command
  if (strcmp(command, "item_before") == 0)
  {
    return_val = item_before(theTree, theTree->theTree, item);
    fprintf(ofp, "item before %s: %d\n", item, return_val - 1);
  }
  // height_balance command
  if (strcmp(command, "height_balance") == 0)
  {
    height_calculations(ofp, theTree, tree);
  }
  // count command
  if (strcmp(command, "count") == 0)
  {
    count_tree(ofp, theTree, tree);
  }
  // delete item command
  if (strcmp(command, "delete") == 0)
  {
    delete_tree_for_item(theTree, item, tree);
    fprintf(ofp, "%s deleted from %s\n", item, tree);
  }
  // delete_tree command
  if (strcmp(command, "delete_tree") == 0)
  {
    search_return = search_for_tree_node(theTree, tree);
    delete_tree_official(search_return);
    fprintf(ofp, "%s deleted\n", tree);
  }

}

int main (void)
{
  // atexit(report_mem_leak);
  FILE *ifp;
  FILE *ofp;
  char buf[256];
  char tree_name[100];
  char insert_tree_name[100];
  char insert_item_name[100];
  int insert_item_count;
  int num_trees;
  int num_items;
  int num_commands;
  int i, j, k;
  tree_name_node *main_tree = NULL;
  tree_name_node *new_node = NULL;
  item_node *item_tree = NULL;
  item_node *item_node = NULL;

  char command[100];
  char tree[100];
  char item[100];
  // open input file
  ifp = fopen("cop3502-as4-input.txt", "r");
  // writes output file
  ofp = fopen("cop3502-as4-output-contractor-maria.txt", "w");
  get_next_nonblank_line(ifp, buf, 255);
  sscanf(buf, "%d %d %d", &num_trees, &num_items, &num_commands);
  // makes a tree for the upper half
  for (i = 0; i < num_trees; i++)
  {
    get_next_nonblank_line(ifp, buf, 255);
    sscanf(buf, "%s", tree_name);
    new_node = new_tree_name_node(tree_name);
    if (i == 0)
    {
      main_tree = new_node;
    }
    else
    {
      name_bst_insert(main_tree, new_node);
    }
  }
  // makes a tree for the bottom half
  for (j = 0; j < num_items; j++)
  {
    get_next_nonblank_line(ifp, buf, 255);
    sscanf(buf, "%s %s %d", insert_tree_name, insert_item_name, &insert_item_count);
    item_node = new_item_node(insert_item_name, insert_item_count);
    item_bst_insert_tree(main_tree, insert_tree_name, item_node);
  }
  // prints the upper and lower trees accordingly
  traverse_in_order(ofp, main_tree);
  fprintf(ofp, "\n");
  traverse_in_order_with_node(ofp, main_tree);

  // command process
  fprintf(ofp, "=====Processing Commands=====\n");
  for (i = 0; i < num_commands; i++)
  {
    get_next_nonblank_line(ifp, buf, 255);
    sscanf(buf, "%s %s %s", command, tree, item);
    command_cases(ofp, item_node, main_tree, command, tree, item);
  }
  // frees all memory leaks (items and trees)
  dispose_tree(main_tree);
  // close the files
  fclose(ifp);
  fclose(ofp);
}
