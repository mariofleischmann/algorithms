package com.github.mariofleischmann.algorithms.searching;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

/**
 * Represents an adjacency list graph.
 */
public class Graph {
    ArrayList<Vertex> vertices;

    public Graph() {
        this.vertices = new ArrayList<>();
    }

    public void newVertex(String name) {
        this.vertices.add(new Vertex(name, this.vertices.size() - 1));
    }

    public boolean containsVertex(String name) {
        return this.vertices.stream().anyMatch(v -> v.getName().equals(name));
    }

    public void newEdge(String from, String to) {
        Vertex v1 = null, v2 = null;
        for (Vertex v : this.vertices) {
            if (v.getName().equals(from)) {
                v1 = v;
            }

            if (v.getName().equals(to)) {
                v2 = v;
            }
        }

        if (v1 != null && v2 != null) {
            v1.addAdjacentVertex(v2);
        }
    }

    /**
     * Implementation of a breath first search.
     */
    public Iterable<String> findShortestPath(String from, String to) {
        for (Vertex v : this.vertices) {
            v.visited = false;
        }
        Queue<Vertex> toVisit = new LinkedList<>();

        Vertex start = this.vertices.stream().filter(v -> v.getName().equals(from)).findFirst().get();
        start.predecessor = null;
        toVisit.add(start);
        while (!toVisit.isEmpty()) {
            Vertex v = toVisit.remove();
            v.visited = true;
            for (Vertex adj : v.getAdjacentVertices()) {
                if (!adj.visited) {
                    adj.predecessor = v;

                    if (adj.getName().equals(to)) {
                        LinkedList<String> path = new LinkedList<>();
                        while (adj != null) {
                            path.addFirst(adj.getName());
                            adj = adj.predecessor;
                        }
                        return path;
                    }

                    adj.visited = true;
                    toVisit.add(adj);
                }
            }
        }

        return null;
    }

    protected class Vertex {
        private String name;
        private int graphIndex;
        private LinkedList<Vertex> adjacencyList;

        // Attributes used in graph search.
        public boolean visited = false;
        public Vertex predecessor = null;

        public Vertex(String name, int graphIndex) {
            this.name = name;
            this.graphIndex = graphIndex;
            this.adjacencyList = new LinkedList<>();
        }

        public String getName() {
            return this.name;
        }

        public int getGraphIndex() {
            return this.graphIndex;
        }

        public void addAdjacentVertex(Vertex v) {
            this.adjacencyList.addLast(v);
        }

        public Iterable<Vertex> getAdjacentVertices() {
            return this.adjacencyList;
        }
    }
}
