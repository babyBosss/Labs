#include<stdio.h>
#include<dos.h>
#include<conio.h>

// Вывести координаты курсора мышки на дисплей в текстовом режиме работы видеоадаптера.

int main(){
unsigned int x,y;

asm mov ah,0
asm int 0x10

for(int i =0; i<100;++i){
//получаем координаты указателя мыши
asm mov ax, 0x03
asm int 0x33
asm mov x, cx
asm mov y, dx
// отображаем указатель мыши
asm mov ax,1
asm int 0x33

// выводим строку "Х="
asm mov al, 'X'
asm mov ah, 0Eh
asm int 10h
asm mov al, '='
asm mov ah, 0Eh
asm int 10h
//посимвольно выводим значение координаты х
//1 число
asm mov ax,cx
asm mov bl,100
asm div bl
asm mov ah,0Eh
asm int 10h
//2число
asm mov bl,10
asm div bl
asm mov bh, ah
asm mov ah,0Eh
asm int 10h
//3число
asm mov al,bh
asm mov ah,0Eh
asm int 10h

//выводим строку ",Y="
asm mov al, ','
asm mov ah, 0Eh
asm int 10h
asm mov al, 'Y'
asm mov ah, 0Eh
asm int 10h
asm mov al, '='
asm mov ah, 0Eh
asm int 10h
//посимвольно выводим координату y
//1 число
asm mov ax,dx
asm mov bl,100
asm div bl
asm mov ah,0Eh
asm int 10h
//2 число
asm mov bl,10
asm div bl
asm mov bh, ah
asm mov ah,0Eh
asm int 10h
//3 число
asm mov al,bh
asm mov ah,0Eh
asm int 10h

delay(500);
clrscr();
}
return 0;
}
