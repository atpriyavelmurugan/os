#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int weight;
    int index;
    long long freeTime; 
} Server;


int compareFree(Server a, Server b) {
    if (a.weight != b.weight) return (a.weight > b.weight) - (a.weight < b.weight);
    return (a.index > b.index) - (a.index < b.index);
}


int compareBusy(Server a, Server b) {
    if (a.freeTime != b.freeTime) return (a.freeTime > b.freeTime) - (a.freeTime < b.freeTime);
    if (a.weight != b.weight) return (a.weight > b.weight) - (a.weight < b.weight);
    return (a.index > b.index) - (a.index < b.index);
}


void pushHeap(Server *heap, int *size, Server val, int (*comp)(Server, Server)) {
    heap[*size] = val;
    int curr = (*size)++;
    while (curr > 0) {
        int p = (curr - 1) / 2;
        if (comp(heap[curr], heap[p]) < 0) {
            Server tmp = heap[curr]; heap[curr] = heap[p]; heap[p] = tmp;
            curr = p;
        } else break;
    }
}


Server popHeap(Server *heap, int *size, int (*comp)(Server, Server)) {
    Server top = heap[0];
    heap[0] = heap[--(*size)];
    int curr = 0;
    while (2 * curr + 1 < *size) {
        int left = 2 * curr + 1, right = 2 * curr + 2, small = left;
        if (right < *size && comp(heap[right], heap[left]) < 0) small = right;
        if (comp(heap[small], heap[curr]) < 0) {
            Server tmp = heap[curr]; heap[curr] = heap[small]; heap[small] = tmp;
            curr = small;
        } else break;
    }
    return top;
}

int* assignTasks(int* servers, int serversSize, int* tasks, int tasksSize, int* returnSize) {
    *returnSize = tasksSize;
    int* ans = (int*)malloc(tasksSize * sizeof(int));
    
    Server* freeHeap = (Server*)malloc(serversSize * sizeof(Server));
    Server* busyHeap = (Server*)malloc(serversSize * sizeof(Server));
    int freeSize = 0, busySize = 0;
    
    for (int i = 0; i < serversSize; i++) {
        Server s = {servers[i], i, 0};
        pushHeap(freeHeap, &freeSize, s, compareFree);
    }
    
    long long time = 0;
    for (int i = 0; i < tasksSize; i++) {
        
        if (time < i) time = i;
        
       
        if (freeSize == 0 && busySize > 0) {
            time = busyHeap[0].freeTime;
        }
        
        
        while (busySize > 0 && busyHeap[0].freeTime <= time) {
            Server s = popHeap(busyHeap, &busySize, compareBusy);
            pushHeap(freeHeap, &freeSize, s, compareFree);
        }
        
        
        Server s = popHeap(freeHeap, &freeSize, compareFree);
        ans[i] = s.index;
        s.freeTime = time + tasks[i];
        pushHeap(busyHeap, &busySize, s, compareBusy);
    }
    
    free(freeHeap);
    free(busyHeap);
    return ans;
}
