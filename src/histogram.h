//
//  histogram.h
//  SegmentTree
//
//  Created by Sneha Venkat on 10/14/18.
//  Copyright © 2018 Sneha Venkat. All rights reserved.
//

#ifndef histogram_h
#define histogram_h

#include "segment_tree.h"
#include <algorithm>
#include <chrono>
using namespace std::chrono;


using namespace std;
class Histogram{
    
    private:
    
    
    public:
    void createBins(float a[],int range,int l){
        sort(a,a+l);
        int max_element = a[l-1];
        int num_buckets = (max_element/range) + 1;
        float *bins = new float[num_buckets];
        for(int i=0;i<num_buckets;i++){
            bins[i] = 0;
        }
        int j=0;
        int range2 = 5;
//      int multiplier = 1;
        
        for(int i=0;i<l;i++){
            if(a[i]<range2)
                bins[j]++;
            else{
                ++j;
                range2 = range*(j+1);
                bins[j]++;
            }
        }
        
        for(int i=0;i<num_buckets;i++){
          
            cout<<bins[i]<<" ";
            
        }
        //return bins;
        
    }
    
    float* create_count_tree(int a[], int n, int l, int r){
        
        int *max_e= max_element(a,a+n);
       // cout<<*max_e;
        float *hist_bins = new float[int(*max_e)];
        //cout<<*max_element<<endl;
        for(int i=0;i<=int(*max_e);i++)
        {
            hist_bins[i]=0.0;
        }
        
        for(int i=0;i<n;i++)
        {
            hist_bins[a[i]]=hist_bins[a[i]]+1.0 ;
        }
        return hist_bins;
        
        /*sum(x)*/
        
    }
    
    void count_hist_normally(int bins[],float a[], int n, int l, int r,int w){
        
        int index = 0;
        for(int i=l;i<=r;i++){
            int gap = min(w,r-i+1);
            for(int j=0;j<n;j++){
               if(floor(a[j])>=i&&floor(a[j])<=(i+gap-1))
                   bins[index]++;
            }
            
            index+=1;
            i = i+w-1;
        }
        
    }
    
    float* query_count_tree(Segment_Tree st_hist_sum,int a[],int n,int l,int r,int w)
    {
        int *max_e= max_element(a,a+n);
        float *bin = new float[int(*max_e)];
        int index = 0;
        
        for(int i=0;i<*max_e;i++)
            bin[i] = 0.0;
        
        for(int i=l;i<r;i++){
        //cout<<i<<endl;
        int gap = min(w,r-i+1);
        bin[index++] = st_hist_sum.query(i,i+gap-1);
       // cout<<bin[index-1]<<endl;
        i = i+w-1;
            
    }
        return bin;
    }
    
    float* width_histogram(float a[], int n, int l, int r,int w){
        float *max_e= max_element(a,a+n);
        float *bin = new float[int(*max_e)];
        int index = 0;
        for(int i=0;i<*max_e;i++)
            bin[i] = 0.0;
        for(int i=l;i<r;i++){
            for(int j=0;j<n;j++){
                if(floor(a[j])>=i&&floor(a[j])<=(i+w-1))
                    bin[index]++;
            }
            
            index+=1;
            i = i+w-1;
        }
        return bin;
    }
    
    float* query_base_tree(Segment_Tree st_hist_sum,float a[],int n,int l,int r,int w ){
        int max_e=(r+1)/w;
        float *bin = new float[max_e];
        int index = 0;
        
        for(int i=0;i<max_e;i++)
            bin[i] = 0.0;
        
        for(int i=l;i<r;i++){
            //cout<<i<<endl;
            int gap = min(w,r-i+1);
            bin[index++] = st_hist_sum.query(i,i+gap-1);
            //cout<<bin[index-1]<<endl;
            i = i+w-1;
        }
        return bin;
    }
    
    float* normal_equal_height(float a[], int n, int l, int r,int h){
        int count = 0;
        int index = 0;
        float *bins = new float[n];
        
        for(int i=0;i<r-l;i++)
            bins[i] = 0;
        
        sort(a, a+n);
        for(int i=0;i<n;i++){
            if(floor(a[i])<0|| floor(a[i])>n)
                continue;
            
            if(count==h)
            {
                index++;
                count = 0;
            }
            else
            {
                bins[index]+=1.0;
                count++;
            }
            
            }
        return bins;
        }
    
    void st_equal_height(Segment_Tree st_hist_sum,float a[], int n, int l, int r,int h1, int h2){
        int mult = h2/h1;
        int *bin = new int[n];
        int index = 0;
        for(int i=0;i<n;i+=mult){
//            cout<<i<<endl;
            bin[index++] = st_hist_sum.query(i,i+mult);
        }
//        for(int i=0;i<index;i++)
//            cout<<bin[i]<<" ";
    }
    
    
    
};

#endif /* histogram_h */
