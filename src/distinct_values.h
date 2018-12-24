//
//  distinct_values.h
//  SegmentTree
//
//  Created by Sneha Venkat on 11/22/18.
//  Copyright © 2018 Sneha Venkat. All rights reserved.
//



#ifndef distinct_values_h
#define distinct_values_h

//#include "segment_tree.h"

#include "segment_tree.h"
#include <chrono>

using namespace std;
using namespace std::chrono;


class Count_Distinct{
public:
    void create_distinct_tree(float a[],int n,int l,int r){
        
        float *bins = new float[n];
        unordered_set<float> set;
        for(int i=0;i<n;i++){
            bins[i] = 0;
            if (set.find(a[i]) == set.end())
            {
                set.insert(a[i]);
                bins[i]++;
            }
            //cout<<i<<" "<<bins[i]<<endl;
        }
        
        /*sum(x)*/
//        Segment_Tree st_x_sum(n);//Segment tree object
//        st_x_sum.build_x_sum(bins);//build sum(x) tree
        Segment_Tree st_x_sum(n);//Segment tree object
        st_x_sum.build_x_sum(bins);//build sum(x) tree
        auto start = high_resolution_clock::now();
        cout <<st_x_sum.query(l, r)<<endl;//print the sum in range(0,6) index-based
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by query function to find distinct values: "
        << duration.count() << " microseconds" << endl<<endl;
        
    }
    
    int count_distinct_normally(float a[],int n,int l,int r){
        int count = 0;
        unordered_set<float> set;
        for(int i=l;i<r;i++){
            if (set.find(a[i]) == set.end()){
                count++;
                set.insert(a[i]);
            }
        }
        return count;
        
    }
    
    
    
};

#endif /* distinct_values_h */
