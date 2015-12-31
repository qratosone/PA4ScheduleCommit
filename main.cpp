
#include<iostream>
#include<string>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#define MAXN 10000005
#define  InHeap(n, i)      ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) )
#define  Parent(i)         ( ( i - 1 ) >> 1 )
#define  LastInternal(n)   Parent( n - 1 )
#define  LChild(i)         ( 1 + ( ( i ) << 1 ) )
#define  RChild(i)         ( ( 1 + ( i ) ) << 1 )
#define  ParentValid(i)    ( 0 < i )
#define  LChildValid(n, i) InHeap( n, LChild( i ) )
#define  RChildValid(n, i) InHeap( n, RChild( i ) )
#define  Smaller(PQ, i, j)  (  (PQ[i]) < (PQ[j])  ? (i) : (j) )
#define  ProperParent(PQ, n, i) \
( RChildValid(n, i) ? Smaller( PQ, Smaller( PQ, i, LChild(i) ), RChild(i) ) : \
( LChildValid(n, i) ? Smaller( PQ, i, LChild(i) ) : i ))

using namespace std;
const int SZ = 1<<20;
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;
class Task {
public:
    long long prior;
    char data[10];
    Task() {
        prior = 0;
    }
    ~Task(){

    }
    Task(long long  p, char* d) {
        prior = p;
        strcpy(data,d);
    }
    bool operator < (const Task &a)
    {
        if (prior < a.prior)
            return true;
        else if (prior == a.prior)
        {
            int temp = 0;
            while (data[temp] == a.data[temp])
            {
                temp++;
            }
            if (data[temp] < a.data[temp])
                return true;
        }
        return false;
    }
    bool HigherPri(Task t2) {
        if (prior<t2.prior)
        {
            return true;
        }
        else if(prior==t2.prior){
            if (data[0] < t2.data[0]) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
};
class Heap {
private:
    Task *data;
    int size;
public:
    Heap(int length_input) {
        data = new Task[length_input];
        size = 0;
    }
    ~Heap() {
        delete[] data;
    }
    void output(){
        cout<<size<<" ";
        for (int i = 0; i <size; ++i) {
            printf("%lld %s ",data[i].prior,data[i].data);
        }
        cout<<endl;
    }
    void push(Task value) {
        data[size] = value;
        int current = size;
        int father = (current - 1) / 2;
        while (data[current] .HigherPri(data[father])) {
            swap(data[current], data[father]);
            current = father;
            father = (current - 1) / 2;
            if (father < 0)break;
        }
        size++;
    }
    //void output() {
    //	for (int i = 0; i < size; i++) {
    //		cout << data[i] << " ";
    //	}
    //	cout << endl;
    //}

    Task top() {
        return data[0];
    }
    void update(int pos, int n) {
        int lchild = 2 * pos + 1, rchild = 2 * pos + 2;
        int max_value = pos;
        if (lchild < n && data[lchild].HigherPri( data[max_value])) {
            max_value = lchild;
        }
        if (rchild < n && data[rchild].HigherPri(data[max_value])) {
            max_value = rchild;
        }
        if (max_value != pos) {
            swap(data[pos], data[max_value]);
            update(max_value, n);
        }
    }
    void pop() {
        swap(data[0], data[size - 1]);
        size--;
        update(0,size);
    }
    void updateUp(){
        update(0,size);
    }
    void setPri(){
        data[0].prior*=2;
    }
    void heap_sort() {
        for (int i = size - 1; i >= 1; i--) {
            swap(data[i], data[0]);
            update(0, i);
        }
    }
    bool isEmpty(){
        if(size==0)return true;
        else return false;
    }
    void swapOnly(){
        swap(data[0],data[size-1]);
        size--;
    }
    int percolateDown(int n, int i)
    {
        int j;
        j = ProperParent(data, n ,i);
        while (i != j)
        {
            swap(data[i], data[j]);
            i = j;
            j = ProperParent(data, n ,i);
        }

        return i;
    }
    void percolate(){
        percolateDown(size,0);
    }
};
int main() {
    int n, m;
    scanf("%d %d",&n,&m);
    Heap TaskList(4000000);
    long long inputP;
    char inputD[10];
    for (int i = 0; i < n; i++)
    {
        scanf("%lld %s",&inputP,inputD);
        Task t(inputP, inputD);
        TaskList.push(t);
    }
    //TaskList.output();
    //long long maxpri = pow(2, 32);
    Task temp;
    int count_1 = 0;
    int size = n;
    while (size > 0 && count_1 < m)
    {
        count_1++;
        temp = TaskList.top();
        printf("%s\n",temp.data);
        //printf("%lld %s\n",temp.prior,temp.data);
        //cout<<"first ";
        //TaskList.output();
        //TaskList.pop();
        //size--;
        temp.prior *= 2;
        TaskList.setPri();
        //cout<<"mid ";
        //TaskList.output();
        if(temp.prior>=4294967296){
            TaskList.pop();
            size--;
        }
        TaskList.percolate();
        //cout<<"second ";
        //TaskList.output();
        //TaskList.updateUp();

    }

    return 0;
}