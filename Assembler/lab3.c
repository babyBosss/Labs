#include<iostream.h>
#include <stdio.h>
#include <dos.h>
#include <conio.h>

// Выводит ASCII-код, только если клавишу нажали два раза

int main(){


union REGS Code;
int pred_code, code; 


for(int i = 1; i <= 10; i++){
	__asm{
    mov ah,00h
    int 16h
    mov Code,al
	mov code,ax
	}
	if (pred_code == code){
	// вывод символа
    printf("Ascii = %02.2X",Code.h.al);
	printf("\n");
	}
	pred_code = code;
	
}
return 0;
}
