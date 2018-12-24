//
//  tree_segment.h
//  SegmentTree
//
//  Created by Sneha Venkat on 11/23/18.
//  Copyright © 2018 Sneha Venkat. All rights reserved.
//

#ifndef tree_segment_h
#define tree_segment_h

#include <vector>

class Tree_Segment{
private:
    // limit for array size
    //const int N = 100000;
    
    //int n; // array size
    
    // Max size of tree
    //float *tree;
    
    vector<float> tree;
    unsigned n;
    
public:
    Tree_Segment(){
        //n = a_size;
        //tree = new float[2*N];
        n = 0;
        tree.reserve(1000000);
        
    }
    
    // function to build the sum(x) tree
    void build_x_sum(vector<float> &arr,int l)
    {
        
        //n = arr.size();
        //arr.reserve(n);
        n = l;
//        for(int i=0;i<n;i++)
//            cout<<arr[i]<<endl;
        
        // insert leaf nodes in tree
        for (unsigned i=0; i<n; i++)
            tree[n+i] = arr[i];
        
        //build the tree by calculating parents
        for (int i = n - 1; i > 0; --i)
            tree[i] = tree[i<<1] + tree[i<<1 | 1];
        
        arr.clear();
    }
    
    // function to build sum(x^2) tree
    void build_x_square_sum(vector<float> &arr)
    {
         n = arr.size();
        // insert leaf nodes in tree
        for (int i=0; i<n; i++)
            tree[n+i] = arr[i]*arr[i];
        
        // build the tree by calculating parents
        for (int i = n - 1; i > 0; --i)
            tree[i] = tree[i<<1] + tree[i<<1 | 1];
        arr.clear();
    }
    
    // function to build the sum(xy) tree
    void build_xy_sum(vector<float> &arr1,vector<float> &arr2)
    {
         n = arr1.size();
        // insert leaf nodes in tree
        for (int i=0; i<n; i++)
            tree[n+i] = arr1[i]*arr2[i];
        
        // build the tree by calculating parents
        for (int i = n - 1; i > 0; --i)
            tree[i] = tree[i<<1] + tree[i<<1 | 1];
        arr1.clear();
        arr2.clear();
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
        float res = 0.0;
        
        
        
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

#endif /* tree_segment_h */
