#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        int x = m-1, y=n-1,j=m+n-1;
        if(n==0)return ;
        if(m==0){
            for(int i=0; i<n; i++){
                A[i] = B[i];
            }
            return;
        }
        
        while(x >=0 && y>=0){
            if(A[x] > B[y]) {
                A[j] = A[x];
                x--;
            }else {
                A[j] = B[y];
                y--;
            }
            j--;
        }
        if(y>=0){
            while(j >= 0){
                A[j] = B[y];
                y--;
                j--;
            }
        }
    }
};