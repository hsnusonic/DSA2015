#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

extern "C" {
#include "avl.h"
#include "bst.h"
#include "rb.h"
}

using namespace std;

void predoder_string_avl(const struct avl_node *node) {
  if (node == NULL)
    return;
  printf ("%s ", (char *)node->avl_data);
  if (node->avl_link[0] != NULL || node->avl_link[1] != NULL) {
    putchar('(');
    predoder_string_avl(node->avl_link[0]);
    putchar(',');
    putchar(' ');
    predoder_string_avl(node->avl_link[1]);
    putchar(')');
  }
}

void predoder_string_bst(const struct bst_node *node) {
  if (node == NULL)
    return;
  printf ("%s ", (char *)node->bst_data);
  if (node->bst_link[0] != NULL || node->bst_link[1] != NULL) {
    putchar('(');
    predoder_string_bst(node->bst_link[0]);
    putchar(',');
    putchar(' ');
    predoder_string_bst(node->bst_link[1]);
    putchar(')');
  }
}

void predoder_string_rb(const struct rb_node *node) {
  if (node == NULL)
    return;
  printf ("%s ", (char *)node->rb_data);
  if (node->rb_link[0] != NULL || node->rb_link[1] != NULL) {
    putchar('(');
    predoder_string_rb(node->rb_link[0]);
    putchar(',');
    putchar(' ');
    predoder_string_rb(node->rb_link[1]);
    putchar(')');
  }
}

int string_compare(const void *pa, const void *pb, void *param) {
  int bigger = strcmp((char *)pa, (char *)pb);
  if (bigger < 0) return -1;
  else if (bigger > 0) return 1;
  else return 0;
}

int main(void) {
  struct avl_table *avl_tree;
  avl_tree = avl_create(string_compare, NULL, NULL);
  struct bst_table *bst_tree;
  bst_tree = bst_create(string_compare, NULL, NULL);
  struct rb_table *rb_tree;
  rb_tree = rb_create(string_compare, NULL, NULL);

  string line;
  while (getline(cin, line)) {
    char *element;
    element = new char[line.size() + 1];
    strncpy(element, line.c_str(), line.size()+1);

    void **p = avl_probe(avl_tree, element);
    p = bst_probe(bst_tree, element);
    p = rb_probe(rb_tree, element);
  }

  predoder_string_avl(avl_tree->avl_root);
  puts("");
  predoder_string_bst(bst_tree->bst_root);
  puts("");
  predoder_string_rb(rb_tree->rb_root);
  puts("");
  return 0;
}
