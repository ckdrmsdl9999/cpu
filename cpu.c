#define MEM_SIZE 1024*1024*1024
#define MAX_SIZE 1024*1000
#define POINTERS 32

#include <stdio.h>
#include <stdlib.h>

typedef enum {OUTER, IN_INSTRUCTION} state;

int add(int a,int b){
    return a+b;
}

int sub(int a,int b){
    return a-b;
}

int multiply(int a,int b){
    return a*b;
}

int divide(int a,int b){
    return a/b;
}

int move(int a,int offset){ // Offset from base of memory
    return 0; 
}

int move_register(int a, int reg, int* registers){
    registers[reg] = a;
}

void perform_op(int opcode, int* args, int* registers){
    switch(opcode){
        case 0:
            if(args[0] == 0){
                move_register(add(args[0],args[1]), args[0], registers);
            break;
    }
}


int main(){
    int* memory = malloc(MEM_SIZE*sizeof(int)); // Initialize memory
    int* registers = malloc(POINTERS*sizeof(int)); // eax, ebx, ecx, edx, math, ebp, esp
    int* buffer = malloc(MAX_SIZE*sizeof(int));
    int i;
    int* buff2;
    state cur_state = OUTER;
    FILE* fp = fopen("machinecode.bin", "r");
    if(fp==NULL){
        printf("machinecode.bin does not exist. Dying.\n");
        exit(0);
    }
    fread(&buffer, MAX_SIZE, 1, fp);
    for(i=0; i<MAX_SIZE; i++){
        buff2 = buffer[i];
        if(cur_state == OUTER){
            perform_op(&buff2, buff2+1, registers);
        }
    }
    fclose(fp);
    return 0;
}
