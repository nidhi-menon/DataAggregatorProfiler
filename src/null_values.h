//
//  null_values.h
//  SegmentTree
//
//  Created by Sneha Venkat on 11/22/18.
//  Copyright © 2018 Sneha Venkat. All rights reserved.
//

#ifndef null_values_h
#define null_values_h

#include "segment_tree.h"
#include <chrono>

using namespace std;
using namespace std::chrono;


class Count_Null{
public:
    void create_null_tree(float a[],int n,int l,int r){
        float *null_bins = new float[n];
        for(int i=0;i<n;i++){
            if(a[i]==-1)
                null_bins[i] = 1;
            else
                null_bins[i] = 0;
        }
    
        /*sum(x)*/
        Segment_Tree st_x_sum(n);//Segment tree object
        st_x_sum.build_x_sum(null_bins);//build sum(x) tree
        auto start = high_resolution_clock::now();
        cout <<st_x_sum.query(l,r)<<endl;//print the sum in range(0,6) index-based
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by query function to find null values: "
        << duration.count() << " microseconds" << endl<<endl;
        
}
    
    int count_null_normally(float a[],int n,int l,int r){
        int count = 0;
        for(int i=l;i<r;i++)
            if(a[i]==-1)
                count++;
        return count;
    }
};

#endif /* null_values_h */
