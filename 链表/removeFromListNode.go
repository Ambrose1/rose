package main

func removeZeroSumSublists(head *ListNode) *ListNode {
	dummy := &ListNode{Val:0}
	dummy.Next = head;
	seen := map[int]*ListNode{}
	prefix := 0
	for node:=dummy; node != nil; node = node.Next {
		prefix += node.Val
		seen[prefix] = node
	}
	prefix = 0
	for node:= dummy; node != nil; node = node.Next {
		prefix += node.Val
		node.Next = seen[prefix].Next
	}
	return dummy.Next
}

1,2,-3,3,1

{0:-3,1:1,3:3,4:1}

0 3 