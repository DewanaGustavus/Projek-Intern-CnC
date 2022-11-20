# Linear Recurrence

Recursion is an algorithm pattern that often appears in Competitive Programming.
The simplest example of recursion problem is calculating the N'th Fibonacci number. 
Fibonacci is a recursion pattern where F(N) is equal to F(N - 1) + F(N - 2) with F(0) = 0 and F(1) = 1.

If we calculate Fibonacci numbers by recursion, the time complexity is O(N) (the proof is trivial so it's not explained here).
Although O(N) seems quite efficient, there is a more efficient method known in Competitive Programming which is the exponential matrix method.

## Exponential Matrix

For Fibonacci problem, the value depends on two previous values.
Now, we will try to represent the Fibonacci Sequence Equation in terms of the 
Matrix.

<p align="center"><img src="https://dev-to-uploads.s3.amazonaws.com/uploads/articles/tqvtl38olff38gnjef6x.png" alt="Array"/></p>

This matrix is created based of this Equation:

F(n) = 1 * F(n - 1) + 1 * F(n - 2)

F(n - 1) = 1 * F(n - 1) + 0 * F(n - 2)

Complexity Analysis :

Time Complexity : The time complexity of this method is O(log N) as the multiplication of the 2nd matrix can be done in O(log N) using Divide and Conquer Algorithm

Space Complexity : The space complexity of this method is O(log N)

## Code

```c++
// C++ program to find value of the N'th value in Fibonacci Sequence Mod 10^9 + 7
#include <bits/stdc++.h>

#define ll long long

using namespace std;
const ll MOD = 1e9 + 7;

// Function to Multiply 2 Matrix, the Result is saved in Matrix a
void multiply(ll a[2][2], ll b[2][2]) {
    ll mul[2][2];

    for (ll i = 0; i < 2; i++) {
        for (ll j = 0; j < 2; j++) {
            mul[i][j] = 0;

            for (ll k = 0; k < 2; k++) {
                mul[i][j] += a[i][k] * b[k][j];
                mul[i][j] %= MOD;
            }
        }
    }

    for (ll i = 0; i < 2; i++) {
        for (ll j = 0; j < 2; j++) {
            a[i][j] = mul[i][j];
        }
    }
}
 
// Function to compute F raise to power n - 1.
ll power(ll F[2][2], ll n) {
    ll M[2][2] = {{1, 1}, {1, 0}};
 
    // Initial Value
    if (n == 1) {
        return F[0][0] + F[0][1];
    }
 
    power(F, n / 2);
 
    multiply(F, F);
 
    if (n % 2 != 0)
        multiply(F, M);

    return (F[0][0] + F[0][1]) % MOD;
}
 
// Return N'th term of Fibonacci Sequence
ll findNthTerm(ll n) {
 
    ll F[2][2] = {{1, 1}, {1, 0}};
 
    //Base cases
    if(n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return power(F, n - 1);
    }
}
 
// Driver Code
int main() {
    for (ll i = 0; i < 100; i++) {
        cout << "F(" << i << ") is " << findNthTerm(i) << endl;
    }
    return 0;
}
```
