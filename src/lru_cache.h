//
//  lru_cache.h
//  SegmentTree
//
//  Created by Sneha Venkat on 12/12/18.
//  Copyright © 2018 Sneha Venkat. All rights reserved.
//

#ifndef lru_cache_h
#define lru_cache_h



/* We can use stl container list as a double
 ended queue to store the cache keys, with
 the descending time of reference from front
 to back and a set container to check presence
 of a key. But to fetch the address of the key
 in the list using find(), it takes O(N) time.
 This can be optimized by storing a reference
 (iterator) to each key in a hash map. */
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define CHUNK_SIZE 10

class LRUCache
{
    // store keys of cache
    list<int> dq;
    
    // store references of key in cache
    unordered_map<int, list<int[]>::iterator> ma;
    int csize; //maximum capacity of cache
    
public:
    LRUCache(int[]);
    void refer(int[]);
    void display();
};

LRUCache::LRUCache(int n)
{
    csize = n;
}

/* Refers key x with in the LRU cache */
void LRUCache::refer(int x)
{
    // not present in cache
    if (ma.find(x) == ma.end())
    {
        // cache is full
        if (dq.size() == csize)
        {
            //delete least recently used element
            ofstream outfile;
            outfile.open("blah.txt");
            int last = dq.back();
            int data = dq.back();
            // write inputted data into the file.
            outfile << data << endl;
            outfile.close();
            dq.pop_back();
            ma.erase(last);
        }
    }
    
    // present in cache
    else
        dq.erase(ma[x]);
    
    // update reference
    dq.push_front(x);
    ma[x] = dq.begin();
}

// display contents of cache
void LRUCache::display()
{
    for (auto it = dq.begin(); it != dq.end();
         it++)
        cout << (*it) << " ";
    
    cout << endl;
}

// Driver program to test above functions
//int main()
//{
//    LRUCache ca(4);
//
//    ca.refer(1);
//    ca.refer(2);
//    ca.refer(3);
//    ca.refer(1);
//    ca.refer(4);
//    ca.refer(5);
//    ca.display();
//
//    return 0;
//}
// This code is contributed by Satish Srinivas

#endif /* lru_cache_h */
