/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> v;
    void print(ListNode* now)
    {
        if(now==NULL) return;
        print(now->next);
        v.push_back(now->val);
    }
    vector<int> printListReversingly(ListNode* head) {
        print(head);
        return v;
    }
};
