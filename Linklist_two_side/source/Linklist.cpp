#include <iostream>
using namespace std;

class LinkList
{
    // friend ostream &operator<<(ostream &cout, LinkList &L);
    // friend istream &operator>>(istream &cin, LinkList &L);

private:
    class node
    {
    public:
        int value;
        node *prev;
        node *next;
        node() : value(0), prev(NULL), next(NULL){};                          // 构造一个值为0，指针指向空的节点
        node(int input_value) : value(input_value), prev(NULL), next(NULL){}; // 构造一个值为value，指针指向空的节点
    };
    int size;
    node *head;
    node *tail;

public:
    LinkList(); // 默认构造函数  创建链表
    LinkList(int data);
    LinkList(const LinkList &L);              // 复制构造函数  创建链表 并把链表L的值赋值给新创建的链表
    ~LinkList();                              // 析构函数  删除链表的值
    int length();                             // 链表长度
    int search(int data);                     // 查找某个数据的下标
    bool insert(int data, int index, int op); // 在某个位置插入新节点 op==0为插入左侧 op==1为插入右侧
    bool easer(int index);                    // 删除某个数据
    bool change(int data, int index);         // 更改某个数据
    void display();                           // 打印链表的每个节点值
    // LinkList &operator=(LinkList L2);         //=重载  不想写了
};

LinkList::LinkList() : size(0), head(NULL), tail(NULL){};
LinkList::LinkList(int data)
{
    node *ptr;
    ptr = new node(data);
    head = ptr;
    tail = ptr;
    size = 1;
}
LinkList::LinkList(const LinkList &L)
{
    size = L.size;
    if (L.size == 0)
        return;
    else
    {
        head = new node(L.head->value);
        node *ptr = head;
        node *temp = L.head->next;
        while (temp != NULL)
        {
            ptr->next = new node(temp->value);
            ptr->next->prev = ptr;
            temp = temp->next;
            ptr = ptr->next;
        }
        tail = ptr;
    }
}
LinkList::~LinkList()
{
    node *ptr = head;
    node *temp = NULL;
    while (ptr != NULL)
    {
        temp = ptr->next;
        delete ptr;
        ptr = temp;
    }
    size = 0;
}
int LinkList::length()
{
    return size;
}
int LinkList::search(int data)
{
    int flag = -1;
    node *ptr = head;
    //    cout<<size<<endl;
    for (int i = 0; i < size; i++)
    {
        if (ptr->value == data)
        {
            flag = i;
            break;
        }
        ptr = ptr->next;
    }
    return flag;
}
bool LinkList::insert(int data, int index, int op)
{
    if (index < 0 || index > size || op < 0 || op > 1)
        return false;
    node *newnode = new node(data);
    if (index == 0 && op == 0) // 插入在头指针前面
    {
        newnode->next = head;
        head->prev = newnode;
        head = newnode;
    }
    else if (index == size - 1 && op == 1) // 插入在为指针后面
    {
        newnode->prev = tail;
        tail->next = newnode;
        tail = newnode;
    }
    else
    {
        node *ptr = head;
        node *temp = NULL;
        for (int i = 0; i < index; i++)
            ptr = ptr->next;
        if (op == 0)
        {
            temp = ptr->prev;
            temp->next = newnode;
            ptr->prev = newnode;
            newnode->prev = temp;
            newnode->next = ptr;
        }
        else
        {
            temp = ptr->next;
            temp->prev = newnode;
            ptr->next = newnode;
            newnode->prev = ptr;
            newnode->next = temp;
        }
    }
    size++;
    return true;
}
bool LinkList::easer(int index)
{
    if (head == NULL || index < 0 || index > size)
        return false;
    bool flag = false;
    node *temp;
    if (index == 0)
    {
        temp = head->next;
        delete head;
        head = temp;
        head->prev=NULL;
        size--;
        flag = true;
    }
    else if (index == size - 1)
    {
        temp = tail->prev;
        delete tail;
        tail = temp;
        tail->next=NULL;
        size--;
        flag = true;
    }
    else
    {
        temp = head;
        for (int i = 0; i < index; i++)
            temp = temp->next;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        size--;
        flag = true;
    }
    return flag;
}
bool LinkList::change(int data, int index)
{
    bool flag = true;
    node *ptr = head;
    if (index < 0 || index > size - 1)
        flag = false;
    for (int i = 0; i < index; i++)
        ptr = ptr->next;
    ptr->value = data;
    return flag;
}
void LinkList::display()
{
    node *ptr = head;
    while (ptr != NULL)
    {
        cout << ptr->value << ' ';
        ptr = ptr->next;
    }
}

int main()
{
    int n, m;
    LinkList L(1);
    cin >> n;
    for (int i = 2; i <= n; i++)
    {
        int k, p;
        cin >> k >> p;
        int index = L.search(k);
        if (index == -1)
        {
            cout << 1 << endl;
            system("pause");
            return 0;
        }
        bool flag = L.insert(i, index, p);
        if (!flag)
        {
            cout << 2 << endl;
            system("pause");
            return 0;
        }
    }
    cin >> m;;
    for (int i = 1; i <= m; i++)
    {
        int k;
        cin >> k;
        int index = L.search(k);
        if (index == -1)
        {
            // cout<<1<<endl;
            // system("pause");
            // return 0;
            
            continue;
        }
        bool flag = L.easer(index);
        //        L.display();
        if (!flag)
        {
            cout << 3 << endl;
            system("pause");
            return 0;
        }
    }
    L.display();
    // system("pause");
    return 0;
}