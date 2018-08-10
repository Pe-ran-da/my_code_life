/*************************************************************************
> File Name: eu16.c
> Author: 
> Mail: 
> Created Time: 2018年07月25日 星期三 13时30分22秒
************************************************************************/

#include<stdio.h>
#define SUM 2

int num[500] = {0};

int main() {
    num[0] = num[1] = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= num[0]; j++) {
            num[j] *= 1024;
        }
        for (int j = 1; j <= num[0]; j++) {
            if (num[j] < 10) continue;
            num[j + 1] += num[j] / 10;
            num[j] %= 10;
            //num[0] += (j == num[0]);
            if(j == num[0]) num[0]++;
        }
        printf("%d : %d\n", i + 1, num[0]);
        for (int k = num[0]; k > 0; k--) {
            printf("%d", num[i]);
        }
        printf("\n");
    }
    int ans = 0;
    for (int i = num[0]; i > 0; i--) {
        ans += num[i]; 
    }
    printf("%d\n", ans);
    return 0;
}


/*#include <inttypes.h>



 #define D_VALUE 1000



  int32_t main() {

      int32_t ans[1000] = {0};

      ans[0] = 1; ans[1] = 1;

      for (int32_t i = 0; i < 100; ++i) {

          for (int32_t j = 1; j <= ans[0]; ++j) {

              ans[j] *= 1024;


          }

          for (int32_t j = 1; j <= ans[0]; ++j) {
          if (ans[j] < D_VALUE) continue;

              ans[j + 1] += ans[j] / D_VALUE; 

              ans[j] %= D_VALUE;

              if (j == ans[0]) ++ans[0];


          }


      }

      int32_t sum = 0;

      for (int32_t i = 1; i <= ans[0]; ++i) {

          while (ans[i]) {

              sum += ans[i] % 10;

              ans[i] /= 10;


          }


      }

      printf("%d\n", sum); 

      return 0;


  }*/
