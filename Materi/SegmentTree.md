## Segment Tree
The segment tree is one of the most useful data structures in competitive programming. This allows you to do point update and range query in $\mathcal{O}(\log N)$ time each for 
**any** associative operation, not just summation.

### Sum on a segment
Suppose we have an array $a_i$ of $n$ elements, and we want to be able to do two operations with it:
- *set(i, v)*: set the element with index $i$ to $v$.
- *sum(l, r)*: find the sum on the segment from $l$ to $r$.

### Structure of the segment tree
Let's imagine that we need to build a segment tree for the following array:</br>
<p align="center"><img src="https://espresso.codeforces.com/62a4ed9368574e5a3a879804287c51434b5c29a3.png" alt="Array"/></p>
The segment tree be constructed as follows. This is a binary tree, in the leaves of which there are elements of the original array, and each internal node contains the sum of the numbers in its children.
<p align="center"><img src="https://espresso.codeforces.com/35bc9067266d25646e8a8a5e4ee10159df770d48.png" alt="Segment Tree"/></p>
Note that the tree turned out so beautiful, because the length of the array was a power of two. If the length of the array is not a power of two, you can extend the array with zeroes to the nearest power of two. In this case, the length of the array will increase no more than twice, so the asymptotic time complexity of the operations will not change.
</br></br>
Now let's look at how to do operations on such a tree.

### Operation set
Let's start with the operation *set*. When the element of the array changes, you need to change the corresponding number in the leaf node of the tree, and then recalculate the values that will change from this. These are the values that are higher up the tree from the modified leaf. We can simply recalculate the value in each node as the sum of the values in children.
<p align="center"><img src="https://espresso.codeforces.com/2adeb7419495bbf9ed0dc0dcc64d8bdfd16aaac8.png" alt="Segment Tree"/></p>
When performing such an operation, we need to recalculate one node on each layer of the tree. We have only $\log N$ layers, so the operation time will be $\mathcal{O}(\log N)$.

### Operation sum
Now let's look at how to calculate the sum on a segment. To do this, let's first see what kind of numbers are written in the nodes of the segment tree. Note that these numbers are the sums on some segments of the original array.
<p align="center"><img src="https://espresso.codeforces.com/06bbaebd49114c1f7b823a57786af0726d394655.png" alt="Segment Tree"/></p>
In this case, for example, the number in the root is the sum over the entire array, and the numbers in the leaves are the sum over the segment of one element.</br></br>
Let's try to build the sum on the segment $[l..r)$ from these already calculated sums. To do this, run a recursive traversal of the segment tree. In this case, we will interrupt recursion in two situations.

- The segment corresponding to the current node does not intersect the segment $[l..r)$. In this case, all the elements in this subtree are outside the area in which we need to calculate the sum, so we can stop the recursion.
- The segment corresponding to the current node is entirely nested in the segment $[l..r)$. In this case, all the elements in this subtree are in the area in which we need to calculate the sum, so we need to add to the answer their sum, which is recorded in the current node.
<p align="center"><img src="https://espresso.codeforces.com/0349d47f2df242db7d9e04098f39fa6bdcacddb3.png" alt="Segment Tree"/></p>
Here, the crosses indicate the vertices at which the recursion broke off in the first cutoff, and the vertices in which the number was added to the answer are circled.

### Code
```c++
#include <bits/stdc++.h>

using namespace std;

int seg[1<<20];

int get(int idx, int l, int r, int x, int y){
    if(l > y || r < x) return 0; // NEUTRAL_ELEMENT
    if(l >= x && r <= y) return seg[idx];
    int mid = (l + r) / 2, lc = 2 * idx, rc = 2 * idx + 1;
    return get(lc, l, mid, x, y) + get(rc, mid+1, r, x, y);
}

void upd(int idx, int l, int r, int x, int val){
    if(l > x || r < x) return;
    if(l == x && r == x){
        seg[idx] = val;
        return;
    }
    int mid = (l + r) / 2, lc = 2 * idx, rc = 2 * idx + 1;
    upd(lc, l, mid, x, val);
    upd(rc, mid+1, r, x, val);
    seg[idx] = seg[lc] + seg[rc];
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);

    int v[8] = {3, 1, 2, 5, 6, 4, 3, 2};

    for(int i = 0; i < 8; i++){
        upd(1, 0, 7, i, v[i]); // Segment tree initiation
    }

    upd(1, 0, 7, 5, 8); // Update value at index = 5

    cout << get(1, 0, 7, 2, 6) << '\n'; // Get sum on segment [2..6]

    return 0;
}

```
