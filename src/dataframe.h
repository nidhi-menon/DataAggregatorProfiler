//
//  dataframe.h
//  SegmentTree
//
//  Created by Sneha Venkat on 10/3/18.
//  Copyright © 2018 Sneha Venkat. All rights reserved.
//

#ifndef dataframe_h
#define dataframe_h
#include "iostream"


#endif /* dataframe_h */

using namespace std;

class DataFrame{
    
private:
    int row;
    int column;
    float **df;

public:
    DataFrame(int r, int c){
        row = r;
        column = c;
        df = new float*[row];
        for(int i = 0; i < row; ++i)
            df[i] = new float[column];
        //float df[r][c];
        for(int i=0;i<row;i++){
            for(int j=0;j<column;j++){
                df[i][j] = ((float) i + (float) j)/float(column);
            }
        }
    }
    
    void print_dataframe(){
        for(int i=0;i<row;i++){
            for(int j=0;j<column;j++){
                cout<<df[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    
    void print_row(int row_no){
        for(int j=0;j<column;j++)
            cout<<df[row_no][j]<<" ";
    }
    
    void print_column(int col_no){
        for(int i=0;i<row;i++)
            cout<<df[i][col_no]<<endl;
    }
    
    void return_column(int col_no,int m,int n,float a[]){
        for(int i=m;i<n;i++)
        {
            a[i] = df[i][col_no];
        }
    }
};
