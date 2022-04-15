package com.github.mariofleischmann.algorithms.searching;

/**
 * Implements a binary search tree.
 * @param <T> type of values to be stored in the tree.
 */
public class BinSearchTree<T extends Comparable<T>> {
    private TreeNode<T> root = null;
    private int size = 0;

    public void insert(T value) {
        TreeNode<T> child = this.root;
        TreeNode<T> parent =  null;

        while (child != null) {
            parent = child;
            if (value.compareTo(parent.value()) < 0) {
                child = parent.left();
            } else {
                child = parent.right();
            }
        }

        if (parent == null) {
            this.root = new TreeNode<>(value);
        } else if (value.compareTo(parent.value()) < 0) {
            parent.setLeft(new TreeNode<>(value));
        } else {
            parent.setRight(new TreeNode<>(value));
        }

        this.size++;
    }

    public void walk() {
        this.walk(this.root);
    }

    private void walk(TreeNode<T> start) {
        if (start != null) {
            walk(start.left());
            System.out.println(start.value().toString());
            walk(start.right());
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

    private int treeWalk(TreeNode<T> node, TreeNode<T>[][] grid, int d, int x) {
        if (node.left() != null) {
            x = treeWalk(node.left(), grid, d+1, x);
        }

        grid[d][x++] = node;

        if (node.right() != null) {
            x = treeWalk(node.right(), grid, d+1, x);
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
            int l = height(node.left(), i + 1);
            int r = height(node.right(), i + 1);
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
            return this.search(start.left(), value);
        } else {
            return this.search(start.right(), value);
        }
    }

    public TreeNode<T> successor(TreeNode<T> node) {
        if (node.right() == null) {
            return null; // no successor
        } else {
            TreeNode<T> successor = node.right();
            while (successor.left() != null) {
                successor = successor.left();
            }

            return successor;
        }
    }

    public boolean delete(T value) {
        TreeNode<T> parent = null;
        TreeNode<T> node = this.root;

        int c = 0;
        while (node != null && (c = value.compareTo(node.value())) != 0) {
            parent = node;
            if (c < 0) {
                node = node.left();
            } else {
                node = node.right();
            }
        }

        if (node == null) {
            // Node not found
            return false;
        }

        TreeNode<T> replacingNode;
        if (node.left() == null) {
            replacingNode = node.right();
        } else if (node.left() != null && node.right() == null) {
            replacingNode = node.left();
        } else {
            // search for direct successor
            replacingNode = node.right();
            boolean isDirectSuccessor = replacingNode.left() == null;
            if (isDirectSuccessor) {
                replacingNode.setLeft(node.left());
            } else {
                TreeNode<T> successorsParent = replacingNode;
                replacingNode = replacingNode.left();
                while(replacingNode.left() != null) {
                    successorsParent = replacingNode;
                    replacingNode = replacingNode.left();
                }

                successorsParent.setLeft(replacingNode.right());
                replacingNode.setLeft(node.left());
                replacingNode.setRight(node.right());
            }
        }

        if (node == this.root) {
            this.root = replacingNode;
        } else if (parent.left() == node) {
            parent.setLeft(replacingNode);
        } else {
            parent.setRight(replacingNode);
        }

        this.size--;
        return true;
    }
}
