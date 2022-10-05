#include <iostream> // подключение библиотек
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iomanip>
using namespace std; 


// Cозданиe простейшего синтаксического анализатора для заданной грамматики операторного предшествования,
// обработка и представление результатов синтаксического анализа.
// Допустимые лексемы входного языка - Идентификаторы, десятичные числа с плавающей точкой
// Исходная грамматика
//  S -> a:=F
//  F -> F+T | T
//  T -> T*E | T/E | E
//  E -> (F) | -(F) | a

unordered_set<string> divider = {"\t","\n"," "}; // хэш-функция с разделительными знаками
unordered_set<string> operat = {"+","-","*","/"}; // со знаками операциями
int main()
{
	setlocale(LC_ALL, "ru");
	string path = "Code.txt"; //Путь к файлу
	string lexema; // Текущая записываемая лексема
	ifstream file;
	file.open(path); //Открытие файла
	vector<string> type; //Вектор типов лексем
	vector<string> arr; // Вектор лексем

	if (file.is_open()) //если файл получилось открыть
	{
		string state = "F"; //начальное состояние 
		char a; // Переменная для взятия символов из файла
		string lineforsymb; // Строковой тип для проверки через строковые функции
		cout << "Файл открыт, Содержимое файла:" << endl;
		while (file.get(a)) // Вытаскиваются символы из файла
		{
			cout << a; // Вывод содержимого исходного файла
			lineforsymb = a;
			if (state == "F") //Начальное состояние
			{
				if (isalpha(a)) //Если символ является буквой
				{
					state = "E1"; //Переход в состояние E1
					lexema += a; //формирование лексемы
				}
				else if (divider.find(lineforsymb) != divider.end()) // Если символ является разделителем
				{
					state = "F";
				}
				else {
					cout << "Лексема введена неверно"; exit(0); // Окончание программы и вывод ошибки при неверном вводе лексемы
				}
			}
			else if (state == "E1") //состояние E1
			{
				if (isalpha(a) || isdigit(a)) // символ - буква или число
				{
					lexema += a;
					state = "E1";
				}
				else if (divider.find(lineforsymb) != divider.end())
				{
					arr.push_back(lexema); //Заталкивание в конец вектора лексемы
					lexema = ""; //Опустошение значения лексемы для записи следующей
					type.push_back("Идентификатор"); //Заталкивание в конец типа вектора
					state = "E2";
				}
				else if (lineforsymb == ":") //символ - двоеточие
				{
					arr.push_back(lexema);
					lexema = lineforsymb;
					type.push_back("Идентификатор");
					state = "EQ1";
				}
				else {
					cout << "Лексема введена неверно"; exit(0);
				}
			}
			else if (state == "E2") //Состояние E2
			{
				if (divider.find(lineforsymb) != divider.end())
				{
					state = "E2";
				}
				else if (lineforsymb == ":")
				{
					state = "EQ1";
				}
				else {
					cout << "Лексема введена неверно"; exit(0);
				}
			}
			else if (state == "EQ1") //Состояние EQ1
			{
				if (lineforsymb == "=") //Символ - равно
				{
					lexema += a;
					arr.push_back(lexema);
					type.push_back("Оператор присваивания");
					lexema = "";
					state = "EQ2";
				}
				else {
					cout << "Лексема введена неверно"; exit(0);
				}
			}
			else if (state == "EQ2") //Состояние EQ2
			{
				if (isalpha(a))
				{
					lexema += a;
					state = "EXP1";
				}
				else if (isdigit(a))
				{
					lexema += a;
					state = "EXP2";
				}
				else if (divider.find(lineforsymb) != divider.end())
				{
					state = "EQ2";
				}
				else if (lineforsymb == "(" || lineforsymb == ")") //Если символ является скобкой
				{
					arr.push_back(lineforsymb);
					type.push_back("Скобка");
					state = "EQ2";
				}
				else {
					cout << "Лексема введена неверно"; exit(0);
				}
			}
			else if (state == "EXP1") //Состояние EXP1
			{
				if (isalpha(a) || isdigit(a))
				{
					lexema += a;
					state = "EXP1";
				}
				else if (divider.find(lineforsymb) != divider.end())
				{
					arr.push_back(lexema);
					type.push_back("Идентификатор");
					lexema = "";
					state = "EQ";
				}
				else if (lineforsymb == ";") //Если символ является точкой с запятой
				{
					arr.push_back(lexema);
					type.push_back("Идентификатор");
					lexema = "";
					arr.push_back(lineforsymb);
					type.push_back("Конец выражения");
					state = "END";
				}
				else if (lineforsymb == "(" || lineforsymb == ")")
				{

					arr.push_back(lexema);
					type.push_back("Идентификатор");
					lexema = "";
					arr.push_back(lineforsymb);
					type.push_back("Скобка");
					state = "EQ";
				}
				else if (operat.find(lineforsymb) != operat.end()) //если символ является одним из знаков операций
				{
					arr.push_back(lexema);
					type.push_back("Идентификатор");
					lexema = "";
					arr.push_back(lineforsymb);
					type.push_back("Знак операции");
					state = "EQ";
				}
				else {
					cout << "Лексема введена неверно"; exit(0);
				}

			}
			else if (state == "EXP2") //Состояние EXP2
			{
				if (isdigit(a))
				{
					lexema += a;
					state = "EXP2";
				}
				else if (divider.find(lineforsymb) != divider.end())
				{
					arr.push_back(lexema);
					type.push_back("Число");
					lexema = "";
					state = "EQ";
				}
				else if (lineforsymb == "(" || lineforsymb == ")")
				{
					arr.push_back(lexema);
					type.push_back("Число");
					lexema = "";
					arr.push_back(lineforsymb);
					type.push_back("Скобка");
					state = "EQ";
				}
				else if (operat.find(lineforsymb) != operat.end())
				{
					arr.push_back(lexema);
					type.push_back("Число");
					lexema = "";
					arr.push_back(lineforsymb);
					type.push_back("Знак операции");
					state = "EQ";
				}
				else if (lineforsymb == ".") // Если символ является точкой
				{
					lexema += a;
					state = "FP";
				}
				else if (lineforsymb == ";")
				{
					arr.push_back(lexema);
					type.push_back("Число");
					lexema = "";
					arr.push_back(lineforsymb);
					type.push_back("Конец выражения");
					state = "END";
				}
				else {
					cout << "Лексема введена неверно"; exit(0);
				}
			}
			else if (state == "FP") // Состояние FP
			{
				if (isdigit(a))
				{
					lexema += a;
					state = "FP";
				}
				else if (divider.find(lineforsymb) != divider.end())
				{
					arr.push_back(lexema);
					type.push_back("Число");
					lexema = "";
					state = "EQ";
				}
				else if (operat.find(lineforsymb) != operat.end())
				{
					arr.push_back(lexema);
					type.push_back("Число");
					lexema = "";
					arr.push_back(lineforsymb);
					type.push_back("Знак операции");
					state = "EQ";
				}
				else if (lineforsymb == ";")
				{
					arr.push_back(lexema);
					type.push_back("Число");
					lexema = "";
					arr.push_back(lineforsymb);
					type.push_back("Конец выражения");
					state = "END";
				}
				else if (lineforsymb == "(" || lineforsymb == ")")
				{
					arr.push_back(lexema);
					type.push_back("Число");
					lexema = "";
					arr.push_back(lineforsymb);
					type.push_back("Скобка");
					state = "EQ";
				}
				else { cout << "Лексема введена неверно"; exit(0); }
			}
			else if (state == "END") //Состояние END
			{
				if (isalpha(a))
				{
					lexema += a;
					state = "E1";
				}
				else if (divider.find(lineforsymb) != divider.end())
				{
					state = "END";
				}
				else {
					cout << "Лексема введена неверно"; exit(0);
				}
			}
			else if (state == "EQ") // Состояние EQ
			{
				if (isalpha(a))
				{
					lexema += a;
					state = "EXP1";
				}
				else if (isdigit(a))
				{
					lexema += a;
					state = "EXP2";
				}
				else if (divider.find(lineforsymb) != divider.end())
				{
					state = "EQ";
				}
				else if (lineforsymb == ";")
				{
					arr.push_back(lineforsymb);
					type.push_back("Конец выражения");
					state = "END";
				}
				else if (lineforsymb == "(" || lineforsymb == ")")
				{
					arr.push_back(lineforsymb);
					type.push_back("Скобка");
					state = "EQ";
				}
				else if (operat.find(lineforsymb) != operat.end())
				{
					arr.push_back(lineforsymb);
					type.push_back("Знак операции");
					state = "EQ";
				}
				else {
					cout << "Лексема введена неверно"; exit(0);
				}
			}
		}
	}
	else // В случае ошибки открытия файла выдаётся следующее сообщение
	{
		cout << "Ошибка с открытием файла(Неправильное имя или данный файл не существует)" << endl;
		exit(0);
	}
	cout << endl;
	file.close();
	cout << "Таблица с результатом работы лексического анализатора" << endl; //вывод таблицы с результатом работы
	cout << "************************************************" << endl;
	cout << "*";
	cout.width(15);
	cout << "Лексема";
	cout.width(9);
	cout << "*";
	cout.width(19);
	cout << "Тип лексемы";
	cout.width(4);
	cout << "*" << endl;
	cout << "************************************************" << endl; //Границы таблицы
	for (int i = 0; i < arr.size(); i++) //цикл для вывода значений векторов
	{
		cout << "*";
		cout.width(14);
		cout << arr[i];
		cout.width(10);
		cout << "*";
		cout.width(20);
		cout << type[i];
		cout.width(3);
		cout << "*" << endl;
	}
	cout << "************************************************" << endl;
	vector <string> temp; // Вектор для построения дерева вывода
	vector <string> temp2; // Вектор, хранящий последний задействованный элемент и все элементы до него
	int flag = 0; // флаг для проверки грамматики и перехода между элементами грамматики
	bool minus = false; //флаг при наличии минуса (для правила грамматики -(F))
	bool skobka = false; // Для обозначения наличие выражения в скобках
	cout << "Дерево вывода:" << endl; // Вывод дерева вывода
	cout << "E" << endl;
	for (int i = 0; i < arr.size(); i++) // Проверка на грамматику в цикле
	{
		if (type[i] == "Идентификатор" && flag == 0) // Условия для добавления в вектор первого элемента
		{
			temp.push_back(arr[i]);
			temp2.push_back(arr[i]);
			flag = 1;
		}
		else if (type[i] == "Оператор присваивания" && flag == 1) // Добавления оператора присваивания
		{
			temp.push_back(arr[i]);
			temp2.push_back(arr[i]);
			flag = 2;
		}
		else if (flag == 2 && arr[i] != ")" && arr[i] != ":=" && (type[i] == "Число" || type[i] == "Скобка" || type[i] == "Идентификатор"))
		{
			if (arr[i] == "(") //проверка на начало скобок
			{
				skobka = true;
				temp.push_back("(E)");
				flag = 5; //переход в состояние начала скобок
			}
			else { temp.push_back("E"); flag = 3; } // переход
			temp2.push_back(arr[i]);
			for (int b=0; b < temp.size(); b++) //вывод после свёртки
			{
				cout << temp[b] ;
			}
			cout << ";"<< endl;
			
		}
		else if (flag == 3) // после идентификатора или числа
		{
			if (type[i] == "Знак операции")
			{
				temp.push_back(arr[i]);
				temp2.push_back(arr[i]);
				flag = 4;
				if (arr[i] == "-") minus = true; //наличие минуса
			}
			else { cout << "Ошибка синтаксического анализатора, не существует правила"; exit(0); } //вывод ошибки
		}
		else if (flag == 4 && arr[i]!=")" && arr[i]!=":=" && arr[i]!=";") // ввод второго элемента после знака операции
		{
			if (minus == true && arr[i] != "(") { cout << "Ошибка синтаксического анализатора, не существует правила"; exit(0); } // проверка на правило грамматики
			if (type[i] == "Скобка") // Построение дерева вывода
			{
				temp.push_back("(E)");
				skobka = true;
			}
			else
				if (skobka == true && arr[i + 1] == ")") 
				{
					temp.push_back("E)");
					for (int b = 0; b < temp.size(); b++)
					{
						cout << temp[b];
					}
					cout << ";" << endl;
				}
				else 
				{ 
					
					temp.push_back("E"); 
					if (skobka == false) {
						for (int b = 0; b < temp.size(); b++)
						{
							cout << temp[b];
						}
						cout << ";" << endl;
					}
				}
			temp2.push_back(arr[i]);
			flag = 5;
			minus = false;
		}
		else if (flag == 5)
		{
			if (type[i] == "Знак операции" && skobka!= true) //Продолжение работы с выражением
			{
				flag = 3;
				i--;
			}
			else if (type[i] == "Идентификатор" || type[i]=="Число") // замена элементов для дерева вывода
			{
				if (skobka == true) { temp.pop_back(); temp.push_back(temp2[i - 1]); temp.push_back("E"); }
				else
				temp.push_back(arr[i]);
				temp2.push_back(arr[i]);
				flag = 6;
			}
		}
		else if (flag == 6)
		{ 
			if (type[i] == "Скобка" || type[i] == "Знак операции")
			{
				if (arr[i] == ")")
				{
					temp.push_back(arr[i]);
					temp2.push_back(arr[i]);
					skobka = false;
					flag = 5;
				}
				else { flag = 3; i--; }
			}
		}
		if (arr[i] == ";") //Если элемент является последним(;)
		{
			for (int c = temp.size()-1; c > -1; c--) // Конечный вывод дерева в зависимости от выражения
			{
				if (temp[c] == "E")
				{
					temp[c] = temp2[c];
					for (int k = 0; k < temp.size();k++) 
					{
						cout << temp[k];
					}
					cout << ";"<<endl;
				}
				else if (temp[c] == "E)")
				{
					temp[c] = temp2[c] + ")";
					for (int k = 0; k < temp.size(); k++)
					{
						cout << temp[k];
					}
					cout << ";" << endl;
				}
			}
		}
	}
}
