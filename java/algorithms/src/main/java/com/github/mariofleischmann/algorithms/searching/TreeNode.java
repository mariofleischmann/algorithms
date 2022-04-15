package com.github.mariofleischmann.algorithms.searching;

/**
 * Represents a node in a binary tree.
 * @param <T> type of the value to be stored in the node.
 */
public class TreeNode<T extends Comparable<T>> {
    private T value;
    private TreeNode<T> left = null;
    private TreeNode<T> right = null;

    /**
     * Creates a new tree node.
     * @param value value to be stored in the node.
     */
    public TreeNode(T value) {
        this.value = value;
    }

    /**
     * Gets the value stored in the node.
     * @return value of the node.
     */
    public T value() {
        return this.value;
    }

    /**
     * Gets the left child node.
     * @return left child node.
     */
    public TreeNode<T> left() {
        return this.left;
    }

    /**
     * Gets the right child node.
     * @return right child node.
     */
    public TreeNode<T> right() {
        return this.right;
    }

    /**
     * Sets the left child node.
     * @param node node to be set as left child.
     */
    public void setLeft(TreeNode<T> node) {
        this.left = node;
    }

    /**
     * Sets the right child node.
     * @param node node to be set as right child.
     */
    public void setRight(TreeNode<T> node) {
        this.right = node;
    }
}
