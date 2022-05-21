#include<iostream>
#include<vector>
using namespace std;
// Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    /**
     * 
     * @param head1 ListNode类 
     * @param head2 ListNode类 
     * @return ListNode类
     */
    ListNode* reverse(ListNode *node){
        ListNode*prev = nullptr;
        while(node){
            ListNode* tmp = node->next;
            node->next = prev;
            prev = node;
            node = tmp;
        }
        return prev;
    }
    
    
    ListNode* addInList(ListNode* head1, ListNode* head2) {
        // write code here 
//         题目没说前导0的数字
        if(head1->val == 0)return head2;
        if(head2->val == 0)return head1;
        ListNode* newHead1 = reverse(head1);
        ListNode* newHead2 = reverse(head2);
        
        int m = 0;//进位
        ListNode* ans = new ListNode(0);
        ListNode *cur = ans;
        while(newHead1 || newHead2){
            int val1 = newHead1 ? newHead1->val : 0;
            int val2 = newHead2 ? newHead2->val : 0;
            int val = val1 + val2 + m;
            if(val>9){
                m = 1;
                val = val%10;
            }else {
                m=0;
            }
            ListNode *next = new ListNode(val);
            cur->next = next;
            cur=cur->next;
            if(newHead1)newHead1 = newHead1->next;
            if(newHead2)newHead2 = newHead2->next;
        }
        if(m==1){
            ListNode* node = new ListNode(1);
            cur->next = node;
        }
        
        return reverse(ans->next);
//         return
        
        
        
    }
};