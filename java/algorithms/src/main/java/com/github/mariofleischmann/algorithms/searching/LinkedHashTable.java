package com.github.mariofleischmann.algorithms.searching;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.ListIterator;

public class LinkedHashTable {
    private int m;
    private int size;
    private ArrayList<LinkedList<Integer>> table;
    private static final double A = (Math.sqrt(5) - 1) / 2;

    public LinkedHashTable(int m) {
        this.m = m;
        this.size = 0;
        this.table = new ArrayList<>(m);
        for (int i = 0; i < m; i++) {
            this.table.add(new LinkedList<>());
        }
    }

    private int h(int x) {
        return (int) Math.floor((x * A - Math.floor(x * A)) * this.m);
    }

    public void insert(int x) {
        LinkedList<Integer> list = this.table.get(this.h(x));
        list.addLast(x);
        this.size++;
    }

    public Integer search(int x) {
        LinkedList<Integer> list = this.table.get(this.h(x));
        for (Integer entry : list) {
            if (entry == x) {
                return entry;
            }
        }

        return null;
    }

    public void delete(int x) {
        LinkedList<Integer> list = this.table.get(this.h(x));
        ListIterator<Integer> it = list.listIterator();
        while (it.hasNext()) {
            if (it.next() == x) {
                it.remove();
                this.size--;
                break;
            }
        }
    }

    public int getSize() {
        return this.size;
    }

    public int getM() {
        return this.m;
    }

    public int getLongestListLength() {
        return this.table.stream().reduce(this.table.get(0), (a, b) -> a.size() > b.size() ? a : b).size();
    }
}
