#include <stdbool.h>
#include <stdio.h>
//Q1 : Finding a min and a max in a list
void minMax(int arr[], int size) {
    int min = arr[0], max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    printf("Minimum element is %d\n", min);
    printf("Maximum element is %d\n", max);
}

//Q2 : Find each amount of every integer in the list
void integerCount(int arr[], int size) {
    //Go through each value
    for (int i = 0; i < size; i++) {
        //The count of each value
        int count = 0;
        //If there is a pair then it already has counted it
        bool pair = false;
        //If the number has a number behind it that is the same then it has already been counted
        for (int k = i-1; k >= 0; k--) {
            if (arr[k] == arr[i]) {
                //Set the pair to true and break the loop
                pair = true;
                break;
            }
        }
        //If the number has a pair but hasn't been counted already then it counts it
        for (int j=0; j<size; j++) {
            if (arr[j] == arr[i] && pair == false) {
                count++;
            }
        }
        //Print only if count isn't zero cause otherwise it means it's an already counted number
        if (count != 0) {
            printf("the number of %d  in the list : %d\n", arr[i], count);
        }
    }
}

//Q3 : find the Kth smallest and largest element in a list
void findKthSmallestLargest (int arr[], int size, int kth) {
    //Sort the array
    for (int i = 0; i < size; i++) {
        int temp;

        //Turn the duplicates into -1 but not one of them
        for (int j = 0; j < size; j++) {
            if (arr[i] == arr[j] && i != j) {
                arr[j] = - 1;
            }
        }

        //Sorts the array
        for (int j = 0; j < size; j++) {
            if (arr[i] < arr[j]) {
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }

    //Count the amount of -1 to skip them
    int count = -1;
    for (int i = 0; i < size; i++) {
        if (arr[i] == - 1) {
            count++;
        }
    }
    //Prints the smallest which is at index Kth + the amount of -1's
    printf("Smallest %d element is %d\n",kth, arr[count + kth]);
    //Prints the largest which is at the end (size) - the Kth
    printf("The largest %d element is %d\n",kth, arr[size - kth]);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}

//Q4 : Find if there is a sum of 2 numbers in the array which equal to an x sum value
void findSum(int arr[], int size, int sum) {
    //Sort the array
    for (int i = 0; i < size; i++) {
        int temp;

        //Turn the duplicates into -1 but not one of them
        for (int j = 0; j < size; j++) {
            if (arr[i] == arr[j] && i != j) {
                arr[j] = - 1;
            }
        }

        //Sorts the array
        for (int j = 0; j < size; j++) {
            if (arr[i] < arr[j]) {
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }

    //Count the amount of -1 to skip them
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == - 1) {
            count++;
        }
    }

    //Starting from the index after the -1's find the sum
    for (int i = count; i < size; i++) {
        for (int j = count; j < size; j++) {
            if (arr[i] + arr[j] == sum) {
                printf("sum found of %d + %d = %d\n", arr[i], arr[j], sum);
            }
        }
    }
}

int fiboRecursive(int elem1, int elem2, int n) {
    if (n == 1) {
        return elem1;
    }
    return fiboRecursive(elem2, elem1 + elem2, n - 1);
}

int max(int a, int b) {
    return (a > b) ? a : b; // Compares if a bigger than b, if true ("?") return a else (":") return b
}

int knapsackMatrix(int W, int weights[], int profits[], int N) {
    int dp[N+1][W+1]; // builds a matrix with + 1 size for base case

    // Goes through each matrix's cell to input profit
    for (int i = 0; i <= N; i++) { //Goes through each item
        for (int w = 0; w <= W; w++) { //For each item tests each possible weight left as an index
            if (i == 0 || w == 0) {
                dp[i][w] = 0; //Fills the first row (the row where there is no more items or no more weight) with 0s (base case)
            }
            //The next two ifs means if you can include the item, get the max of max(Previous profit + current item profit OR the current profit) otherwise just fill cell with the current profit as it has no more capacity
            else if (weights[i-1] <= w) {
                dp[i][w] = max(profits[i-1] + dp[i-1][w - weights[i-1]], dp[i-1][w]);
            }
            else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    // The final answer will be in dp[N][W]
    return dp[N][W];
}

int knapsack1D(int W, int weight[], int profit[], int N) {
    // Create a 1D DP array of size (W + 1), initialized to 0
    int dp[W + 1];

    // Initialize the dp array with 0
    for (int i = 0; i <= W; i++) {
        dp[i] = 0;
    }

    // Loop through each item
    for (int i = 0; i < N; i++) {
        // Update the DP array in reverse (to avoid overwriting previous values too early)
        for (int w = W; w >= weight[i]; w--) {
            // Perform the DP update to decide whether to include the current item
            dp[w] = dp[w] > (profit[i] + dp[w - weight[i]]) ? dp[w] : (profit[i] + dp[w - weight[i]]);
        }
    }

    // The answer will be stored in dp[W], the maximum profit with weight capacity W
    return dp[W];
}

// Recursive function to solve 0/1 Knapsack problem
int knapsackRecursive(int W, int weight[], int profit[], int N) {
    // Base case: if no items are left or the capacity is 0
    if (N == 0 || W == 0)
        return 0;

    // If the weight of the current item is more than the remaining capacity, exclude it
    if (weight[N - 1] > W)
        return knapsackRecursive(W, weight, profit, N - 1);

    // Recursively consider both options: including and excluding the current item
    // Return the maximum profit of the two choices
    else
        return max(
            profit[N - 1] + knapsackRecursive(W - weight[N - 1], weight, profit, N - 1),
            knapsackRecursive(W, weight, profit, N - 1)
        );
}


int main(void) {
    int arr[] = {1, 9, 1, 9, 1, 5, 6, 9, 9, 9, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    //minMax(arr, size);
    //integerCount(arr, size);
    //findKthSmallestLargest(arr, size, 2);
    //findSum(arr, size, 15);
    //printf("%d", fiboRecursive(0, 1, 32));
    int weights[] = {1, 1, 1};
    int profits[] = {10, 20, 30};
    int W = 2;
    int N = sizeof(profits) / sizeof(profits[0]);
    printf("max profit for the KnapSackMatrix is : %d\n", knapsackMatrix(W, weights, profits, N));
    printf("max profit for the KnapSack1D is : %d\n", knapsack1D(W, weights, profits, N));
    printf("max profit for the KnapSackRecursive is : %d\n", knapsackRecursive(W, weights, profits, N));
    return 0;
}
