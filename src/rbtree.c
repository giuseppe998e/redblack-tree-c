/**
 * RedBlack-Tree-C - Another C implementation of a red-black tree
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
struct __rbt_node {
    unsigned key:31,  // Key used to balance the rbtree (SPACE OPTIMIZATION)
            color:1;  // Color of the node [0: Black, 1: Red]
    void *value;      // Void pointer to the value stored in the node
    struct __rbt_node *link[3];  // Link to the parent/left/right node 
                                 // [0:Left, 1:Right, 2:Parent]
};

/**
 * 
 */
struct __rbtree {
    struct __rbt_node *root;
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
void *rbtree_search(rbtree rbt, unsigned key) {

    return NULL;
}

/**
 *
 */
void *rbtree_insert(rbtree rbt, unsigned key, void *value, size_t v_size) {

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
void *rbtree_remove(rbtree rbt, unsigned key) {

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
