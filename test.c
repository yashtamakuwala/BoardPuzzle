#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// int main() {
//     char num[12];
//     for (int a = 0; a<= 9; a++ ){
//         for (int b = 0; b<= 9; b++){
//             for (int c = 0; c<= 9; c++){
//                 for (int d = 0; d<=9; d++){
//                     for(int e = 0; e <= 9; e++){
//                         int z = 4 * (a + b*10 + c * 100 + d 1* 1000 + e*10000);
//                         snprintf(num, "%d", z );
//                         int revNum = e + d*10 + c * 100 + b * 1000 + a*10000
//                     }
//                 }
//             }
//         }
//     }
    
// }

// typedef struct {
//    int name;
//    int salary;
//     } Worker;                    // Worker is now a type, like char and int
    
//     int main() {
//      Worker w, *wp;             // define variables with the new type
   
//      wp = &w;
   
//      w.salary = 125000;         // is probably what you want
//      (*wp).salary = 125000;     // or you can use the pointer, but this looks kludgy
//      wp->salary = 125000;       // this is the 'sexy' way to use pointers
     
//      return EXIT_SUCCESS; 
//    }


// int main(){
//    int a = 20;
//    int *p = &a;

//    // printf("a is %d\n", a);
//    // // printf("address of a %d", &a );
//    // // printf("&p is %p \n", &p);
//    // printf("p is %p \n", p);

//    // printf("value at *p %d\n", *p);
//    int z = p + 5;
//    // printf("z is %x",z);

//    // for (int i = 0; i <5; i++){
//    //    int z;
      
//    //    // sprintf(z,"%x",4*i);
//    //    (p + 0x4) = i;
//    // }

//    //  for (int i = 0; i <5; i++){
//    //     printf("%d\n", *(p+4*i));
//    //    // *(p + i*4) = i;
//    // }

//    printf("\nAddress: %d\n",&a);
//    printf("%d\n", &a - 9);
//    printf("%d\n", &a - 0x9);
//    // printf("sizeof char %d\n", sizeof(char));
//    return EXIT_SUCCESS;
// }

void main(){
   char c = 'b';
   // int num = c - '0';
   // // snprintf(c, "%d", num );
   // printf("a : %d", num);

   if( c > 'a' && c < 'z' ){
      printf("\nless");
   }
}