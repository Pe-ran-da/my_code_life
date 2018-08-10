/*************************************************************************
	> File Name: eu45_1.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月29日 星期日 08时44分32秒
 ************************************************************************/

#include<stdio.h>

#include <stdio.h>
#include <inttypes.h>

int64_t pentagonal(int64_t n) { 
    return n * (3 * n - 1) / 2;
}

int64_t is_pentagonal(int64_t x) {
        int64_t head = 1, tail = 500000000, mid;
    while (head <= tail) {
                mid = (head + tail) >> 1;
                if (pentagonal(mid) == x) return 1;
                if (pentagonal(mid) > x) tail = mid - 1;
                else head = mid + 1;
            
    }
        return 0; 

}

int main() {
        int64_t i = 1, j = 1, ans = INT64_MAX;
    while (pentagonal(j + 1) - pentagonal(j) < ans) {
                j++;
                i = j - 1;
        do {
            if (is_pentagonal(pentagonal(i) + pentagonal(j))) {
                if (is_pentagonal(pentagonal(j) - pentagonal(i))) {
                    if (pentagonal(j) - pentagonal(i) < ans) {
                                                ans = pentagonal(j) - pentagonal(i);
                                                printf("%" PRId64 " -> %" PRId64 "\n", pentagonal(j), pentagonal(i));
                                            
                    }
                                    
                }
                            
            }
                        i--;
                    
        } while (i >= 1 && pentagonal(j) - pentagonal(i) < ans);
            
    }
        printf("%" PRId64 "\n", ans);
        return 0;

}
