// 线段树
#include <iostream>
#include <vector>
using namespace std;

class NumArray {
    private:
        vector<int>  segmentTree;
        int n;
    
    void build(int node, int start, int end, vector<int> &nums) {
        // 叶子结点
        if(start == end) {
            segmentTree[node] = nums[start];
            return;
        }

        int end_new = start + (end-start)/2;
        build(node * 2+1,start,end_new,nums);
        build(node * 2+2,end_new+1,end,nums);
        segmentTree[node] = segmentTree[node*2+1] + segmentTree[node *2 +2];
    }

    void change(int index, int val, int node, int s, int e) {
        if(s == e) {
            segmentTree[node] = val;
            return;
        }

        int m = (s+e)/2;
        if (index <= m) {
            change(index,val,node*2+1, s,m);
        } else {
            change(index,val,node*2+2,m+1,e);
        }
        segmentTree[node] = segmentTree[node * 2+1] +segmentTree[node * 2 +2];
    }
}