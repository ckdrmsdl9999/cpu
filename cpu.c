#define MEM_SIZE 1024*1024*1024
#define MAX_SIZE 1024*100000
#define POINTERS 32

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add(int* a,int* b){
    *a = *a+*b;
}

void sub(int* a,int* b){
    *a = *a-*b;
}

void multiply(int* a,int* b){
    *a = *a * *b;
}

void divide(int* a,int* b){
    *a = *a / *b;
}

void move(int* a, int* address){
    *address = *a;
}

int perform_op(char opcode, int* args, int* registers, int* memory){
    printf("arg1: %u, arg2: %u, arg3: %u\n", args[0], args[1], args[2]);
    printf("opcode=%u\n",opcode);
    switch(opcode){

        case 0: // add
            if(args[0] == 0){ // register -> register
                add(&registers[args[1]],&registers[args[2]]);
            }
            else{ // memory -> register
                add(&registers[args[1]],&memory[args[2]]);
            }
            return 3; // arg count
        case 4: // move
            if(args[0] == 0){ // register -> register
                move(&registers[args[1]],&registers[args[2]]);
            }
            else if(args[0] == 1){ // memory -> register
                move(&memory[args[1]],&registers[args[2]]);
            }
            else if(args[0] == 2){ // register -> memory
                move(&registers[args[1]],&memory[args[2]]);
            }
            else if(args[0] == 3){ // value -> register
                move(&args[1],&registers[args[2]]);
            }
            return 3;
    }
    return 0;
}

void print_registers(int* registers){
    int i;
    printf("Registers: ");
    for(i=0; i<POINTERS; i++){
        printf("%u,%u ", i, registers[i]);
    }
    printf("\n");
}

void print_buffer(char* buffer){
    char c = 'X';
    int i = 0;
    while(c != '\xff'){
        c = buffer[i];
        printf("Char %u: %c, ", i, c);
        i++;
    }
    printf("\n");
}

int main(){
    int* memory = malloc(MEM_SIZE*sizeof(int)); // Initialize memory
    int* registers = malloc(POINTERS*sizeof(int)); // eax, ebx, ecx, edx, math, ebp, esp
    char* buffer = malloc(MAX_SIZE*sizeof(char));
    printf("%p\n", buffer);
    int i = 0;
    char* buff2;
    FILE* fp = fopen("machinecode.bin", "rb");
    if(fp==NULL){
        printf("machinecode.bin does not exist. Dying.\n");
        exit(0);
    }
    fread(buffer, sizeof(char), MAX_SIZE, fp);
    while(i<MAX_SIZE){
        buff2 = buffer + i;
        print_buffer(buff2);
        printf("Got %u\n",*buff2);
        printf("i=%u\n", i);
       
        int* args = (int *)(buff2+sizeof(char));
        int res = (perform_op(*buff2, args, registers, memory)); // Increment instruction pointer
        printf("Res=%u\n", res);
        i += 1 + sizeof(int)*res;
        print_registers(registers);
        if(buffer[i]=='\xff')
            break;
    }
    fclose(fp);
    return 0;
}
