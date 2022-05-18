#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int fib(int n) {
        if(n<2)return n;
        int MOD = 1000000007;
        int a = 0, b = 0,c = 1;
        for(int i=2; i<=n; i++){
            a = b;
            b = c;
            c = (a+b)%MOD;
        }
        return c;

    }
};