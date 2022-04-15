package com.github.mariofleischmann.algorithms.sorting;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertTrue;

import org.junit.Test;

import java.util.Comparator;

/**
 * Unit tests for quick sort implementation.
 */
public class QuickSortTest {
    /**
     * Test whether array of elements can be sorted in increasing order.
     */
    @Test
    public void orderIncrementing()
    {
        Integer[] arr = new Integer[] {1, 5, 3, 5, 7, 4};
        QuickSort qsort = new QuickSort(QuickSort.PivotPosition.MEDIAN);
        qsort.sort(arr, 0, arr.length - 1, Comparator.comparingInt((Integer a) -> a));
        assertArrayEquals(new Integer[] {1, 3, 4, 5, 5, 7}, arr);
    }

    /**
     * Test whether array of elements can be sorted in decreasing order.
     */
    @Test
    public void orderDecrementing()
    {
        Integer[] arr = new Integer[] {1, 5, 3, 5, 7, 4};
        QuickSort qsort = new QuickSort(QuickSort.PivotPosition.MEDIAN);
        qsort.sort(arr, 0, arr.length - 1, Comparator.comparingInt((Integer a) -> -a));
        assertArrayEquals(new Integer[] {7, 5, 5, 4, 3, 1}, arr);
    }

    /**
     * Test whether an array can be "sorted" without runtime error.
     */
    @Test
    public void orderEmptyArray()
    {
        Integer[] arr = new Integer[] {};
        QuickSort qsort = new QuickSort(QuickSort.PivotPosition.MEDIAN);
        qsort.sort(arr, 0, arr.length-1, Comparator.comparingInt((Integer a) -> a));
        assertTrue(arr.length == 0);
    }
}
