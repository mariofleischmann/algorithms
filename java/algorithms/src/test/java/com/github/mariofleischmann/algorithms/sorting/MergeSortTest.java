package com.github.mariofleischmann.algorithms.sorting;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertTrue;

import org.junit.Test;

import java.util.Comparator;

/**
 * Unit tests for merge sort implementation.
 */
public class MergeSortTest
{
    /**
     * Test whether array of elements can be sorted in increasing order.
     */
    @Test
    public void orderIncrementing()
    {
        Integer[] unsorted = new Integer[] {1, 5, 3, 5, 7, 4};
        Integer[] sorted = MergeSort.Sort(unsorted, Comparator.comparingInt((Integer a) -> a));
        assertArrayEquals(sorted, new Integer[] {1, 3, 4, 5, 5, 7});
    }

    /**
     * Test whether array of elements can be sorted in decreasing order.
     */
    @Test
    public void orderDecrementing()
    {
        Integer[] unsorted = new Integer[] {1, 5, 3, 5, 7, 4};
        Integer[] sorted = MergeSort.Sort(unsorted, Comparator.comparingInt((Integer a) -> -a));
        assertArrayEquals(sorted, new Integer[] {7, 5, 5, 4, 3, 1});
    }

    /**
     * Test whether an array can be "sorted" without runtime error.
     */
    @Test
    public void orderEmptyArray()
    {
        Integer[] unsorted = new Integer[] {};
        Integer[] sorted = MergeSort.Sort(unsorted, Comparator.comparingInt((Integer a) -> a));
        assertTrue(sorted.length == 0);
    }
}
