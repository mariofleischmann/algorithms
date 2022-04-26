package com.github.mariofleischmann.algorithms.searching;

import java.util.LinkedList;
import java.util.Queue;

/**
 * Implements a binary search tree.
 * @param <T> type of values to be stored in the tree.
 */
public class BinSearchTree<T extends Comparable<T>> {
    private TreeNode<T> root = null;
    private int size = 0;

    public void insert(T value) {
        TreeNode<T> parent = null;
        TreeNode<T> child = this.root;

        while (child != null) {
            parent = child;
            if (value.compareTo(parent.value()) < 0) {
                child = parent.left;
            } else {
                child = parent.right;
            }
        }

        TreeNode<T> n = new TreeNode<>(value);
        n.parent = parent;
        if (parent == null) {
            this.root = n;
        } else if (value.compareTo(parent.value()) < 0) {
            parent.left = n;
        } else {
            parent.right = n;
        }

        this.size++;
    }

    public void walk() {
        this.walk(this.root);
    }

    private void walk(TreeNode<T> start) {
        if (start != null) {
            walk(start.left);
            System.out.println(start.value().toString());
            walk(start.right);
        }
    }

    public void treeWalk() {
        if (this.size == 0) {
            return;
        }

        TreeNode<T>[][] grid = new TreeNode[this.height()][this.size];
        this.treeWalk(this.root, grid, 0, 0);

        StringBuilder output = new StringBuilder();
        for (TreeNode[] row : grid) {
            for (TreeNode node : row) {
                output.append((node == null) ? "    " : node.value().toString());
            }
            output.append('\n');
        }
        System.out.print(output);
    }

    public void walkLevel() {
        Queue<TreeNode<T>> q = new LinkedList<>();
        q.add(this.root);
        while (q.size() > 0) {
            TreeNode<T> n = q.remove();
            System.out.println(n.value().toString());

            if (n.left != null) {
                q.add(n.left);
            }
            if (n.right != null) {
                q.add(n.right);
            }
        }
    }

    private int treeWalk(TreeNode<T> node, TreeNode<T>[][] grid, int d, int x) {
        if (node.left != null) {
            x = treeWalk(node.left, grid, d+1, x);
        }

        grid[d][x++] = node;

        if (node.right != null) {
            x = treeWalk(node.right, grid, d+1, x);
        }

        return x;
    }

    public int height() {
        return height(this.root, 0);
    }

    private int height(TreeNode<T> node, int i) {
        if (node == null) {
            return i;
        } else {
            int l = height(node.left, i + 1);
            int r = height(node.right, i + 1);
            return Math.max(l, r);
        }
    }

    public TreeNode<T> search(T value) {
        return this.search(this.root, value);
    }

    public TreeNode<T> search(TreeNode<T> start, T value) {
        if (start == null || value.compareTo(start.value()) == 0) {
            return start;
        }

        if (value.compareTo(start.value()) < 0) {
            return this.search(start.left, value);
        } else {
            return this.search(start.right, value);
        }
    }

    public TreeNode<T> successor(TreeNode<T> node) {
        if (node.right == null) {
            return null; // no successor
        } else {
            TreeNode<T> successor = node.right;
            while (successor.left != null) {
                successor = successor.left;
            }

            return successor;
        }
    }

    public TreeNode<T> realSucc(TreeNode<T> node) {
        // Try to find successor of node x
        TreeNode<T> s = successor(node);
        if (s != null) {
            return s;
        }

        // If no successor of x is found, find y
        // for which the direct predecessor is x.

        //   y
        // o
        //   o
        //     o
        //       x

        TreeNode<T> p = node.parent;
        while (p != null && node == p.right) {
            node = p;
            p = p.parent;
        }

        return p;
    }

    public boolean delete(T value) {
        TreeNode<T> node = this.search(value);
        if (node == null) {
            // Node not found
            return false;
        }

        TreeNode<T> replacingNode;
        if (node.left == null) {
            replacingNode = node.right;
        } else if (node.right == null) {
            replacingNode = node.left;
        } else {
            replacingNode = this.successor(node);
            boolean directSuccessor = replacingNode.parent == node;
            if (!directSuccessor) {
                replacingNode.parent.left = replacingNode.right;
                replacingNode.right = node.right;
                node.right.parent = replacingNode;
            }
            replacingNode.left = node.left;
            node.left.parent = replacingNode;
        }

        if (replacingNode != null) {
            replacingNode.parent = node.parent;
            this.size--;
        }

        if (node == this.root) {
            this.root = replacingNode;
        } else if (node.parent.left == node) {
            node.parent.left = replacingNode;
        } else {
            node.parent.right = replacingNode;
        }

        return true;
    }
}
