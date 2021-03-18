/**
 * RedBlack-Tree-c - Another implementation of a C red-black tree
 * Copyright (C) 2021 - Giuseppe Eletto <peppe.eletto@gmail.com>
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU LGPLv3 along with
 * this library. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string.h>

#include "rbtree.h"

/**
 * 
 */
struct __rbtree_node {
    unsigned key,      // Key used to balance the rbtree
             color:1;  // Color of the node [0: Black, 1: Red]
    void *value;       // Void pointer to the value stored in the node
    struct __rbtree_node *link[3]; // Link to the parent/left/right node 
                                   // [0:Parent, 1:Left, 2:Right]
};

/**
 * 
 */
struct __rbtree {
    struct __rbtree_node *root;
};
 
/**
 * 
 */
rbtree rbtree_init() {
    struct __rbtree *rbt = malloc(sizeof(*rbt));
    if (!rbt)
        return NULL;

    rbt->root = NULL;
    return rbt;
}

/**
 *
 */
void *rbtree_search_node(rbtree rbt, unsigned key) {

    return NULL;
}

/**
 *
 */
void *rbtree_insert_node(rbtree rbt, unsigned key, void *value, size_t v_size) {

    return NULL;
}

/**
 * 
 */
static void __rbtree_node_free(struct __rbtree_node *node) {
}

/**
 * 
 */
void *rbtree_remove_node(rbtree rbt, unsigned key) {

    return NULL;
}

/**
 *
 */
void rbtree_free(rbtree rbt) {
    if (!rbt)
        return;

    __rbtree_node_free(rbt->root);
    free(rbt);
}
