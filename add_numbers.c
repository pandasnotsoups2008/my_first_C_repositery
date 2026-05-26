#include <stdio.h>

int main()
{
    printf("Enter two numbers: ");
    int num1, num2;
    scanf("%d %d", &num1, &num2);
    int sum = num1 + num2;
    printf("Sum = %d\n", sum);    // ← This line is missing!
    return 0;
}