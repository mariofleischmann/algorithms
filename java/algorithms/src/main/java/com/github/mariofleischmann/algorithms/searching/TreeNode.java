package com.github.mariofleischmann.algorithms.searching;

/**
 * Represents a node in a binary tree.
 * @param <T> type of the value to be stored in the node.
 */
public class TreeNode<T extends Comparable<T>> {
    private T value;
    public TreeNode<T> left;
    public TreeNode<T> right;
    public TreeNode<T> parent;

    /**
     * Creates a new tree node.
     * @param value value to be stored in the node.
     */
    public TreeNode(T value) {
        this.value = value;
        this.left = null;
        this.right = null;
        this.parent = null;
    }

    /**
     * Gets the value stored in the node.
     * @return value of the node.
     */
    public T value() {
        return this.value;
    }
}
