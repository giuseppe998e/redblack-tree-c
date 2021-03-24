# RedBlack-Tree-C
This is an implementation of a `Red-Black Tree` written in C just for fun and with educational purposes.  
**It is not intended for use in a production scenario.**

## Usage example
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rbtree.h"

struct test_s {
    char *txt;
};

void free_value(void *v) {
    printf("DEL\n");

    if (!v)
        return;

    free(((struct test_s*) v)->txt);
    free(v);
}

int main(int argc, char **argv) {
    // Initialize RBTree
    rbtree rbt = rbtree_init(free_value);

    // Insert filler nodes
    rbtree_insert(rbt, 5, 0, 0);
    rbtree_insert(rbt, 1, 0, 0);
    rbtree_insert(rbt, 3, 0, 0);

    // Insert hll node
    struct test_s hll;
    hll.txt = strdup("HELLO");
    rbtree_insert(rbt, 6, &hll, sizeof(struct test_s));  // Copy

    // Insert filler nodes
    rbtree_insert(rbt, 8, 0, 0);
    rbtree_insert(rbt, 2, 0, 0);
    rbtree_insert(rbt, 7, 0, 0);

    // Insert wrld node
    struct test_s *wrld = malloc(sizeof(struct test_s));
    wrld->txt = strdup("WORLD");
    rbtree_insert(rbt, 4, wrld, 0);  // Reference

    // Insert filler nodes
    rbtree_insert(rbt, 9, 0, 0);
    rbtree_insert(rbt, 0, 0, 0);

    // Print nodes count
    printf("Num# nodes: %u\n", rbtree_nodes(rbt));

    // Check nodes existence
    printf("Exists hll? %c\n", rbtree_search(rbt, 6) ? 'Y' : 'N');
    printf("Exists wrld? %c\n", rbtree_search(rbt, 4) ? 'Y' : 'N');

    // Print texts contatenation
    struct test_s *ptr_hll = rbtree_get(rbt, 6),
                  *ptr_wrld = rbtree_get(rbt, 4);
    printf("Texts concat.: '%s %s!'\n", ptr_hll->txt, ptr_wrld->txt);

    // Free up RBTree
    rbtree_free(rbt);
    return 0;
}
```