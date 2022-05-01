package com.github.mariofleischmann.algorithms.searching;

import java.util.ArrayList;

public class BTree<T extends Comparable<T>> {
    private final int order;
    private BTreeNode<T> root;

    public BTree(int order) {
        this.order = order;
        this.root = new BTreeNode<>(order, true);
    }

    public void insert(T data) {
        if (this.root.isFull()) {
            BTreeNode<T> n = new BTreeNode<>(this.order, false);
            n.children.set(0, this.root);
            n.splitChild(0);
            this.root = n;
        }

        this.insert(data, this.root);
    }

    private void insert(T data, BTreeNode<T> node) {
        if (node.isLeaf) {
            node.insert(data);
        } else {
            BTreeNode<T> child = node.ensureInsertion(data);
            this.insert(data, child);
        }
    }

    public void walk() {
        this.walk(this.root);
    }

    private void walk(BTreeNode<T> node) {
        if (!node.isLeaf) {
            this.walk(node.children.get(0));
        }

        for (int i = 0; i < node.n; i++) {
            System.out.println(node.keys.get(i).toString());

            if (!node.isLeaf) {
                this.walk(node.children.get(i+1));
            }
        }
    }

    public int height() {
        int h = 1;
        BTreeNode<T> node = this.root;

        while (!node.isLeaf) {
            h++;
            node = node.children.get(0);
        }

        return h;
    }

    public BTreeNode<T> search(T data) {
        return this.search(data, this.root);
    }

    private BTreeNode<T> search (T data, BTreeNode<T> node) {
        int i = 0;
        while (i < node.n && data.compareTo(node.keys.get(i)) > 0) {
            i++;
        }

        if (i < node.n && data.compareTo(node.keys.get(i)) == 0) {
            return node;
        }

        if (node.isLeaf) {
            return null;
        }

        return this.search(data, node.children.get(i));
    }

    public static class BTreeNode<T extends Comparable<T>> {
        public final boolean isLeaf;
        public final int order;
        public final ArrayList<T> keys;
        public final ArrayList<BTreeNode<T>> children;
        private int n;

        public BTreeNode(int order, boolean isLeaf) {
            this.order = order;
            this.isLeaf = isLeaf;

            this.keys = new ArrayList<>(2 * order - 1);
            this.children = new ArrayList<>(2 * order);
            for (int i = 0; i < 2 * order - 1; i++) {
                this.keys.add(i, null);
                this.children.add(i, null);
            }
            this.children.add(2 * order - 1, null);

            this.n = 0;
        }

        public boolean isFull() {
            return this.n == (2 * this.order - 1);
        }

        public void splitChild(int index) {
            BTreeNode<T> child = this.children.get(index);
            T key = child.keys.get(child.n / 2);
            BTreeNode<T> sibling = child.split();
            this.insertChild(sibling, index + 1);
            this.insertKey(key, index);

            this.n++;
        }

        private BTreeNode<T> split() {
            this.n = this.order - 1;

            BTreeNode<T> sibling = new BTreeNode<>(this.order, this.isLeaf);
            sibling.n = this.order - 1;

            for (int i = 0; i < this.order - 1; i++) {
                sibling.keys.set(i, this.keys.get(this.order + i));
            }

            if (!this.isLeaf) {
                for (int i = 0; i < this.order; i++) {
                    sibling.children.set(i, this.children.get(this.order + i));
                }
            }

            return sibling;
        }

        private void insertKey(T key, int pos) {
            for (int i = this.n; i > pos; i--) {
                this.keys.set(i, this.keys.get(i-1));
            }

            this.keys.set(pos, key);
        }

        private void insertChild(BTreeNode<T> child, int pos) {
            for (int i = this.n + 1; i > pos; i--) {
                this.children.set(i, this.children.get(i-1));
            }

            this.children.set(pos, child);
        }

        public BTreeNode<T> ensureInsertion(T data) {
            int i = 0;
            while (i < this.n && data.compareTo(this.keys.get(i)) > 0) {
                i++;
            }

            BTreeNode<T> child = this.children.get(i);
            if (child.isFull()) {
                this.splitChild(i);
                if (data.compareTo(this.keys.get(i)) > 0) {
                    i++;
                }
            }

            return this.children.get(i);
        }

        public void insert(T data) {
            if (!this.isLeaf) {
                return;
            }

            int i = this.findInsertionIndex(data);
            this.insertKey(data, i);
            this.n++;
        }

        private int findInsertionIndex(T key) {
            for (int i = this.n; i > 0; i--) {
                T other = this.keys.get(i - 1);
                if (other.compareTo(key) <= 0) {
                    return i;
                }
            }

            return 0;
        }

        public void walk() {
            System.out.print("( ");
            for (int i = 0; i < this.n; i++) {
                System.out.print(this.keys.get(i).toString() + " ");
            }

            System.out.println(")");
        }
    }
}
