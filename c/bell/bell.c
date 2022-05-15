/**
 * bell.c
 * Number of ways to connect n solder pads.
 */

#include <stdio.h>

#define N 10

unsigned long long sum(unsigned long long *arr, int n) {
    unsigned long long s = 0;
    for (int i = 0; i < n; i++){
        s += arr[i];
    }

    return s;
}

void find_connection_groups(unsigned long long *g, int n)
{
    if (n == 1) {
        g[0] = 1;
    } else {
        find_connection_groups(g, n-1);
        for (int i = n-1; i >= 1; i--) {
            g[i] = g[i-1] + (i+1) * g[i];
        }
    }
    
    printf("%d\t%lld\n", n, sum(g, n));
}

int main(void)
{
    unsigned long long g[N] = {0};
    find_connection_groups(g, N);
    return 0;    
}
