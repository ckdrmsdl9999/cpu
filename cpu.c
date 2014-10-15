#define MEM_SIZE 1024*1024*1024
#define MAX_SIZE 1024*100000
#define POINTERS 32

#include <stdio.h>
#include <stdlib.h>

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

void move_register(int a, int reg, int* registers){
    registers[reg] = a;
}

int perform_op(char opcode, char* args, int* registers, int* memory){
    switch(opcode){

        case 0:
            if(args[0] == 0){ // register -> register
                add(&registers[args[1]],&registers[args[2]]);
            }
            else{ // memory -> register
                add(&registers[args[1]],&memory[args[2]]);
            }
            return 2; // arg count
        case 4:
            if(args[0] == 0){ // register -> register
                return 0;
            }
    
    }
}

void print_registers(int* registers){
    int i;
    printf("Registers: ");
    for(i=0; i<POINTERS; i++){
        printf("%u,%u ", i, registers[i]);
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
    FILE* fp = fopen("machinecode.bin", "r");
    if(fp==NULL){
        printf("machinecode.bin does not exist. Dying.\n");
        exit(0);
    }
    fread(buffer, sizeof(char), MAX_SIZE, fp);
    printf("%u\n",buffer+4);
    while(i<MAX_SIZE){
        buff2 = buffer + i;
        printf("Got %u\n",*buff2);
        printf("i=%u\n", i);
        i += sizeof(char) * (perform_op(*buff2, buff2+sizeof(char), registers, memory)+1); // Increment instruction pointer
        printf("thing=%u\n", buffer[i]);
        if(buffer[i]=='\xff')
            break;
        // print_registers(registers);
    }
    fclose(fp);
    return 0;
}
