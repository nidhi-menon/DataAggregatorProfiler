//
//  segment_tree.h
//  SegmentTree
//
//  Created by Sneha Venkat on 10/8/18.
//  Copyright © 2018 Sneha Venkat. All rights reserved.
//

#ifndef segment_tree_h
#define segment_tree_h

class Segment_Tree{
private:
// limit for array size
const int N = 100000;

int n; // array size

// Max size of tree
float *tree;
    
public:
    Segment_Tree(int a_size){
        n = a_size;
        tree = new float[2*N];
        
    }

// function to build the sum(x) tree
void build_x_sum(float arr[])
{
    // insert leaf nodes in tree
    for (int i=0; i<n; i++)
        tree[n+i] = arr[i];
    
    // build the tree by calculating parents
    for (int i = n - 1; i > 0; --i)
        tree[i] = tree[i<<1] + tree[i<<1 | 1];
}
    
// function to build sum(x^2) tree
void build_x_square_sum(float arr[])
    {
        // insert leaf nodes in tree
        for (int i=0; i<n; i++)
            tree[n+i] = arr[i]*arr[i];
        
        // build the tree by calculating parents
        for (int i = n - 1; i > 0; --i)
            tree[i] = tree[i<<1] + tree[i<<1 | 1];
    }
    
// function to build the sum(xy) tree
void build_xy_sum(float arr1[],float arr2[])
    {
        // insert leaf nodes in tree
        for (int i=0; i<n; i++)
            tree[n+i] = arr1[i]*arr2[i];
        
        // build the tree by calculating parents
        for (int i = n - 1; i > 0; --i)
            tree[i] = tree[i<<1] + tree[i<<1 | 1];
    }

// function to update a tree node
void updateTreeNode(int p, float value)
{
    // set value at position p
    tree[p+n] = value;
    p = p+n;
    
    // move upward and update parents
    for (int i=p; i > 1; i >>= 1)
        tree[i>>1] = tree[i] + tree[i^1];
}

// function to get sum on interval [l, r)
float query(int l, int r)
{
    float res = 0;
    
    // loop to find the sum in the range
    for (l += n, r += n; l < r; l >>= 1, r >>= 1)
    {
        if (l&1)
            res += tree[l++];
        
        if (r&1)
            res += tree[--r];
    }
    
    return res;
}
};

#endif /* segment_tree_h */
