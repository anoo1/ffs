/*
 * Copyright (c) International Business Machines Corp., 2014
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/*!
 * @file tree.h
 * @brief Binary Tree Container
 * @details Trees are a kind of associative container that stores elements formed
 *          by the conbination of a @em key and a @em tree_node
 * @details For example,
 * @code
 * ...
 * int main (int argc, char *argv[]) {
 *     typedef struct {
 *         int i;
 *         float f;
 *         tree_node_t node;
 *     } data_t;
 *
 *     slab_t s;
 *     slab_init(&s, "my_slab", sizeof(data_t), 4096);
 *
 *     tree_t t;
 *     tree_init(&t, default_compare);
 *
 *     int i;
 *     for (i=0; i<25; i++) {
 *         data_t * d = (data_t *)slab_alloc(&s);
 *
 *         d->i = i;
 *         d->f = (float)i	// key
 *
 *         tree_node_init(&d->node, (const void *)(d->i));
 *         tree_insert(&t, &d->node);
 *
 *         printf("insert i[%d] --> %p\n", i, d);
 *     }
 * @endcode
 * @author Shaun Wetzstein <shaun@us.ibm.com>
 * @date 2010-2011
 */

#ifndef __TREE_H__
#define __TREE_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "exception.h"
#include "builtin.h"
#include "compare.h"
#include "type.h"

#define INIT_TREE_NODE	{NULL,}
#define INIT_TREE	{NULL,NULL,NULL,NULL,0}

/* ==================================================================== */

typedef struct tree_node tree_node_t;	//!< Alias for the @em tree_node class

typedef int (*tree_walk_f) (tree_node_t *);	//!< Tree walk callback function

/*!
 * @brief tree node
 * @details Primitive types cannot be stored in the @em tree container, instead the user must
 * embed a @em tree_node object within the stored object.
 */
struct tree_node {
	tree_node_t *left;	//!< Reference the left tree_node (a.k.a. left sub-tree)
	tree_node_t *right;	//!< Reference the right tree_node (a.k.a. right sub-tree)
	tree_node_t *parent;	//!< Reference the parent tree_node

	const void *key;	//!< Reference to the key bytes for this tree_node
};

/*!
 * @brief tree container
 * @details Primitive types cannot be stored in the @em tree container, instead the user must
 * embed a @em tree_node object within the stored object.
 */
struct tree {
	tree_node_t *root;	//!< Reference to the root tree_node of the @em tree

	tree_node_t *min;	//!< Reference to the node with smallest 'key' in the tree
	tree_node_t *max;	//!< reference to the node with largest 'key' in the tree

	compare_f compare;	//!< Reference to the function used to distinguish tree_nodes
	size_t size;		//!< Cache of the number of tree_node's contained in the @em tree
};
typedef struct tree tree_t;	//!< Alias for the @em tree class

/* ==================================================================== */

/*!
 * @brief Constructs a @em tree_node object
 * @memberof tree_node
 * @param self [in] tree_node object @em self pointer
 * @param key [in] pointer to key bytes
 * @return Reference to an initialized tree_node object on SUCCESS
 */
static inline tree_node_t *tree_node_init(tree_node_t * self, const void *key)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/*!
 * @brief Check if the @em tree_node object is a leaf node
 * @details A leaf node is one where both @em .left and @em .right are NULL
 * @memberof tree_node
 * @param self [in] tree_node object @em self pointer
 * @return True if the @em tree_node is a leaf node, false otherwise
 */
static inline bool tree_node_leaf(tree_node_t * self)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/*!
 * @brief Check if the @em tree_node object is an internal node
 * @details An internal node is one where either (or both) @em .left and @em .right are non-NULL
 * @memberof tree_node
 * @param self [in] tree_node object @em self pointer
 * @return True if the @em tree_node is an internal node, false otherwise
 */
static inline bool tree_node_internal(tree_node_t * self)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/*!
 * @brief Return the left sub-tree of a @em tree_node
 * @memberof tree_node
 * @param self [in] tree_node object @em self pointer
 * @return Reference to a @em tree_node if @em self is non-NULL, NULL otherwise
 */
static inline tree_node_t *tree_node_left(tree_node_t * self)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/*!
 * @brief Return the right sub-tree of a @em tree_node
 * @memberof tree_node
 * @param self [in] tree_node object @em self pointer
 * @return Reference to a @em tree_node if @em self is non-NULL, NULL otherwise
 */
static inline tree_node_t *tree_node_right(tree_node_t * self)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/*!
 * @brief Return the parent tree_node of a @em tree_node
 * @memberof tree_node
 * @param self [in] tree_node object @em self pointer
 * @return Reference to a @em tree_node if @em self is non-NULL, NULL otherwise
 */
static inline tree_node_t *tree_node_parent(tree_node_t * self)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/*!
 * @brief Return the key pointer of a @em tree_node
 * @memberof tree_node
 * @param self [in] tree_node object @em self pointer
 * @return Reference to the key bytes if @em self is non-NULL, NULL otherwise
 */
static inline const void *tree_node_key(tree_node_t * self)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/*!
 * @brief Return the prev tree_node of a @em tree_node
 * @memberof tree_node
 * @param self [in] tree_node object @em self pointer
 * @return Reference to a @em tree_node if @em self is non-NULL, NULL otherwise
 */
extern tree_node_t *tree_node_prev(tree_node_t * self)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/*!
 * @brief Return the next tree_node of a @em tree_node
 * @memberof tree_node
 * @param self [in] tree_node object @em self pointer
 * @return Reference to a @em tree_node if @em self is non-NULL, NULL otherwise
 */
extern tree_node_t *tree_node_next(tree_node_t * self)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/*!
 * @brief Dump the contents of a @em tree to @em out output stream
 * @memberof tree_node
 * @param self [in] tree_node object @em self pointer
 * @param out [in] Reference to the @em out output stream
 * @return None
 * @throws UNEXPECTED if @em self pointer is NULL
 */
extern void tree_node_dump(tree_node_t * self, FILE * out)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/* ======================================================== */

static inline tree_node_t *tree_node_init(tree_node_t * self, const void *key)
{
	self->left = self->right = NULL;
	self->parent = NULL;
	self->key = key;
	return self;
}

static inline bool tree_node_leaf(tree_node_t * self)
{
	return self ? self->left == NULL && self->right == NULL : false;
}

static inline bool tree_node_internal(tree_node_t * self)
{
	return self ? self->left != NULL && self->right != NULL : false;
}

static inline tree_node_t *tree_node_left(tree_node_t * self)
{
	return self ? self->left : NULL;
}

static inline tree_node_t *tree_node_right(tree_node_t * self)
{
	return self ? self->right : NULL;
}

static inline tree_node_t *tree_node_parent(tree_node_t * self)
{
	return self ? self->parent : NULL;
}

static inline const void *tree_node_key(tree_node_t * self)
{
	return self ? self->key : NULL;
}

/* ======================================================== */

/*!
 * @brief Constructs a @em tree object
 * @memberof tree
 * @param self [in] tree_node object @em self pointer
 * @param compare [in] Reference to the @em tree_node compare function
 * @return None
 * @throws UNEXPECTED if @em self pointer is NULL
 */
extern int tree_init(tree_t * self, compare_f compare)
/*! @cond */
__nonnull((1, 2)) /*! @endcond */ ;

/*!
 * @brief Insert a new @em tree_node into the @em tree container
 * @memberof tree
 * @param self [in] tree object @em self pointer
 * @param node [in] Reference to the @em tree_node to insert
 * @return @em true if the @em tree_node was inserted, @em false otherwise
 * @throws UNEXPECTED if @em self pointer is NULL
 * @throws UNEXPECTED if @em tree_node.key points to a duplicate key
 */
extern int tree_insert(tree_t * self, tree_node_t * node)
/*! @cond */
__nonnull((1, 2)) /*! @endcond */ ;

/*!
 * @brief Removes a @em tree_node from the @em tree container
 * @memberof tree
 * @param self [in] tree object @em self pointer
 * @param node [in] Reference to the @em tree_node to remove
 * @return @em true if the @em tree_node was removed, @em false otherwise
 * @throws UNEXPECTED if @em self pointer is NULL
 */
extern int tree_remove(tree_t * self, tree_node_t * node)
/*! @cond */
__nonnull((1, 2)) /*! @endcond */ ;

/*!
 * @brief Find a @em tree_node within the @em tree container
 * @memberof tree
 * @param self [in] tree object @em self pointer
 * @param key [in] Reference to the @em key to find
 * @return Reference to a @em tree_node on SUCCESS, false otherwise
 * @throws UNEXPECTED if @em self pointer is NULL
 */
extern tree_node_t *tree_find(tree_t * self, const void *key)
/*! @cond */
__nonnull((1, 2)) /*! @endcond */ ;

/*!
 * @brief Walk the @em tree and call walk_func for each node
 * @memberof tree
 * @param self [in] tree object @em self pointer
 * @param walk_func [in] Reference to the walk function callback
 * @return None
 * @throws UNEXPECTED if @em self pointer is NULL
 */
extern int tree_walk(tree_t * self, tree_walk_f walk_func)
/*! @cond */
__nonnull((1, 2)) /*! @endcond */ ;

/*!
 * @brief Hexdump the contents of a @em tree to @em out output stream
 * @memberof tree
 * @param self [in] tree object @em self pointer
 * @param out [in] Reference to the @em out output stream
 * @return None
 * @throws UNEXPECTED if @em self pointer is NULL
 */
extern void tree_dump(tree_t * self, FILE * out)
/*! @cond */
__nonnull((1, 2)) /*! @endcond */ ;

/*!
 * @brief Return the root @em tree_node of a @em tree container
 * @memberof tree
 * @param self [in] tree object @em self pointer
 * @return Reference to a @em tree_node if @em self is non-NULL, NULL otherwise
 */
static inline tree_node_t *tree_root(tree_t * self)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/*!
 * @brief Return whether a @em tree container is empty
 * @memberof tree
 * @param self [in] tree object @em self pointer
 * @return @em true if @em tree is empty, false otherwise
 */
static inline bool tree_empty(tree_t * self)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/*!
 * @brief Return the node count of a @em tree container
 * @memberof tree
 * @param self [in] tree object @em self pointer
 * @return @em 0 if @em tree is empty, @em non-0 otherwise
 */
static inline size_t tree_size(tree_t * self)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/*!
 * @brief Return the minimum @em tree_node of a @em tree container
 * @memberof tree
 * @param self [in] tree object @em self pointer
 * @return Reference to a @em tree_node if @em self is non-NULL, NULL otherwise
 */
static inline tree_node_t *tree_min(tree_t * self)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/*!
 * @brief Return the maximum @em tree_node of a @em tree container
 * @memberof tree
 * @param self [in] tree object @em self pointer
 * @return Reference to a @em tree_node if @em self is non-NULL, NULL otherwise
 */
static inline tree_node_t *tree_max(tree_t * self)
/*! @cond */
__nonnull((1)) /*! @endcond */ ;

/* ======================================================== */

static inline tree_node_t *tree_root(tree_t * self)
{
	return self ? self->root : NULL;
}

static inline bool tree_empty(tree_t * self)
{
	return self ? self->root == NULL : true;
}

static inline size_t tree_size(tree_t * self)
{
	return self ? self->size : 0;
}

static inline tree_node_t *tree_min(tree_t * self)
{
	return self ? self->min : NULL;
}

static inline tree_node_t *tree_max(tree_t * self)
{
	return self ? self->max : NULL;
}

/* ======================================================== */

/*!
 * @brief Insert a new @em tree_node into the @em tree container
 * @details @em splay_insert is similar to @em tree_insert except
 *          it will self-adjust using the splay algorithm
 * @memberof tree
 * @param self [in] splay object @em self pointer
 * @param node [in] Reference to the @em tree_node to insert
 * @return @em true if the @em tree_node was inserted, @em false otherwise
 * @throws UNEXPECTED if @em self pointer is NULL
 * @throws UNEXPECTED if @em tree_node.key points to a duplicate key
 */
extern int splay_insert(tree_t * self, tree_node_t * node)
/*! @cond */
__nonnull((1, 2)) /*! @endcond */ ;

/*!
 * @brief Removes a @em tree_node from the splay @em tree container
 * @details @em splay_remove is similar to @em tree_remove except
 *          it will self-adjust using the splay algorithm
 * @memberof tree
 * @param self [in] splay object @em self pointer
 * @param node [in] Reference to the @em tree_node to remove
 * @return @em true if the @em tree_node was removed, @em false otherwise
 * @throws UNEXPECTED if @em self pointer is NULL
 * @throws UNEXPECTED if @em tree_node.key points to a duplicate key
 */
extern int splay_remove(tree_t * self, tree_node_t * node)
/*! @cond */
__nonnull((1, 2)) /*! @endcond */ ;

/*!
 * @brief Find a @em tree_node within the splay @em tree container
 * @details @em splay_find is similar to @em tree_find except it will
 *          self-adjust using the splay algorithm
 * @memberof tree
 * @param self [in] splay object @em self pointer
 * @param key [in] Reference to the @em key to find
 * @return Reference to a @em tree_node on SUCCESS, false otherwise
 * @throws UNEXPECTED if @em self pointer is NULL
 */
extern tree_node_t *splay_find(tree_t * self, const void *key)
/*! @cond */
__nonnull((1, 2)) /*! @endcond */ ;

/* ======================================================== */

#endif				/* __TREE_H__ */
