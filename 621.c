#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int leastInterval(char* tasks, int tasksSize, int n) {
    int freq[26] = {0};
    
    for (int i = 0; i < tasksSize; i++) {
        freq[tasks[i] - 'A']++;
    }
    
    int maxFreq = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
        }
    }
    
    int countMaxFreq = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] == maxFreq) {
            countMaxFreq++;
        }
    }
    
    
    int minLen = (maxFreq - 1) * (n + 1) + countMaxFreq;
    
   
    return (tasksSize > minLen) ? tasksSize : minLen;
}
