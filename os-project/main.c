//
//  main.c
//  os-project
//
//  Created by 김혜영 on 2020/07/12.
//  Copyright © 2020 김혜영. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void MIN(int* arr1, int* arr2)
{
    int pf = arr1[1];
    int slength = arr1[3];
    int pageframe[15];
    memset(pageframe, -1, sizeof(pageframe));
    int pagefault = 1;
    int pftime[100] = { 0 };
    int gothrough = 1;
    int rset[16][100];
    int pfcount = 0;

    for (int i = 0; i < slength; i++) {
        for (int j = 0; j < pf; j++) {
            if (pageframe[j] == -1) {
                pageframe[j] = arr2[i];
                gothrough = 0;
                pftime[i] = i+1;
                pagefault = 1;
                break;
            }
            else if (pageframe[j] != -1 && arr2[i] == pageframe[j]) {
                pagefault = 0;
                break;
            }
        }
        
        if (pagefault == 1&& gothrough==1) {
            
            pftime[i] = i+1;
            int current = i;
            int min[15][2] = { 0 };
            for (int k = 0; k < pf; k++) {
                while (pageframe[k] != arr2[current]) {
                    current++;
                    if (current > slength) break;
                }
                min[k][0] = pageframe[k];
                min[k][1] = current; // πÃ∑° ¿Œµ¶Ω∫∞™
                current = i;
            }
            int temp[1][2];
            for (int m = pf - 1; m > 0; m--) {
                for (int n = 0; n < m; n++) {
                    if (min[n][1] < min[n + 1][1]) {
                        temp[0][1] = min[n + 1][1];
                        min[n + 1][1] = min[n][1];
                        min[n][1] = temp[0][1];
                        temp[0][0] = min[n + 1][0];
                        min[n + 1][0] = min[n][0];
                        min[n][0] = temp[0][0];
                    }
                    else if (min[n][1] == min[n + 1][1]) {
                        if (min[n][0] > min[n + 1][0]) {
                            temp[0][1] = min[n + 1][1];
                            min[n + 1][1] = min[n][1];
                            min[n][1] = temp[0][1];
                            temp[0][0] = min[n + 1][0];
                            min[n + 1][0] = min[n][0];
                            min[n][0] = temp[0][0];
                        }
                    }
                }
            }
            int s = 0;
            while (pageframe[s]!=min[0][0]){
                s++;
            }
            pageframe[s] = arr2[i];
            
        }
        gothrough = 1;
        pagefault = 1;
        for (int p = 0; p < pf; p++) {
            rset[p + 1][i] = pageframe[p];
        }
        
    }
    printf("\nMIN: \n\n");
    for (int i = 0; i < slength; i++) {
        rset[0][i] = i + 1;
        printf("%3d ", rset[0][i]);
    }
    printf("\n--------------------------------------------------------------------\n");
    for (int i = 0; i < slength; i++) {
        printf("%3d ", arr2[i]);
    }
    printf("\n--------------------------------------------------------------------\n");
    for (int i = 1; i < pf+1; i++) {
        for (int j = 0; j < slength; j++) {
            if(rset[i][j]!=-1) printf("%3d ", rset[i][j]);
            else printf("%3c ", 'X');
        }
        printf("\n");
    }
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < slength; i++) {
        if (pftime[i] != 0) {
            printf("%3c ", 'F');
            pfcount++;
        }
        else {
            printf("%3d ", pftime[i]);
        }
    }
    printf("\n--------------------------------------------------------------------\n");
    printf("Total Page fault : %d \n", pfcount);
}

void FIFO(int* arr1, int* arr2) {
    int pf = arr1[1];
    int slength = arr1[3];
    int pageframe[15];
    memset(pageframe, -1, sizeof(pageframe));
    int pagefault = 1;
    int pftime[100] = { 0 };
    int gothrough = 1;
    int timestamp[100];
    memset(timestamp, -1, sizeof(timestamp));
    int pfcount = 0;
    int rset[16][100];

    for (int i = 0; i < slength; i++) {
        for (int j = 0; j < pf; j++) {
            if (pageframe[j] == -1) {
                pageframe[j] = arr2[i];
                timestamp[i] = arr2[i];
                gothrough = 0;
                pftime[i] = i + 1;
                pagefault = 1;
                break;
            }
            else if (pageframe[j] != -1 && arr2[i] == pageframe[j]) {
                pagefault = 0;
                break;
            }
        }
        if (pagefault == 1 && gothrough == 1) {
            pftime[i] = i + 1;
            
                int t = 0;
                while(timestamp[t]==-1){
                    t++;
                }
            
            for (int a = 0; a < pf; a++) {
                if (pageframe[a] == timestamp[t]) {
                    pageframe[a] = arr2[i];
                    timestamp[i] = arr2[i];
                    timestamp[t] = -1;
                }
            }
        }
        gothrough = 1;
        pagefault = 1;
        for (int p = 0; p < pf; p++) {
            rset[p + 1][i] = pageframe[p];
        }
    }
    printf("\nFIFO: \n\n");
    for (int i = 0; i < slength; i++) {
        rset[0][i] = i + 1;
        printf("%3d ", rset[0][i]);
    }
    printf("\n--------------------------------------------------------------------\n");
    for (int i = 0; i < slength; i++) {
        printf("%3d ", arr2[i]);
    }
    printf("\n--------------------------------------------------------------------\n");
    for (int i = 1; i < pf + 1; i++) {
        for (int j = 0; j < slength; j++) {
            if (rset[i][j] != -1) printf("%3d ", rset[i][j]);
            else printf("%3c ", 'X');
        }
        printf("\n");
    }
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < slength; i++) {
        if (pftime[i] != 0) {
            printf("%3c ", 'F');
            pfcount++;
        }
        else {
            printf("%3d ", pftime[i]);
        }
    }
    printf("\n--------------------------------------------------------------------\n");
    printf("Total Page fault : %d \n", pfcount);
}
            
void LRU(int* arr1, int* arr2) {
    int pf = arr1[1];
    int slength = arr1[3];
    int pageframe[15];
    memset(pageframe, -1, sizeof(pageframe));
    int pagefault = 1;
    int pftime[100] = { 0 };
    int gothrough = 1;
    int timestamp[15] = { 0 };
    int rset[16][100];
    int pfcount = 0;

    for (int i = 0; i < slength; i++) {
        timestamp[arr2[i]] = i + 1;
        for (int j = 0; j < pf; j++) {
            if (pageframe[j] == -1) {
                pageframe[j] = arr2[i];
                gothrough = 0;
                pftime[i] = i + 1;
                pagefault = 1;
                break;
            }
            else if (pageframe[j] != -1 && arr2[i] == pageframe[j]) {
                pagefault = 0;
                break;
            }
        }
        if (pagefault == 1 && gothrough == 1) {
            pftime[i] = i + 1;
            int checkarr[15] = { 0 };
            for (int k = 0; k < pf; k++) {
                checkarr[k] = timestamp[pageframe[k]];
            }
            int temp;
            for (int m = pf - 1; m > 0; m--) {
                for (int n = 0; n < m; n++) {
                    if (checkarr[n] > checkarr[n + 1]) {
                        temp = checkarr[n + 1];
                        checkarr[n + 1] = checkarr[n];
                        checkarr[n] = temp;
                    }
                }
            }
            int t = 0;
            while (checkarr[t] == 0) t++;
            for (int s = 0; s < pf; s++) {
                if (timestamp[pageframe[s]] == checkarr[t]) {
                    pageframe[s] = arr2[i];
                    break;
                }
            }
        }
        gothrough = 1;
        pagefault = 1;
        for (int p = 0; p < pf; p++) {
            rset[p + 1][i] = pageframe[p];
        }
    }
    printf("\nLRU: \n\n");
    for (int i = 0; i < slength; i++) {
        rset[0][i] = i + 1;
        printf("%3d ", rset[0][i]);
    }
    printf("\n--------------------------------------------------------------------\n");
    for (int i = 0; i < slength; i++) {
        printf("%3d ", arr2[i]);
    }
    
    printf("\n--------------------------------------------------------------------\n");
    for (int i = 1; i < pf + 1; i++) {
        for (int j = 0; j < slength; j++) {
            if (rset[i][j] != -1) printf("%3d ", rset[i][j]);
            else printf("%3c ", 'X');
        }
        printf("\n");
    }
    printf("--------------------------------------------------------------------\n");
    
    for (int i = 0; i < slength; i++) {
        if (pftime[i] != 0) {
            printf("%3c ", 'F');
            pfcount++;
        }
        else {
            printf("%3d ", pftime[i]);
        }
    }
    printf("\n--------------------------------------------------------------------\n");
    printf("Total Page fault : %d \n", pfcount);

}

void LFU(int* arr1, int* arr2) {
    int pf = arr1[1];
    int slength = arr1[3];
    int pageframe[15];
    memset(pageframe, -1, sizeof(pageframe));
    int pagefault = 1;
    int pftime[100] = { 0 };
    int gothrough = 1;
    int count[15] = { 0 };
    int rset[16][100];
    int pfcount = 0;

    for (int i = 0; i < slength; i++) {
        count[arr2[i]]++;
        for (int j = 0; j < pf; j++) {
            if (pageframe[j] == -1) {
                pageframe[j] = arr2[i];
                gothrough = 0;
                pftime[i] = i + 1;
                pagefault = 1;
                break;
            }
            else if (pageframe[j] != -1 && arr2[i] == pageframe[j]) {
                pagefault = 0;
                break;
            }
        }
        if (pagefault == 1 && gothrough == 1) {
            pftime[i] = i + 1;
            int checkarr[15][2] = { 0 };
            for (int k = 0; k < pf; k++) {
                checkarr[k][0] = pageframe[k];
                checkarr[k][1] = count[pageframe[k]];
            }
            int temp[1][2];
            for (int m = pf-1; m > 0; m--) {
                for (int n = 0; n < m; n++) {
                    if (checkarr[n][1] > checkarr[n + 1][1]) {
                        temp[0][1] = checkarr[n + 1][1];
                        temp[0][0] = checkarr[n + 1][0];
                        checkarr[n + 1][1] = checkarr[n][1];
                        checkarr[n + 1][0] = checkarr[n][0];
                        checkarr[n][1] = temp[0][1];
                        checkarr[n][0] = temp[0][0];
                    }
                    else if (checkarr[n][1] == checkarr[n + 1][1]) {
                        int startpoint = i-1;
                        while (arr2[startpoint] != checkarr[n][0] && arr2[startpoint] != checkarr[n + 1][0]) {
                            startpoint--;
                        }
                        if (arr2[startpoint] == checkarr[n][0]) {
                            temp[0][1] = checkarr[n + 1][1];
                            temp[0][0] = checkarr[n + 1][0];
                            checkarr[n + 1][1] = checkarr[n][1];
                            checkarr[n + 1][0] = checkarr[n][0];
                            checkarr[n][1] = temp[0][1];
                            checkarr[n][0] = temp[0][0];
                        }
                    }
                }
            }
            
            int s = 0;
            while (pageframe[s] != checkarr[0][0]) {
                s++;
            }
            pageframe[s] = arr2[i];
        }
        gothrough = 1;
        pagefault = 1;
        for (int p = 0; p < pf; p++) {
            rset[p + 1][i] = pageframe[p];
        }
    }
    printf("\nLFU: \n\n");
    for (int i = 0; i < slength; i++) {
        rset[0][i] = i + 1;
        printf("%3d ", rset[0][i]);
    }
    printf("\n--------------------------------------------------------------------\n");
    for (int i = 0; i < slength; i++) {
        printf("%3d ", arr2[i]);
    }
    printf("\n--------------------------------------------------------------------\n");
    for (int i = 1; i < pf + 1; i++) {
        for (int j = 0; j < slength; j++) {
            if (rset[i][j] != -1) printf("%3d ", rset[i][j]);
            else printf("%3c ", 'X');
        }
        printf("\n");
    }
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < slength; i++) {
        if (pftime[i] != 0) {
            printf("%3c ", 'F');
            pfcount++;
        }
        else {
            printf("%3d ", pftime[i]);
        }
    }
    printf("\n--------------------------------------------------------------------\n");
    printf("Total Page fault : %d \n", pfcount);
}

void WS(int* arr1, int* arr2) {
    int pnum = arr1[0];
    int wsize = arr1[2];
    int slength = arr1[3];
    int pageframe[15];
    memset(pageframe, -1, sizeof(pageframe));
    int pftime[100] = { 0 };
    int memorystate[15] = { 0 };
    int rset[16][100] = { 0 };
    int pfcount = 0;

    for (int i = 0; i < slength; i++) {
        
        if (i >= wsize) {
            for (int m = 0; m < 15; m++) {
                memorystate[m] = 0;
                pageframe[m] = -1;
            }
            for (int j = 0; j < wsize; j++) {
                memorystate[arr2[i - 1 - j]] = 1;
            }
        }
        for (int k = 0; k < 15; k++) {
            if (memorystate[k] != 0) {
                pageframe[k] = k;
            }
        }
        if (memorystate[arr2[i]] == 0) {
            pageframe[arr2[i]] = arr2[i];
            pftime[i] = i + 1;
            memorystate[arr2[i]] = 1;
        }
        for (int p = 0; p < pnum; p++) {
            rset[p + 1][i] = pageframe[p];
        }
    }
    printf("\nWS: \n\n");
    for (int i = 0; i < slength; i++) {
        rset[0][i] = i + 1;
        printf("%3d ", rset[0][i]);
    }
    printf("\n--------------------------------------------------------------------\n");
    for (int i = 0; i < slength; i++) {
        printf("%3d ", arr2[i]);
    }
    printf("\n--------------------------------------------------------------------\n");
    for (int i = 1; i < pnum + 1; i++) {
        for (int j = 0; j < slength; j++) {
            if (rset[i][j] != -1) printf("%3d ", rset[i][j]);
            else printf("%3c ", 'X');
        }
        printf("\n");
    }
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < slength; i++) {
        if (pftime[i] != 0) {
            printf("%3c ", 'F');
            pfcount++;
        }
        else {
            printf("%3d ", pftime[i]);
        }
    }
    printf("\n--------------------------------------------------------------------\n");
    printf("Total Page fault : %d \n", pfcount);
}

int main()
{
    int arr1[4];
    int arr2[100];
    scanf("%d %d %d %d", &arr1[0], &arr1[1], &arr1[2], &arr1[3]);
    for (int i = 0; i < arr1[3]; i++) {
        scanf("%d", &arr2[i]);
    }
    MIN(arr1, arr2);
    printf("\n");
    FIFO(arr1, arr2);
    printf("\n");
    LRU(arr1, arr2);
    printf("\n");
    LFU(arr1, arr2);
    printf("\n");
    WS(arr1, arr2);
    printf("\n");
    return 0;
}

