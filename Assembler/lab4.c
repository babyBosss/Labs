#include <iostream.h>
#include <stdio.h>
#include <dos.h>
#include <conio.h>
 
 // Получать координаты манипулятора мышь в реальном режиме времени

int main(){
int X; //координаты х
int Y; //координаты y

//цикл повторений  
for(int i = 1; i <= 100; i++){

//ассемблерная вставка  
start:
__asm{
	mov AX, 011b //инструкции
	int 33h //прерывание для мышки
	mov ax, cx //помещаем координату Х в АХ
	mov X, ax //помещаем координату из АХ в переменную
	mov ax, dx //помещаем координату У в АХ
	mov Y, ax //помещаем координату из АХ в переменную
	 
	LOOP start
}     cout << "\n";    
	cout <<"X = "; //вывод координаты курсора по х
	cout << X; 
	cout <<"  Y = "; //вывод координаты курсора по y
	cout << Y;                     
}
return 0;
}
