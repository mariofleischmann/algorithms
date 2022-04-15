package com.github.mariofleischmann.algorithms.sorting;

import java.util.Arrays;
import java.util.Comparator;

/**
 * Implements the merge sort algorithm.
 */
public class MergeSort
{
    public static <T extends Comparable<T>> T[] Sort(T[] arr, Comparator<T> comparator) {
        int l = arr.length;
        if (l <= 1) {
            // Array is already sorted
            return arr;
        }

        int m = l / 2;
        T[] arr1 = MergeSort.Sort(Arrays.copyOfRange(arr, 0, m), comparator);
        T[] arr2 = MergeSort.Sort(Arrays.copyOfRange(arr, m, l), comparator);

        // At this point, arrays arr1 and arr2 are sorted

        int i1 = 0, i2 = 0;
        for (int i = 0; i < l; i++) {
            if (i1 >= arr1.length)
                arr[i] = arr2[i2++];
            else if (i2 >= arr2.length)
                arr[i] = arr1[i1++];
            else {
                if (comparator.compare(arr1[i1], arr2[i2]) < 0)
                    arr[i] = arr1[i1++];
                else
                    arr[i] = arr2[i2++];
            }
        }

        return arr;
    }
}
