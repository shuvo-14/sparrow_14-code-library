#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<queue>
#include<cstring>
#include<string>
#include<stack>
#include<set>
#include<unordered_set>
#include<map>
#include<unordered_map>

using namespace std;
struct node{
    int data;
    node* next;
    node(int val)
    {
        data = val;
        next = NULL;
    }
};
void addEnd(node* &head, int val)
{
    node* tmp = new node(val);
    if(head == NULL)
    {
        head = tmp;
        return;
    }
    node* cur = head;
    while(cur->next != NULL) cur = cur->next;
    cur->next = tmp;
}
void addFront(node* &head, int val)
{
    node* tmp = new node(val);
    if(head == NULL) 
    {
        head = tmp;
        return;
    }
    tmp->next = head;
    head = tmp;
}
void display(node* head)
{
    node* cur = head;
    while(cur != NULL) cout << cur->data << " ",cur = cur->next;
    cout << endl;
}
node* reverse(node* &head)
{
    node* cur = head;
    node* prev = NULL;
    node* nxt;
    while(cur != NULL)
    {
        nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    return prev;
}
node* RecursiveReverse(node* &head)
{
    if(head->next == NULL or head == NULL) return head;
    node* newHead = RecursiveReverse(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;
}
node* ReverseK(node* &head, int k)
{
    node* cur = head;
    node* prev = NULL;
    node* nxt;
    int cnt = 0;
    while(cnt < k and cur != NULL)
    {
        nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
        cnt++;
    }
    node* curHead = NULL;
    if(nxt != NULL) 
    {
        curHead =  ReverseK(nxt,k);
        head->next = curHead;
    }
    return prev;
}
void makeCycle(node* head, int pos)
{
    node* cur = head;
    node* startPoint = head;
    int cnt = 1;
    while(cur->next != NULL)
    {
        if(cnt == pos)
        {
            startPoint = cur;
        }
        cnt++;
        cur = cur->next;
    }
    cur->next = startPoint;
}
int detectCycle(node* head)
{
    node* fast = head;
    node* slow = head;

    while(fast != NULL and fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow) return 1;
    }
    return 0;
}
void RemoveCycle(node* &head)
{
    node* fast = head;
    node* slow = head;
    do{
        fast = fast->next->next;
        slow = slow->next;
    }while(fast != slow);

    fast = head;
    while(fast->next != slow->next)
    {
        fast = fast->next;
        slow = slow->next;
    }
    slow->next = NULL;
}
int main()
{
    node* head = NULL;
    for(int i = 1; i <= 6; i++) addEnd(head,i);
    display(head);
    makeCycle(head,3);
    cout << detectCycle(head) << endl;
    RemoveCycle(head);
    cout << detectCycle(head) << endl;
    return 0;
}
