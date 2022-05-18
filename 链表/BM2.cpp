

struct ListNode {
 	int val;
 	struct ListNode *next;
     ListNode(int x):val(x),next(nullptr){};
  };


class Solution {
public:
    /**
     * 
     * @param head ListNode类 
     * @param m int整型 
     * @param n int整型 
     * @return ListNode类
     */
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        // write code here
        ListNode* dummyHead = new ListNode(-1);
        dummyHead->next = head;
        ListNode* pre = dummyHead;
        for(int i=0;i<m-1;i++){
            pre=pre->next;
        }
        
        ListNode *last = pre;
        for(int i=0; i<n-m+1; i++){
            last = last->next;
        }
        
//         截取子链表
        ListNode* leftNode = pre->next;
        ListNode* second = last->next;
        
//         切断链接
        pre->next = nullptr;
        last->next = nullptr;
        
        reserve(leftNode);
        
        pre->next = last;
        leftNode->next = second;
        return dummyHead->next;
    }
    
    void reserve(ListNode* head){
        ListNode* prev = nullptr;
        ListNode* node = head;
        while(node) {
            ListNode *next = node->next;
            node->next = prev;
            prev = node;
            node = next;
        }
    }


    // 优化
    ListNode* reverseBetweenN(ListNode* head, int m, int n) {
        // write code here
        ListNode* dummyHead = new ListNode(-1);
        dummyHead->next = head;
        ListNode* pre = dummyHead;
        for(int i=0;i<m-1;i++){
            pre=pre->next;
        }
        
        ListNode* cur = pre->next;
        ListNode* curN = nullptr;
        for(int i=0; i<n-m;i++){
            curN = cur->next;
            cur->next = curN->next;
            curN->next = pre->next;
            pre->next = curN;
        }
        
        return dummyHead->next;
    }
};