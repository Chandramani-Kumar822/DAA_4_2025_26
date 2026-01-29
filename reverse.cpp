#include<iostream>
using namespace std;
class ListNode{
    public:
    int val;
    ListNode* next;
    ListNode(int data){
        val=data;
        next=NULL;
    }

};
class Main {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* temp = head;
        ListNode* prev = NULL;
        while(temp!=NULL){
            ListNode* front= temp->next;
            temp->next=prev;
            prev=temp;
            temp=front;
        }
        return prev;
        
    }
};