package com.github.mariofleischmann.algorithms.sorting;

import java.util.Comparator;

/**
 * Implements the quick sort algorithm.
 */
public class QuickSort {
    public enum PivotPosition {
        LEFT, RIGHT, MIDDLE, MEDIAN
    }

    private PivotPosition pivotPosition;

    public QuickSort(PivotPosition pos) {
        this.pivotPosition = pos;
    }

    public <T> void sort(T[] arr, int l, int r, Comparator<T> comp) {
        if (l < r) {
            this.enforcePivotPosition(arr, l, r, comp);
            int q = this.partition(arr, l, r, comp);
            this.sort(arr, l, q-1, comp);
            this.sort(arr, q+1, r, comp);
        }
    }

    private <T> void enforcePivotPosition(T[] arr, int l, int r, Comparator<T> comp) {
        switch (this.pivotPosition) {
            case LEFT:
                T temp = arr[l];
                arr[l] = arr[r];
                arr[r] = temp;
                break;
            case MIDDLE:
                int m = (l + r) / 2;
                temp = arr[m];
                arr[m] = arr[r];
                arr[r] = temp;
                break;
            case MEDIAN:
                m = (l + r) / 2;
                int compL = comp.compare(arr[l], arr[m]) + comp.compare(arr[l], arr[r]);
                int compM = comp.compare(arr[m], arr[l]) + comp.compare(arr[m], arr[r]);
                if (compL > -2 && compL < 2) {
                    temp = arr[l];
                    arr[l] = arr[r];
                    arr[r] = temp;
                }
                else if (compM > -2 && compM < 2) {
                    temp = arr[m];
                    arr[m] = arr[r];
                    arr[r] = temp;
                }
                else {
                    // keep right element at its position
                }
                break;
            default: break;
        }
    }

    private <T> int partition(T[] arr, int l, int r, Comparator<T> comp) {
        T pivot = arr[r];
        int i = l;
        int j = r-1;

        while (i < j) {
            while (comp.compare(arr[i], pivot) < 0)
                i++;
            while (j > l && comp.compare(arr[j], pivot) >= 0)
                j--;

            if (i < j) {
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
        }

        if (i == j && comp.compare(arr[i], pivot) < 0)
            i++;

        if (arr[i] != pivot) {
            T temp = arr[i];
            arr[i] = arr[r];
            arr[r] = temp;
        }

        return i;
    }
}
