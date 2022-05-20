#include<iostream>
#include<vector>
using namespace std;
/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 * };
 */

class Solution {
public:
    /**
     * 
     * @param head ListNode类 the head node
     * @return ListNode类
     */
    ListNode* sortInList(ListNode* head) {
        // write code here
        if(head == nullptr || head->next == nullptr)return head;
        ListNode *fast = head->next, *slow = head;
        while(fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }
        ListNode *tmp = slow->next;
        slow->next = nullptr;
        
        ListNode *left = sortInList(head);
        ListNode *right = sortInList(tmp);
        
        ListNode *h = new ListNode(0);
        ListNode *ans = h;
        
        while(left != nullptr && right != nullptr) {
            if(left->val < right->val){
                h->next = left;
                left = left->next;
            }else {
                h->next = right;
                right = right->next;
            }
            h=h->next;
        }
        h->next = left != nullptr ?left : right;
        return ans->next;
        
    }
};