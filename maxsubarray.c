#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
    long long sum;
} Result;

Result maxResult(Result a, Result b, Result c) {
    Result max = a;
    if (b.sum > max.sum) max = b;
    if (c.sum > max.sum) max = c;
    return max;
}

Result maxCrossingSubarray(int arr[], int left, int mid, int right, long long constraint) {
    long long leftSum = LLONG_MIN;
    long long sum = 0;
    int maxLeft = -1;

    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        if (sum <= constraint && sum > leftSum) {
            leftSum = sum;
            maxLeft = i;
        }
    }

    long long rightSum = LLONG_MIN;
    sum = 0;
    int maxRight = -1;

    for (int j = mid + 1; j <= right; j++) {
        sum += arr[j];
        if (sum <= constraint && sum > rightSum) {
            rightSum = sum;
            maxRight = j;
        }
    }

    if (maxLeft != -1 && maxRight != -1 && leftSum + rightSum <= constraint) {
        return (Result){maxLeft, maxRight, leftSum + rightSum};
    } else {
        return (Result){-1, -1, LLONG_MIN};
    }
}

Result maxSubarray(int arr[], int left, int right, long long constraint) {
    if (left > right) return (Result){-1, -1, LLONG_MIN};

    if (left == right) {
        if (arr[left] <= constraint)
            return (Result){left, left, arr[left]};
        else
            return (Result){-1, -1, LLONG_MIN};
    }

    int mid = left + (right - left) / 2;
    Result leftRes = maxSubarray(arr, left, mid, constraint);
    Result rightRes = maxSubarray(arr, mid + 1, right, constraint);
    Result crossRes = maxCrossingSubarray(arr, left, mid, right, constraint);

    return maxResult(leftRes, rightRes, crossRes);
}

void printArray(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]");
}

void printResult(int testNum, int arr[], int size, long long constraint, Result res) {
    printf("Test Case %d:\n", testNum);
    printf("  Input Array: ");
    if (size == 0) {
        printf("[]\n");
    } else {
        printArray(arr, size);
        printf("\n");
    }
    printf("  Constraint: %lld\n", constraint);

    if (res.sum == LLONG_MIN) {
        printf("  No feasible subarray under the constraint.\n");
    } else {
        printf("  Maximum Subarray: ");
        for (int i = res.start; i <= res.end; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n  Sum: %lld\n", res.sum);
    }
    printf("\n");
}

int main() {
    int test1[] = {2, 1, 3, 4};
    int test2[] = {2, 2, 2, 2};
    int test3[] = {1, 5, 2, 3};
    int test4[] = {6, 7, 8};
    int test5[] = {1, 2, 3, 2, 1};
    int test6[] = {1, 1, 1, 1, 1};
    int test7[] = {4, 2, 3, 1};
    int test8[] = {};
    int test9[] = {1, 2, 3};

    int n10 = 100000;
    int *test10 = malloc(n10 * sizeof(int));
    for (int i = 0; i < n10; i++) test10[i] = i + 1;

    int test11[]={3,2,-1,5,6,2,-8};
    struct {
        int *arr;
        int size;
        long long constraint;
    } tests[] = {
        {test1, sizeof(test1)/sizeof(int), 5},
        {test2, sizeof(test2)/sizeof(int), 4},
        {test3, sizeof(test3)/sizeof(int), 5},
        {test4, sizeof(test4)/sizeof(int), 5},
        {test5, sizeof(test5)/sizeof(int), 5},
        {test6, sizeof(test6)/sizeof(int), 4},
        {test7, sizeof(test7)/sizeof(int), 5},
        {test8, 0, 10},
        {test9, sizeof(test9)/sizeof(int), 0},
        {test10, n10, 1000000000LL},
        {test11,sizeof(test11)/sizeof(int),20}
    };

    for (int i = 0; i < 11; i++) {
        Result res = maxSubarray(tests[i].arr, 0, tests[i].size - 1, tests[i].constraint);
        printResult(i + 1, tests[i].arr, tests[i].size, tests[i].constraint, res);
    }

    free(test10);
    return 0;
}