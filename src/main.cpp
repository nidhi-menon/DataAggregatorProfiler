
//  main.cpp
//  SegmentTree
//
//  Created by Sneha Venkat on 10/3/18.
//  Copyright © 2018 Sneha Venkat. All rights reserved.
//

#include "iostream"
#include "stdc++.h"
#include "dataframe.h"
#include "segment_tree.h"
#include <unordered_map>
#include "histogram.h"
#include "distinct_values.h"
#include "null_values.h"
#include "b_plus_tree.h"
#include "math.h"
#include <chrono>
#include <random>
//#include <math>
//#include "tree_segment.h"
#include <vector>

using namespace std;

// C++ program to find out execution time of
// of functions
#include <algorithm>
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;


float ord_sum(float a[], int l, int r){
    float sum = 0.0;
    for(int i=l;i<r;i++)
        sum+=a[i];
    return sum;
}

float ord_sq_sum(float a[], int l, int r){
    float sum = 0.0;
    for(int i=l;i<r;i++)
        sum+=pow(a[i],2);
    return sum;
}

float ord_xy_sum(float a1[], float a2[], int l, int r){
    float sum = 0;
    for(int i=l;i<r;i++)
        sum+=(a1[i]*a2[i]);
    return sum;
}

float mean(float a[], Segment_Tree st_x_sum,int l,int r){
    float sum = st_x_sum.query(l, r);
    //float sum = ord_sum(a,l,r);
    int n = r-l;
    return sum/n;
}

float rmse(float a[],Segment_Tree st_x_sq_sum,int l,int r){
    float sq_sum = st_x_sq_sum.query(l, r);
    //float sq_sum = ord_sq_sum(a,l,r);
    int n = r-l;
    return sqrt(sq_sum/n);
}

float var(float a[],Segment_Tree st_x_sum,Segment_Tree st_x_sq_sum, int l, int r){
    int n = r-l;
    float sq_sum = st_x_sq_sum.query(l, r);
    //float sq_sum = ord_sq_sum(a,l,r);
    return (sq_sum-mean(a,st_x_sum,l,r))/n;
}

float stdev(float a[],Segment_Tree st_x_sum,Segment_Tree st_x_sq_sum,int l,int r){
    return sqrt(var(a,st_x_sum,st_x_sq_sum,l,r));
}

float kur(Segment_Tree st_x_sum,Segment_Tree st_x_sq_sum,float a[],int l,int r){
    float avg = mean(a,st_x_sum,l,r);
    float st_dev = stdev(a,st_x_sum,st_x_sq_sum,0,6);
    int n = r-l;
    float result = 0.0;
    for(int i=l;i<r;i++){
        float eq = (a[i]-avg)/st_dev;
        result+=pow(eq,4);
    }
    return result/n - 3.0;
}

float covar(float b1[],float b2[],Segment_Tree st_xy_sum, Segment_Tree st_x_sum_1,Segment_Tree st_x_sum_2,int l,int r){
    float sum_1 = st_x_sum_1.query(l, r);
    float sum_2 = st_x_sum_2.query(l, r);
    float sum = st_xy_sum.query(l, r);
//    float sum = ord_xy_sum(b1,b2,l,r);
//    float sum_1 = ord_sum(b1,l,r);
//    float sum_2 = ord_sum(b2,l,r);
    int n = r-l;
    return (sum/n)-((sum_1*sum_2)/pow(n,2));
}

float slr(float b1[],float b2[],Segment_Tree st_xy_sum, Segment_Tree st_x_sum_1,Segment_Tree st_x_sum_2,Segment_Tree st_x_sq_sum_1,int l,int r){
    
    return covar(b1,b2,st_xy_sum,st_x_sum_1,st_x_sum_2,l,r)/var(b1,st_x_sum_1,st_x_sq_sum_1,l,r);
}

float corr(float x[],float y[],Segment_Tree st_x_sum_1,Segment_Tree st_x_sum_2,Segment_Tree st_x_sq_sum_1,Segment_Tree st_x_sq_sum_2,Segment_Tree st_xy_sum,int l,int r){
    
    float sum_xy = st_xy_sum.query(l, r);
    float sum_x = st_x_sum_1.query(l, r);
    float sum_y = st_x_sum_2.query(l, r);
//    float sum_xy = ord_xy_sum(x, y, l, r);
//    float sum_x = ord_sum(x, l, r);
//    float sum_y = ord_sum(y, l, r);
    
    float sq_sum_x = pow(sum_x,2);
    float sq_sum_y = pow(sum_y,2);
    
//    float x_sq_sum = st_x_sq_sum_1.query(l, r);
//    float y_sq_sum = st_x_sq_sum_2.query(l, r);
    
    float x_sq_sum = ord_sq_sum(x, l, r);
    float y_sq_sum = ord_sq_sum(y, l, r);
    
    int n = r-l;
    float num = (n*sum_xy)-(sum_x*sum_y);
    float den_1 = sqrt(n*x_sq_sum-sq_sum_x);
    float den_2 = sqrt(n*y_sq_sum-sq_sum_y);
    float den = den_1*den_2;
    return num/den;
    
}

int main(int argc, const char * argv[]) {
    //float check[] = {1.0, 2.5, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
    
//    float b[] = {0,0,0,5,5,5,10,10,10,15,15,15,20,20,20};
//    float b1[] = {0,0,0,5,5,5,10,10,10,15,15,15,20,20,20};
//    float b2[] = {0,0,0,5,5.5,5,10,10.5,10,15,15.5,15,20,20,20};
//    float c[] = {-1,0,3,4,-1,6,-1,10,20,-1};
    float check[] = {0.0,0.0,0.0,5.0,5.0,5.0,10.0,10.0,10.0,15.0,15.0,15.0,20.0,20.0,20.0};
    int len_check = sizeof(check)/sizeof(*check);
    
    
    
    float a[10000];
    float b[10000];
    float b1[10000];
    float b2[10000];
    float c[10000];
    int d[10000];
    int count_arr[10000];
    
    for(int i=0;i<9999;i++){
        //srand(50);
        a[i] = rand()/float(RAND_MAX)*9999.f+1.f;
        b[i] = rand()/float(RAND_MAX)*9999.f+1.f;
        b1[i] = rand()/float(RAND_MAX)*9999.f+1.f;
        b2[i] = rand()/float(RAND_MAX)*9999.f+1.f;
        c[i] = rand()/float(RAND_MAX)*9999.f+1.f;
        count_arr[i] = floor(a[i]);
    }
    
    int len_a = sizeof(a)/sizeof(*a);
    int len_b = sizeof(b)/sizeof(*b);
    int len_b1 = sizeof(b1)/sizeof(*b1);
    int len_b2 = sizeof(b2)/sizeof(*b2);
    int len_c = sizeof(c)/sizeof(*c);
    int len_d = sizeof(d)/sizeof(*d);
    int len_count_arr = sizeof(count_arr)/sizeof(*count_arr);
    
    Histogram h;
    Count_Distinct dis;
    Count_Null n;
    
    float *max_e= max_element(a,a+len_a);
    float *min_e= min_element(a,a+len_a);
    
    
    int w = 5;
    
//    /*Traditional: Time taken by histogram function*/
//    int len_bins =  ((12-0)/3)+1;
    int len_bins =  ((floor(*max_e)-floor(*min_e))/w)+1;
    int bins[len_bins];
    for(int i=0;i<=len_bins;i++)
        bins[i] = 0;
//    h.count_hist_normally(bins,check, len_check, 0,12 ,3 );
    auto start = high_resolution_clock::now();
    h.count_hist_normally(bins,a, len_a, *min_e,*max_e ,w );
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by normal histogram function: "<< duration.count() << " microseconds" << endl<<endl;
    cout<<endl;

    /*Segment tree: Time taken by histogram function*/
    cout<<"Segment tree: Count Histogram between "<<0<<" and "<<10000<<" : ";
    cout<<endl;
    float *hist_bins = new float[floor(*max_e)];
    hist_bins = h.create_count_tree(count_arr,len_count_arr,floor(*min_e),floor(*max_e));
    Segment_Tree st_hist_sum(floor(*max_e));
    st_hist_sum.build_x_sum(hist_bins);
    start = high_resolution_clock::now();
    h.query_count_tree(st_hist_sum,count_arr,len_count_arr,floor(*min_e),floor(*max_e),w);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by segment tree histogram function: "<< duration.count() << " microseconds" << endl<<endl;
    cout<<endl;

    /*Segment tree: Time taken by base width histogram function*/
    cout<<"Segment tree: Count Base Histogram between "<<0<<" and "<<10000<<" : ";
    cout<<endl;
    float *hist_base_bins = new float[floor(*max_e)];
    hist_base_bins = h.width_histogram(a,len_a,floor(*min_e),floor(*max_e),5);
    Segment_Tree base_hist_sum(floor(*max_e));
    base_hist_sum.build_x_sum(hist_base_bins);
    start = high_resolution_clock::now();
    h.query_base_tree(base_hist_sum,a,len_a,floor(*min_e),floor(*max_e),50);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by segment tree histogram function: "<< duration.count() << " microseconds" << endl<<endl;
    cout<<endl;

    /*Traditional: Time taken by base height histogram function*/
    cout<<"Traditional: Count height Histogram between "<<0<<" and "<<10000<<" : ";
    cout<<endl;
    start = high_resolution_clock::now();
    h.normal_equal_height(a,len_a,floor(*min_e),floor(*max_e),6);
    //h.normal_equal_height(check,len_check,0,20,3);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by segment tree histogram function: "<< duration.count() << " microseconds" << endl<<endl;
    cout<<endl;

    /*Segment Tree: Time taken by base height histogram function*/
    cout<<"Segment Tree: Count height Histogram between "<<0<<" and "<<10000<<" : ";
    cout<<endl;
    float* height_bins = h.normal_equal_height(a,len_a,floor(*min_e),floor(*max_e),5);
    Segment_Tree height_hist_sum(floor(*max_e));
    height_hist_sum.build_x_sum(height_bins);
//    for(int i=0;i<20;i++)
//        cout<<height_bins[i]<<" ";
    start = high_resolution_clock::now();
    h.st_equal_height(height_hist_sum,a, len_a, floor(*max_e), floor(*min_e),5, 50);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by segment tree histogram function: "<< duration.count() << " microseconds" << endl<<endl;
    cout<<endl;


    /*Using segment tree: Null and distinct values*/
    cout<<"Segment tree: No. of distinct values between "<<0<<" and "<<10000<<" : ";
    dis.create_distinct_tree(b,len_b,0,len_b);
    cout<<endl;
    cout<<"Segment tree: No. of null values between "<<0<<" and "<<10000<<" : ";
    n.create_null_tree(c,len_c,0,len_c);
    cout<<endl;

    /*Using segment tree: Null and distinct values*/
    cout<<"Traditional: No. of distinct values between "<<0<<" and "<<10000<<" : ";
     start = high_resolution_clock::now();
    dis.count_distinct_normally(b,len_b,0,len_b);
     stop = high_resolution_clock::now();
    cout<<endl;
     duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
    << duration.count() << " microseconds" << endl<<endl;

    cout<<"Traditional: No. of null values between "<<0<<" and "<<10000<<" : ";
    start = high_resolution_clock::now();
    n.count_null_normally(c,len_c,0,len_c);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<endl;
    cout << "Time taken by function: "
    << duration.count() << " microseconds" << endl<<endl;
    
    /*Time taken to build various types of segment trees*/
    start = high_resolution_clock::now();
    Segment_Tree st_x_sum(len_a);//Segment tree object
    st_x_sum.build_x_sum(a);//build sum(x) tree
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by build_x_sum: "
    << duration.count() << " microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    Segment_Tree st_x_sum_1(len_b1);//Segment tree object
    st_x_sum_1.build_x_sum(b1);//build sum(x) tree
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by build_x_sum function: "
    << duration.count() << " microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    Segment_Tree st_x_sum_2(len_b2);//Segment tree object
    st_x_sum_2.build_x_sum(b2);//build sum(x) tree
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by build_x_sum function: "
    << duration.count() << " microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    Segment_Tree st_x_sq_sum(len_a);//Segment tree object
    st_x_sq_sum.build_x_square_sum(a);//build sum(x^2) tree
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by build_x_square_sum function: "
    << duration.count() << " microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    Segment_Tree st_x_sq_sum_1(len_b1);//Segment tree object
    st_x_sq_sum_1.build_x_square_sum(b1);//build sum(x^2) tree
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by build_x_square_sum function: "
    << duration.count() << " microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    Segment_Tree st_x_sq_sum_2(len_b2);//Segment tree object
    st_x_sq_sum_2.build_x_square_sum(b2);//build sum(x^2) tree
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by build_x_square_sum function: "
    << duration.count() << " microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    Segment_Tree st_xy_sum(len_b1);//Segment tree object
    st_xy_sum.build_xy_sum(b1,b2);//build sum(x^2) tree
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by build_xy_sum function: "
    << duration.count() << " microseconds" << endl<<endl;

    /*Time taken for different operations*/
    start = high_resolution_clock::now();
    cout<<"Mean: "<<mean(a,st_x_sum,0,len_a)<<endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
    << duration.count() << " microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    cout<<"RMSE: "<<rmse(a,st_x_sq_sum,0,len_a)<<endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
    << duration.count() << " microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    cout<<"Variance: "<<var(a,st_x_sum,st_x_sq_sum,0,len_a)<<endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
    << duration.count() << " microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    cout<<"STD: "<<stdev(a,st_x_sum,st_x_sq_sum,0,len_a)<<endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
    << duration.count() << " microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    cout<<"Kurtosis: "<<kur(st_x_sum,st_x_sq_sum,a,0,len_a)<<endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
    << duration.count() << " microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    cout<<"Covariance: "<<covar(b1,b2,st_xy_sum,st_x_sum_1,st_x_sum_2,0,len_b1)<<endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
    << duration.count() << " microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    cout<<"Simple Linear Regression: "<<slr(b1,b2,st_xy_sum,st_x_sum_1,st_x_sum_2,st_x_sq_sum_1,0,len_b1)<<endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
    << duration.count() << " microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    cout<<"Correlation: "<<corr(b1,b2,st_x_sum_1,st_x_sum_2,st_x_sq_sum_1,st_x_sq_sum_2,st_xy_sum,0,len_b)<<endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
    << duration.count() << " microseconds" << endl<<endl;
    
//    Histogram h;
//    float *hist;
//    hist = h.createBins(b,5,len_b);
//    int len_hist_1 = sizeof(hist)/sizeof(hist[0]);
//    Segment_Tree width_hist(len_hist_1);
//    width_hist.build_x_sum(hist);
//    cout <<width_hist.query(0, 2)<<endl;//print the sum in range(0,2) index-based
//
//    DataFrame d(10,10);
//    d.print_dataframe();
//    cout<<endl;
//    int start=0,end=7;
//    float chunk[(end-start)];
//    d.return_column(0,start,end,chunk);
//
//    int n1 = sizeof(a)/sizeof(a[0]);
//    int n2 = sizeof(chunk)/sizeof(chunk[0]);
//
//    /*sum(x)*/
//    Segment_Tree st_x_sum(n2);//Segment tree object
//    st_x_sum.build_x_sum(chunk);//build sum(x) tree
//    cout <<st_x_sum.query(0, 6)<<endl;//print the sum in range(0,2) index-based
//
//    /*sum(x^2)*/
//    Segment_Tree st_x_sq_sum(n1);//Segment tree object
//    st_x_sq_sum.build_x_square_sum(a);//build sum(x^2) tree
//    cout <<st_x_sq_sum.query(0, 3)<<endl;//print the sum in range(0,2) index-based
//
//
//    /*sum(xy)*/
//    Segment_Tree st_xy_sum(n1);//Segment tree object
//    st_xy_sum.build_xy_sum(a,a);//build sum(x^2) tree
//    cout <<st_xy_sum.query(0, 3)<<endl;//print the sum in range(0,2) index-based
//
//    //HashMap to store segment tree references
//    Segment_Tree *ptr_x_sum = &st_x_sum;
//    Segment_Tree *ptr_x_sq_sum = &st_x_sq_sum;
//    Segment_Tree *ptr_xy_sum = &st_xy_sum;
//    unordered_map<string,Segment_Tree*> umap;
//    umap["x_sum"] = ptr_x_sum;
//    umap["x_square_sum"] = ptr_x_sq_sum;
//    umap["xy_sum"] = ptr_xy_sum;
    

    
    
    BTree t(3); // A B-Tree with minium degree 3
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);
    
    cout << "Traversal of the constucted tree is ";
    t.traverse();
    
    int k = 6;
    (t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    
    k = 15;
    (t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present";

    cout<<endl;
    
    
    
    return 0;
}
