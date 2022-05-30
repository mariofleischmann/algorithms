package com.github.mariofleischmann.algorithms.searching;

import java.util.Hashtable;
import java.util.Set;

/**
 * Represents a weighted graph implemented with an adjacency list.
 */
public class WeightedGraph<T> {
    private Hashtable<T, Hashtable<T, Integer>> adjacencyList = new Hashtable<>();

    public void newVertex (T v) {
        this.adjacencyList.put(v, new Hashtable<>());
    }

    public void newEdge (T a, T b, int cost) {
        this.adjacencyList.get(a).put(b, cost);
    }

    public Set<T> vertices() {
        return this.adjacencyList.keySet();
    }

    public Set<T> neighbors(T v) {
        return this.adjacencyList.get(v).keySet();
    }

    public Integer cost(T a, T b) {
        return this.adjacencyList.get(a).get(b);
    }

    public boolean containsVertex(T v) {
        return this.adjacencyList.containsKey(v);
    }
}