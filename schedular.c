#include <stdio.h>
#include <stdlib.h>

#define MAXQUEUE 20
#define TRUE 1
#define FALSE 0

typedef struct process
{
    float time;
    char name[10];
    int priority;
}QueueElement;

typedef struct queue{
    int count;
    int front;
    int rear;
    QueueElement items[MAXQUEUE];
}Queue;

void CreateQueue(Queue *q)
{
    q->count = 0;
    q->front = 1;
    q->rear = 0;
}

int IsQueueEmpty(Queue *q)
{
    if(q->rear < q->front)
        return(TRUE);
    else
        return(FALSE);
}

int IsQueueFull(Queue *q)
{
    if(q->rear == MAXQUEUE -2)
        return(TRUE);
    else
        return(FALSE);
}

void Append(Queue *q, QueueElement x)
{
    if(IsQueueFull(q))
     {
        printf("Queue Full\n");
        exit(1);
     }
     else
    {
        q->items[++(q->rear)] = x;
        q->count++;
        heapSort(q);
     }
}

void Serve(Queue *q, QueueElement *x)
{
    if(IsQueueEmpty(q))
    {
        printf("queue i empty,under flown");
        exit(1);
    }
        *x=q->items[(q->front)++];
        q->count--;
}


void swap(QueueElement *a, QueueElement *b )
{
    QueueElement temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//function to get right child of a node of a tree
int rightChild(Queue *q, int index)
{
    if((((2*index)+1) < MAXQUEUE) && (index >= 1))
    return (2*index)+1;
    return -1;
}

//function to get left child of a node of a tree
int leftChild(Queue *q, int index)
 {
    if(((2*index) < MAXQUEUE) && (index >= 1))
    return 2*index;
    return -1;
}

void min_heapify(Queue *q, int index)
{
    int indexLeftChild = leftChild(q, index);
    int indexRightChild = rightChild(q, index);

  // finding smallest among index, left child and right child
    int smallest = index;

    if ((indexLeftChild <= q->rear) && (indexLeftChild>0))
    {
        if (q->items[indexLeftChild].priority <= q->items[smallest].priority)
        {
            if (q->items[indexLeftChild].priority == q->items[smallest].priority)
            {
                if (q->items[indexLeftChild].time < q->items[smallest].time)
                {
                    smallest = indexLeftChild;
                }
            }
            else
            {
                smallest = indexLeftChild;
            }
      }
    }
    if ((indexRightChild <= q->rear && (indexRightChild>0)))
    {
        if (q->items[indexRightChild].priority <= q->items[smallest].priority)
        {
            if (q->items[indexRightChild].priority == q->items[smallest].priority)
            {
                if (q->items[indexRightChild].time < q->items[smallest].time)
                {
                    smallest = indexRightChild;
                }
            }
            else
            {
                smallest = indexRightChild;
            }
        }
    }
  // smallest is not the node, node is not a heap
    if (smallest != index)
    {
        swap(&q->items[index], &q->items[smallest]);
        min_heapify(q, smallest);
    }
}

void build_min_heap(Queue *q)
{
    int i;
    for(i=q->rear/2; i>=1; i--)
    {
        min_heapify(q, i);
    }
}

QueueElement delete_min(Queue *q)
{
    QueueElement minimum = q->items[q->front];
    q->items[q->front] = q->items[q->rear];
    q->rear--;
    min_heapify(q, q->front);

    return minimum;
}

void heapSort(Queue *q){
    build_min_heap(q);
}

int main()
{
    Queue Q;
    CreateQueue(&Q);

    char name[20];
    int  priority , no = 0 , i = 1;
    float time , waitingT = 0 , turnaroundT = 0 , totturnT = 0, totwaitT = 0;

    printf("\n");
    printf("\t   \t         __   __   __   __  __  __  __      __        __  _ _            __  __        \n");
    printf("\t   \t        |__| |__| |  | |   |__ |__ |__     |__  |__| |__   | | |  | |   |__ |__|       \n");
    printf("\t   \t        |    | |  |__| |__ |__  __| __|     __| |  | |__  _|_| |__| |__ |__ | |        \n");
    printf("\t   \t        ------------------------------------------------------------------------       \n\n\n");

    printf("\t\t\tInput number of processes : ");
    scanf(" %d",&no);

    QueueElement sort;

    while(i!=no+1)
    {
        printf("\n\t\t\t\tProcess-%d\n\t\t\t\tProcess name : ",i);
        scanf(" %s",Q.items[i].name);

        printf("\t\t\t\tProcess priority : ");
        scanf("%d",&Q.items[i].priority);
        if(Q.items[i].priority<0 || Q.items[i].priority==0)
        {
            printf("\t\t\tpriority number can not be negative vale or zero!!\n");
            continue;
        }
        printf("\t\t\t\tBurst Time (s) : ");
        scanf("%f",&Q.items[i].time);
        Append(&Q,Q.items[i]);
        i++;
    }

    printf("\n\n\tNumber \tProcess Name \tPriority \tBurst time (s)\t\tWaiting Time (s) \tTurnaround time (s)\n");

    for(int i = 1 ; i<=no ;i++)
    {
        sort = delete_min(&Q);
        turnaroundT = waitingT+sort.time;
        totturnT += turnaroundT;
        printf("\t  %d)\t%s\t\t%d\t\t%.2f\t\t\t%.2f\t\t\t%.2f\n",i,sort.name,sort.priority,sort.time,waitingT,turnaroundT);
        totwaitT +=waitingT;
        waitingT += sort.time;
    }

    printf("\t-----------------------------------------------------------------------------------------------------------\n");
    printf("\t\tTotal\t\t\t\t\t\t\t%.2f\t\t\t%.2f\n",totwaitT,totturnT);
    printf("\t-----------------------------------------------------------------------------------------------------------\n");
    printf("\n\n\t\tAverage waiting time (s) = %.2f \t\tAverage turnaround time (s) = %.2f\n\n",totwaitT/no,totturnT/no);

}
