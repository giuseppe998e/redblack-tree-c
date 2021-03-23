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

#ifndef __REDBLACK_TREE_H
#define __REDBLACK_TREE_H

#include <stddef.h>

/**
 * RedBlack-Tree pointer
 */
typedef struct __rbtree *rbtree;

/**
 * Initializes a new empty RedBlack-Tree
 */
rbtree rbtree_init();

/**
 * Looks for a node in the RedBlack-Tree
 */
int rbtree_search(rbtree, unsigned);

/**
 * Looks for a node in the RedBlack-Tree
 * and returns the pointer to its stored value
 */
void *rbtree_get(rbtree, unsigned);

/**
 * Inserts a new node into the RedBlack-Tree
 */
int rbtree_insert(rbtree, unsigned, void*, size_t);

/**
 * Deletes a node from the RedBlack-Tree
 */
void rbtree_delete(rbtree, unsigned); // TODO NOTIMPL

/**
 * Removes a node from the RedBlack-Tree
 * and returns the pointer to its stored value
 * which MUST be freed!
 */
void *rbtree_remove(rbtree, unsigned); // TODO NOTIMPL

/**
 * Frees a RedBlack-Tree
 */
void rbtree_free(rbtree);

#endif
