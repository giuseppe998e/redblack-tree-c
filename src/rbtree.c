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
#define RED   1

#define LEFT   0
#define RIGHT  1
#define PARENT 2

#define LEFT_OF(_x)   ((_x)->link[ LEFT ])
#define RIGHT_OF(_x)  ((_x)->link[ RIGHT ])
#define PARENT_OF(_x) ((_x)->link[ PARENT ])

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
    struct __rbt_node *root;  // Tree root node
    void (*free_v)(void*);    // Ptr to value custom free function
};

/**
 * 
 */
rbtree rbtree_init(void (*free_v)(void*)) {
    struct __rbtree *rbt = malloc(sizeof(*rbt));
    if (!rbt)
        return NULL;

    // Init struct
    rbt->root = NULL;
    rbt->free_v = free_v ? free_v : free;

    return rbt;
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
    LEFT_OF(node) =
        RIGHT_OF(node) =
            PARENT_OF(node) = NULL;

    // Return the new node
    return node;
}

/**
 * 
 */
static void __rbt_node_rotate(rbtree rbt, struct __rbt_node *node, int dir) {
    struct __rbt_node *tmp = node->link[ !dir ];

    node->link[ !dir ] = tmp->link[ dir ];

    if (tmp->link[ dir ])
        PARENT_OF(tmp->link[ dir ]) = node;

    PARENT_OF(tmp) = PARENT_OF(node);

    if (PARENT_OF(node))
        PARENT_OF(node)->link[ node != PARENT_OF(node)->link[ dir ] ] = tmp;
    else
        rbt->root = tmp;

    tmp->link[ dir ] = node;
    PARENT_OF(node) = tmp;
}

/**
 * 
 */
static void __rbt_rest_prop(rbtree rbt, struct __rbt_node *node) {
    node->color = RED;

    while ((node != rbt->root) &&
            (PARENT_OF(node)->color == RED))
    {
        // Set parent and grandparent
        struct __rbt_node *parent = PARENT_OF(node),
                          *grandp = PARENT_OF(parent);

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
                        parent = PARENT_OF(node);
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
    // Search for parent node
    struct __rbt_node *node = rbt->root,
                      *parent = NULL;
    while (node && (node->key != key)) {
        parent = node;
        node = node->link[ node->key < key ];
    }

    // If node exist, do not re-insert
    if (node)
        return 0;

    // Create node to insert
    struct __rbt_node *new_node = __rbt_node_new(key, value, v_size);
    if (!new_node)
        return 0;

    // Else, insert new node
    PARENT_OF(new_node) = parent;

    // Set node parent (if any)
    if (parent)
        parent->link[ parent->key < key ] = new_node;
    else
        rbt->root = new_node;

    // Restore the red-black property
    __rbt_rest_prop(rbt, new_node);

    return 1;
}

/**
 * 
 */
static struct __rbt_node *__rbt_get_node(rbtree rbt, unsigned key) {
    struct __rbt_node *node = rbt->root;
    while (node && (node->key != key))
        node = node->link[ node->key < key ];

    return node;
}

/**
 * 
 */
void *rbtree_get(rbtree rbt, unsigned key) {
    struct __rbt_node *node = __rbt_get_node(rbt, key);
    if (!node)
        return NULL;

    return node->value;
}

/**
 * 
 */
int rbtree_search(rbtree rbt, unsigned key) {
    struct __rbt_node *node = __rbt_get_node(rbt, key);
    return !!node;
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
void rbtree_delete(rbtree rbt, unsigned key) {
    void *ptr = rbtree_remove(rbt, key);
    rbt->free_v(ptr);
}

/**
 * 
 */
void rbtree_free(rbtree rbt) {
    // Free up red-black tree
    if (rbt->root) {
        struct __rbt_node *node = rbt->root,
                            *lft_mst = node,
                            *tmp;

        while (node) {
            while (LEFT_OF(lft_mst))
                lft_mst = LEFT_OF(lft_mst);

            LEFT_OF(lft_mst) = RIGHT_OF(node);
            tmp = node;
            node = LEFT_OF(node);

            rbt->free_v(tmp->value);
            free(tmp);
        }
    }

    // Free up rbtree struct
    free(rbt);
}
