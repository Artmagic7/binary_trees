#include "binary_trees.h"

/**
 * heap_insert - Inputs a value in Max Binary Heap
 * @root: a double pointer to the root node of the Heap to insert the value
 * @value: the value to store in the node to be inputed
 *
 * Return: a pointer to the created node
 *         NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *tree, *new, *flip;
	int size, leaves, sub, bit, level, tmp;

	if (!root)
		return (NULL);
	if (!(*root))
		return (*root = binary_tree_node(NULL, value));
	tree = *root;
	size = binary_tree_size(tree);
	leaves = size;
	for (level = 0, sub = 1; leaves >= sub; sub *= 2, level++)
		leaves -= sub;
	/* Deduct all nodes except for bottom-most level */

	for (bit = 1 << (level - 1); bit != 1; bit >>= 1)
		tree = leaves & bit ? tree->right : tree->left;
	/*
	 * Crosses tree to first empty slot based on the binary
	 * reprsntatn of the nmbr of leaves.
	 * Example -
	 * If there are 12 nodes in a complete tree, there are 5 leaves on
	 * the 4th tier of the tree. 5 is 101 in binary. 1 corresponds to
	 * right, 0 to left.
	 * The first empty node is 101 == RLR, *root->right->left->right
	 */

	new = binary_tree_node(tree, value);
	leaves & 1 ? (tree->right = new) : (tree->left = new);

	flip = new;
	for (; flip->parent && (flip->n > flip->parent->n); flip = flip->parent)
	{
		tmp = flip->n;
		flip->n = flip->parent->n;
		flip->parent->n = tmp;
		new = new->parent;
	}
	/* Toss values with parent until parent value exceeds new value */

	return (new);
}

/**
 * binary_tree_size - Quantifies the size of a binary tree
 * @tree: Tree to quantify the size of
 *
 * Return: size of the tree
 *         0 if tree is NULL
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
	if (!tree)
		return (0);

	return (binary_tree_size(tree->left) + binary_tree_size(tree->right) + 1);
}
