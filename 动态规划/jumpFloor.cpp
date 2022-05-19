#include<iostream>
using namespace std;

class Solution {
public:
    int jumpFloor(int number) {
        int a=0,b=0,c=1;
        for(int i=1;i<=number; i++){
            a = b;
            b = c;
            c = a+b;
        }
        return c;
        
    }
};