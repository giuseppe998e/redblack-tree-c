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

#ifndef __REDBLACK_TREE_H
#define __REDBLACK_TREE_H

#include <stddef.h>

/**
 * 
 */
typedef struct __rbtree *rbtree;

/**
 * 
 */
rbtree rbtree_init();

/**
 *
 */
void *rbtree_search(rbtree, unsigned);

/**
 *
 */
void *rbtree_insert(rbtree, unsigned, void*, size_t);

/**
 * 
 */
void *rbtree_remove(rbtree, unsigned);

/**
 *
 */
void rbtree_free(rbtree);

#endif
