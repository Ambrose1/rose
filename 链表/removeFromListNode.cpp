#include<iostream>


ListNode* removeFromList(ListNode *head) {
	ListNode *dummy = new ListNode(0);
	dummy->next = head;
	unordered_map<int, ListNode*> map;
	int prefix = 0;
	for (ListNode *node= dummy; node; node=node->next) {
		prefix += node.val;
		map[prefix] = node;
	}
	prefix = 0;
	for (ListNode *node=dummy; node; node=node->next) {
		prefix += node->next;
		node->next = map[prefix];
	}
}
void main(){

}