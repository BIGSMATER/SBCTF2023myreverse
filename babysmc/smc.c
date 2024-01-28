#include<stdio.h>
#include<windows.h>
#include<string.h>
// char flag[41]="SBCTF{The_code_can_be_edit_when_running}";
unsigned int encflag[10]={3776109546,4260205215,116586236,4076271869,4093020152,4059887356,251038144,4140300481,130517195,150898624};


void check(char *input) {
    for(int i=0;i<10;i++)
    {
        *(unsigned int*)&input[i*4]+=0x12345678;
        *(unsigned int*)&input[i*4]^=0x87654321;
    }
    for(int i=0;i<10;i++)
    {
        if(*(unsigned int*)&input[i*4]!=encflag[i])
        {
            printf("Wrong!");
            exit(0);
        }
    }
            printf("Right!");
        return 0;
}

void smc() {
    unsigned long old = (unsigned long) malloc(8);
    char *pcheck = (char*)check;
    int len = 184;
    char *addr = pcheck - (unsigned long) pcheck % 4096;
    VirtualProtect(addr, 4096, PAGE_EXECUTE_WRITECOPY, &old);
    for (int i = 0; i < len; i++) {
        *(pcheck + i) = (*(pcheck + i) ^ 0x2e);
    }
}

int main() {
    char input[41];
    printf("input your flag:\n");
    scanf("%s", input);
    smc();
    check(input);
    return 0;
}
