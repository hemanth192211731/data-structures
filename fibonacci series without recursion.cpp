#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of terms: ");
    scanf("%d", &n);

    int first = 0, second = 1;

    printf("Fibonacci Series:\n%d %d ", first, second);

    for (int i = 2; i < n; i++) {
        int next = first + second;
        printf("%d ", next);
        first = second;
        second = next;
    }

    return 0;
}
