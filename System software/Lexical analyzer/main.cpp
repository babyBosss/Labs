#include <iostream> // подключение библиотек
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iomanip>
using namespace std; 

// построение сканера на примере заданного простейшего входного языка.
// Входной язык содержит арифметические выражения, разделенные символом ; (точка с запятой).
// Арифметические выражения состоят из идентификаторов, десятичных чисел с плавающей точкой,
// знака присваивания (:=), знаков операций +, -, *, / и круглых скобок.

unordered_set<string> divider = {"\t","\n"," "}; // хэш-функция с разделительными знаками
unordered_set<string> operat = {"+","-","*","/"}; // со знаками опе-рациями
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
		cout << "Файл открыт, Содержимое файла:"<< endl;
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
				else { cout << "Лексема введена неверно"; exit(0); // Окончание программы и вывод ошибки при неверном вводе лексемы
				}
			}
			else if (state == "E1") //состояние E1
			{
				if (isalpha(a) || isdigit(a)) // символ - буква или число
				{
					lexema += a;
					state = "E1";
				}
				else if (divid-er.find(lineforsymb)!=divider.end()) 
				{
					arr.push_back(lexema); //Заталкивание в ко-нец вектора лексемы
					lexema = ""; //Опустошение значения лексемы для записи следующей
					type.push_back("Идентификатор"); //Заталкивание в конец типа вектора
					state = "E2";
				}
				else if (lineforsymb == ":") //символ - двоето-чие
				{
					arr.push_back(lexema);
					lexema = lineforsymb;
					type.push_back("Идентификатор");
					state = "EQ1";
				}
				else { cout << "Лексема введена неверно"; exit(0);
				}
			}
			else if (state == "E2") //Состояние E2
			{
				if (divider.find(lineforsymb) != divider.end())
				{
					state = "E2";
				}
				else if (lineforsymb==":") 
				{
					state = "EQ1";
				}
				else { cout << "Лексема введена неверно"; ex-it(0);
				}
			}
			else if (state == "EQ1") //Состояние EQ1
			{
				if (lineforsymb == "=") //Символ - равно
				{
					lexema += a;
					arr.push_back(lexema);
					type.push_back("Знак присваивания");
					lexema = "";
					state = "EQ2";
				}
				else { cout << "Лексема введена неверно"; ex-it(0);
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
				else if (divider.find(lineforsymb) != divid-er.end())
				{
					state = "EQ2";
				}
				else if (lineforsymb == "(" || lineforsymb == ")") //Если символ является скобкой
				{
					arr.push_back(lineforsymb);
					type.push_back("Скобка");
					state = "EQ2";
				}
				else { cout << "Лексема введена неверно"; ex-it(0);
				}
			}
			else if (state=="EXP1") //Состояние EXP1
			{
				if (isalpha(a) || isdigit(a))
				{
					lexema += a;
					state = "EXP1";
				}
				else if (divid-er.find(lineforsymb)!=divider.end()) 
				{
					arr.push_back(lexema);
					type.push_back("Идентификатор");
					lexema = "";
					state = "EQ";
				}
				else if (lineforsymb==";") //Если символ являет-ся точкой с запятой
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
				else { cout << "Лексема введена неверно"; exit(0);
				}

			}
			else if (state == "EXP2") //Состояние EXP2
			{
				if (isdigit(a))
				{
					lexema += a;
					state = "EXP2";
				}
				else if (divider.find(lineforsymb) != divid-er.end())
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
				else if (operat.find(lineforsymb) != op-erat.end())
				{
					arr.push_back(lexema);
					type.push_back("Число");
					lexema = "";
					arr.push_back(lineforsymb);
					type.push_back("Знак операции");
					state = "EQ";
				}
				else if (lineforsymb == ".") // Если символ яв-ляется точкой
				{
					lexema += a;
					state = "FP";
				}
				else if (lineforsymb==";")
				{
					arr.push_back(lexema);
					type.push_back("Число");
					lexema = "";
					arr.push_back(lineforsymb);
					type.push_back("Конец выражения");
					state = "END";
				}
				else { cout << "Лексема введена неверно"; exit(0);
				}
			}
			else if (state=="FP") // Состояние FP
			{
				if (isdigit(a))
				{
					lexema += a;
					state = "FP";
				}
				else if (divider.find(lineforsymb) != divid-er.end())
				{
					arr.push_back(lexema);
					type.push_back("Число");
					lexema = "";
					state = "EQ";
				}
				else if (operat.find(lineforsymb) != op-erat.end())
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
				else if (divider.find(lineforsymb) != divid-er.end())
				{
					state = "END";
				}
				else { cout << "Лексема введена неверно"; ex-it(0);
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
				else if (divid-er.find(lineforsymb)!=divider.end()) 
				{
					state = "EQ";
				}
				else if (lineforsymb == ";")
				{
					arr.push_back(lineforsymb);
					type.push_back("Конец выражения");
					state = "END";
				}
				else if(lineforsymb=="(" || lineforsymb==")")
				{
					arr.push_back(lineforsymb);
					type.push_back("Скобка");
					state = "EQ";
				}
				else if(operat.find(lineforsymb)!=operat.end())
				{
					arr.push_back(lineforsymb);
					type.push_back("Знак операции");
					state = "EQ";
				}
				else { cout << "Лексема введена неверно"; ex-it(0);
				}
			}
		}	
	}
	else // В случае ошибки открытия файла выдаётся следующее сооб-щение
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
		cout << "*" <<endl;
	}
	cout << "************************************************" << endl;
}
