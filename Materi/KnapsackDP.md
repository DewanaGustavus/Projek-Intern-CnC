## Knapsack DP

Knapsack problems generally involve filling a limited container with a subset of items where we want to count or optimize some quantity associated with the items.

Almost every time, you can think of each item as having a positive weight, and the total weight of the items we choose must not exceed the capacity of the container, which is some number. Some variations of knapsack-type problems include:

- The 0/1 Knapsack problem: Choosing a subset of items such that we maximize their total value and their total weight does not exceed the capacity of the container
- Finding all the possible total weights that we can achieve from any subset of items such that their total weight does not exceed the capacity of the container (in the chapter of CPH linked above)
- Counting how many sequences of items will fill the container completely, meaning the total weight is exactly the capacity of the container (the order may or may not matter)

### 0-1 Knapsack Problem

### Motivating problem
Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum total value in the knapsack. In other words, given two integer arrays val[0..n-1] and wt[0..n-1] which represent values and weights associated with n items respectively. Also given an integer W which represents knapsack capacity, find out the maximum value subset of val[] such that sum of the weights of this subset is smaller than or equal to W. You cannot break an item, either pick the complete item or don’t pick it (0-1 property).

### Approach
Like other typical Dynamic Programming(DP) problems, re-computation of same subproblems can be avoided by constructing a temporary array K[][] in bottom-up manner.

The state DP[i][j] will denote maximum value of ‘j-weight’ considering all values from ‘1 to ith’. So if we consider ‘wi’ (weight in ‘ith’ row) we can fill it in all columns which have ‘weight values > wi’. Now two possibilities can take place: 
- Fill ‘wi’ in the given column.
- Do not fill ‘wi’ in the given column.

Now we have to take a maximum of these two possibilities, formally if we do not fill ‘ith’ weight in ‘jth’ column then DP[i][j] state will be same as DP[i-1][j] but if we fill the weight, DP[i][j] will be equal to the value of ‘wi’+ value of the column weighing ‘j-wi’ in the previous row. So we take the maximum of these two possibilities to fill the current state.

### Code
```c++
// A dynamic programming based
// solution for 0-1 Knapsack problem
#include <bits/stdc++.h>
using namespace std;

// Returns the maximum value that
// can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n)
{
	int i, w;
	vector<vector<int>> K(n + 1, vector<int>(W + 1));

	// Build table K[][] in bottom up manner
	for(i = 0; i <= n; i++)
	{
		for(w = 0; w <= W; w++)
		{
			if (i == 0 || w == 0)
				K[i][w] = 0;
			else if (wt[i - 1] <= w)
				K[i][w] = max(val[i - 1] +
								K[i - 1][w - wt[i - 1]],
								K[i - 1][w]);
			else
				K[i][w] = K[i - 1][w];
		}
	}
	return K[n][W];
}

// Driver Code
int main()
{
	int val[] = { 60, 100, 120 };
	int wt[] = { 10, 20, 30 };
	int W = 50;
	int n = sizeof(val) / sizeof(val[0]);
	
	cout << knapSack(W, wt, val, n);
	
	return 0;
}

// This code is contributed by Debojyoti Mandal

```
Complexity Analysis: 

- Time Complexity: $\mathcal{O}(N*W)$ 
where ‘N’ is the number of weight element and ‘W’ is capacity. As for every weight element we traverse through all weight capacities 1<=w<=W.
- Auxiliary Space: $\mathcal{O}(N*W)$. 
The use of 2-D array of size ‘N*W’.


Note that this approach can be improved further.
We can just iterate through all possible weight from the largest weight W to 0 for every weight available. Since every weight possibilities is emulated and the maximum possible combination is always chosen, we can know that this solution works.

### Code
```c++
#include <bits/stdc++.h>
using namespace std;
int knapSack(int W, int wt[], int val[], int n)
{
	// making and initializing dp array
	int dp[W + 1];
	memset(dp, 0, sizeof(dp));

	for (int i = 1; i < n + 1; i++) {
		for (int w = W; w >= 0; w--) {

			if (wt[i - 1] <= w)
				// finding the maximum value
				dp[w] = max(dp[w],
							dp[w - wt[i - 1]] + val[i - 1]);
		}
	}
	return dp[W]; // returning the maximum value of knapsack
}
int main()
{
	int val[] = { 60, 100, 120 };
	int wt[] = { 10, 20, 30 };
	int W = 50;
	int n = sizeof(val) / sizeof(val[0]);
	cout << knapSack(W, wt, val, n);
	return 0;
}
```
Complexity Analysis:
- Time Complexity: $\mathcal{O}(N*W)$. As redundant calculations of states are avoided.
- Auxiliary Space: $\mathcal{O}(W)$ As we are using 1-D array instead of 2-D array.



Source:
- https://usaco.guide/gold/knapsack?lang=cpp
- https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/