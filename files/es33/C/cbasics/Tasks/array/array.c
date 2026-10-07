// create one dynamic array in that sorting and remove the even numbers and print the final array after sorting

#include <stdio.h>
#include <stdlib.h>
void sorting(int *arr, int n)
{
   int i, j, temp;
   for (i = 0; i < n - 1; i++)
   {
      for (j = i + 1; j < n; j++)
      {
         if (arr[i] > arr[j])
         {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
         }
      }
   }
}
int even_remove(int *arr, int n)
{
   int i, temp = 0;
   for (i = 0; i < n; i++)
   {
      if (arr[i] % 2 != 0)
      {
         arr[temp] = arr[i];
         temp++;
      }
   }
   return temp;
}
int main()
{
   int n, i;
   printf("enter size of array\n");
   scanf("%d", &n);

   int *arr = (int *)malloc(n * sizeof(int));

   if (arr == NULL)
   {
      printf("dynamic creation was failed");
      return 1;
   }
   for (i = 0; i < n; i++)
   {
      scanf("%d", &arr[i]);
   }
   printf("\n");
   sorting(arr, n);
   printf("after sorting number \n");
   for (i = 0; i < n; i++)
   {
      printf("%d ", arr[i]);
   }
   printf("\n");
   printf("after remove even number \n");
   int remove = even_remove(arr, n);
   for (i = 0; i < remove; i++)
   {
      printf("%d ", arr[i]);
   }
   printf("\n"

   );
   free(arr);
   return 0;
}
