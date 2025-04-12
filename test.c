#include <stdio.h>
// void change_num(int* input_ptr, int* address) {
//   input_ptr = address;
// }
// void change_double(int** input_ptr, int* address) {
//   *input_ptr = address;
// }
// int main() {
//   int* a;
//   int** double_a;
//   int b = 8;
//   a = &b;
//   double_a = &a;
//   int c= 15;
//   change_num(a, &c);
// //1번 결과
//   printf("%d", *a);
//   printf("\n");
//   change_double(double_a, &c);
// //2번 결과
//   printf("%d", *a);
//   return 0;
// }

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// void swap(int a, int b){
//     int temp = a;
//     a = b;
//     b = temp;
// }

int main(){
    int a = 10;
    int b = 5;

    swap(&a, &b);
    printf("a = %d, b = %d", a, b);
    return 0;
}