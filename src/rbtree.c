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

#define BLACK 0
#define  RED  1

#define PARENT 2

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
int rbtree_search(rbtree rbt, unsigned key) {
    struct __rbt_node *node = rbt->root;
    while (node) {
        // If node key is equal to the searched one,
        // return true
        if (node->key == key)
            return 1;

        // Go to next node
        node = node->link[ node->key < key ];
    }

    return 0;
}

/**
 *
 */
void *rbtree_get(rbtree rbt, unsigned key) {
    struct __rbt_node *node = rbt->root;
    while (node) {
        // If node key is equal to the searched one,
        // return value ptr
        if (node->key == key)
            return node->value;

        // Go to next node
        node = node->link[ node->key < key ];
    }

    return NULL;
}

/**
 *
 */
static void __rbt_node_rotate(rbtree rbt, struct __rbt_node *node, int dir) {
    struct __rbt_node *tmp = node->link[ !dir ];

    node->link[ !dir ] = tmp->link[ dir ];

    if (tmp->link[ dir ])
        (tmp->link[ dir ])->link[ PARENT ] = node;

    tmp->link[ PARENT ] = node->link[ PARENT ];

    if (!node->link[ PARENT ])
        rbt->root = tmp;
    else
        (node->link[ PARENT ])->link[ node != (node->link[ PARENT ])->link[ dir ] ] = tmp;

    tmp->link[ dir ] = node;
    node->link[ PARENT ] = tmp;
}

/**
 *
 */
static struct __rbt_node *__rbt_node_new(unsigned key, void *value, size_t v_size) {
    // Create a new tree node
    struct __rbt_node *node = malloc(sizeof(*node));
    if (!node)
        return NULL;

    // Set node key
    node->key = key;

    // Set node value
    if (v_size) {
        // Allocate a new void* and copy data to it
        void *new_ptr = malloc(v_size);
        memcpy(new_ptr, value, v_size);
        node->value = new_ptr;
    } else {
        // Point void* to arg "value"
        node->value = (void *)value;
    }

    // Set all links to NULL
    // TODO better impl?
    node->link[0] =
        node->link[1] =
            node->link[2] = NULL;

    // Return the new node
    return node;
}

/**
 * 
 */
static struct __rbt_node *__rbtree_insert(rbtree rbt, unsigned key, void *value, size_t v_size) {
    // Create node to insert
    struct __rbt_node *new_node = __rbt_node_new(key, value, v_size);
    if (!new_node)
        return NULL;

    // Insert of first node
    if (!rbt->root) {
        rbt->root = new_node;
        return new_node;
    }

    // Insert of successive node
    struct __rbt_node *node = rbt->root,
                      *parent = NULL;
    while (node) {
        parent = node;
        node = node->link[ node->key < key ];
    }

    new_node->link[ PARENT ] = parent;
    return parent->link[ parent->key < key ] = new_node;
}

/**
 * 
 */
static void __rbtree_rest_prop(rbtree rbt, struct __rbt_node *node) {
    node->color = RED;

    while ((node != rbt->root) && 
            ((node->link[ PARENT ])->color == RED))
    {
        // Set parent and grandparent
        struct __rbt_node *parent = node->link[ PARENT ],
                          *grandp = parent->link[ PARENT ];

        for (int dir = 0; dir < 2; ++dir) {
            // Parent is LEFT(0)/RIGHT(1) child of GrandParent
            if (parent == grandp->link[ dir ]) {
                struct __rbt_node *uncle = grandp->link[ !dir ];

                if (uncle && uncle->color == RED) {
                    grandp->color = RED;
                    parent->color = uncle->color = BLACK;
                    node = grandp;
                }

                else {
                    if (node == parent->link[ !dir ]) {
                        __rbt_node_rotate(rbt, parent, dir);
                        node = parent;
                        parent = node->link[ PARENT ];
                    }

                    __rbt_node_rotate(rbt, grandp, !dir);
                    int tmp_color = parent->color;
                    parent->color = grandp->color;
                    grandp->color = tmp_color;
                    node = parent;
                }

                break;
            }
        }
    }

    // Color the root BLACK
    rbt->root->color = BLACK;
}

/**
 * 
 */
int rbtree_insert(rbtree rbt, unsigned key, void *value, size_t v_size) {
    // Insert new node into the tree
    struct __rbt_node *new_node = __rbtree_insert(rbt, key, value, v_size);
    if (!new_node)
        return 0;

    // Restore the red-black property
    __rbtree_rest_prop(rbt, new_node);

    return 1;
}

/**
 * 
 */
static void __rbt_node_free(struct __rbt_node *node) {
    if (!node)
        return;

    free(node->value);
    free(node);
}

/**
 * 
 */
void *rbtree_remove(rbtree rbt, unsigned key) {
    // TODO ...
    return NULL;
}

/**
 *
 */
static struct __rbt_node *__rbtree_find_bttm_lft(struct __rbt_node *node) {
    while (node->link[0])
        node = node->link[0];

    return node;
}

/**
 *
 */
void rbtree_free(rbtree rbt) {
    // Free up red-black tree
    if (rbt->root) {
        struct __rbt_node *node = rbt->root,
                        *bttm_lft = __rbtree_find_bttm_lft(node);

        while (node) {
            if (node->link[1]) {
                bttm_lft->link[0] = node->link[1];
                bttm_lft = __rbtree_find_bttm_lft(bttm_lft);
            }

            struct __rbt_node *tmp = node;
            node = node->link[0];
            __rbt_node_free(tmp);
        }
    }

    // Free up rbtree struct
    free(rbt);
}
