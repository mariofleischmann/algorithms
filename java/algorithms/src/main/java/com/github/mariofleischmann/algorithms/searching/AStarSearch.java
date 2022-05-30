package com.github.mariofleischmann.algorithms.searching;

import java.util.*;
import java.util.function.Function;

public class AStarSearch<T> {
    private Hashtable<T, Boolean> visited = new Hashtable<>();
    private Hashtable<T, T> pred = new Hashtable<>();
    private Hashtable<T, Double> d = new Hashtable<>();
    private Hashtable<T, Double> f = new Hashtable<>();

    private T goal;

    public AStarSearch(WeightedGraph<T> graph, T start, T goal, Function<T, Double> heuristic) {
        for (T v : graph.vertices()) {
            d.put(v, Double.MAX_VALUE);
            pred.put(start, start);
            visited.put(v, false);
        }

        d.put(start, 0.);
        double h = heuristic.apply(start);
        f.put(start, h);

        PriorityQueue<Pair> K = new PriorityQueue<>((a, b) -> (int) (a.prio - b.prio));
        K.add(new Pair(start, 0));

        while (!K.isEmpty()) {
            T u = K.remove().vertex;
            if (u.equals(goal)) {
                this.goal = u;
                return;
            }

            for (T v : graph.neighbors(u)) {
                if (visited.get(v)) {
                    continue;
                }

                double x = d.get(u) + graph.cost(u, v) + heuristic.apply(v);
                if (K.stream().anyMatch((p) -> p.vertex.equals(v)) && x > f.get(v)) {
                    continue;
                }

                pred.put(v, u);
                f.put(v, x);
                d.put(v, d.get(u) + graph.cost(u, v));
                K.add(new Pair(v, x));
            }

            visited.put(u, true);
        }

        // goal not found
        this.goal = null;
    }

    protected class Pair {
        public final T vertex;
        public final double prio;

        public Pair(T vertex, double prio) {
            this.vertex = vertex;
            this.prio = prio;
        }
    }

    public Iterable<T> path() {
        if (this.goal == null) {
            return null;
        }

        LinkedList<T> path = new LinkedList<>();
        T curr = this.goal, previous;
        do {
            path.addFirst(curr);
            previous = curr;
            curr = this.pred.get(curr);
        } while (!previous.equals(curr));

        return path;
    }

    public Iterable<T> visitedVertices() {
        LinkedList<T> visited = new LinkedList<>();
        for (Map.Entry<T, Boolean> e : this.visited.entrySet()) {
            if (e.getValue()) {
                visited.add(e.getKey());
            }
        }

        return visited;
    }
}
