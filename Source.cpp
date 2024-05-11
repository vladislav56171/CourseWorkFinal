#include <iostream>
#include <string>
#include <locale.h>
#include <muParser.h> 
using namespace std;

bool isconvertibleToDouble(const std::string& s) { // Функция для проверки числовых аргументов
	try {
		size_t pos;
		double value = std::stod(s, &pos);

		// Проверяем, что вся строка была использована для преобразования
		return pos == s.length();
	}
	catch (const std::invalid_argument&) {
		return false; // Некорректный аргумент (строка не число)
	}
	catch (const std::out_of_range&) {
		return false; // Вне диапазона чисел типа double
	}
}

void manual() { // Вывод инструкции
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Инструкция: " << endl;
	cout << "При вводе функции f(x) используйте в качестве переменной только x" << endl;
	cout << "При вычислении производной x может быть только числом, иначе программа завершится" << endl;
	cout << "Для получения корректных результатов следуйте ограничениям на переменные, указанные в описаниях функций" << endl;
	cout << "Вы можете использовать следующие константы в своей функции: " << endl;
	cout << "_pi = 3,14159 " << endl;
	cout << "_e = 2,71828 " << endl;
	cout << "Математические функции использовать только в следующем виде: " << endl;
	cout << "sin(x)     cos(x)     tan(x)" << endl;
	cout << "asin(x)    acos(x)    atan(x)" << endl;
	cout << "Внимание: функции cot и acot при подсчете производной произвольной функции напрямую не работают, вместо них используйте:" << endl;
	cout << "cot(x) ~ 1/tan(x)" << endl;
	cout << "acot(x) ~ atan(1/x)" << endl;
	cout << "Натуральный логарифм: ln(x), ОГРАНИЧЕНИЕ: x > 0" << endl;
	cout << "Логарифм с основанием A: logA(x), ОГРАНИЧЕНИЕ: x > 0; A > 0; A != 1" << endl;
	cout << "Для корректной обработки производных используйте: '+', '-', '*', '/', '^', '(', ')'" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
}

int derivative() { // Функция для подсчета производной функции одной переменной
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	string function;
	string x_tmp;
	cout << "Введите функцию f(x): ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Для правильной работы getline()
	getline(cin, function); // Ввод функции f(x)
	cout << "Ваша функция f(x) = " << function << endl;
	cout << "Введите значение x: ";
	cin >> x_tmp; // Ввод значения x
	if (!isconvertibleToDouble(x_tmp)) { // Проверка, что введенный x является числом
		cout << "Ошибка ввода аргумента x" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		return 1;
	}
	double x, h = 0.001;
	x = stod(x_tmp);
	double tmp_1 = x + h; // tmp_1(2) необходимы для дальнейшего вычисления производной
	double tmp_2 = x - h;

	mu::Parser parser_fx_minus_h;
	mu::Parser parser_fx_plus_h;

	try { // Попытка вычисления производной (выполняется, если проверка на корректный ввод x была успешной
		parser_fx_plus_h.SetExpr(function);
		parser_fx_plus_h.DefineVar("x", &tmp_1);
		double fx_plus = parser_fx_plus_h.Eval();
		parser_fx_minus_h.SetExpr(function);
		parser_fx_minus_h.DefineVar("x", &tmp_2);
		double fx_minus = parser_fx_minus_h.Eval();
		double derivative = (fx_plus - fx_minus) / (2 * h);
		cout << "Провизводная функции f(x) = " << function << " в точке x = " << x << " равна: " << derivative << endl;
	}
	catch (mu::Parser::exception_type& e) { // Вывод ошибки, при вычислении производной с ошибкой
		cout << "Ошибка при вычислении функции: " << e.GetMsg() << endl;
	}
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	return 0;
}

int calculate_table_derivative(string fx, string dfx, bool fl_a = false, bool fl_n = false) { // Функция для подсчета табличной производной
	cout << "Если f(x) = " << fx << ", то f'(x) = " << dfx << endl;
	string x_tmp, n_tmp, a_tmp;
	mu::Parser df;
	try { // Попытка вычисления табличной производной
		if (fl_a) {
			cout << "Введите a: ";
			cin >> a_tmp;
			if (!isconvertibleToDouble(a_tmp)) { // Проверка, что введенная a является числом
				cout << "Ошибка ввода аргумента a" << endl;
				return 1;
			}
			else {
				double a = stod(a_tmp);
				df.DefineVar("a", &a);
			}
		}
		if (fl_n) {
			cout << "Введите n: ";
			cin >> n_tmp;
			if (!isconvertibleToDouble(n_tmp)) { // Проверка, что введенная n является числом
				cout << "Ошибка ввода аргумента n" << endl;
				return 1;
			}
			else {
				double n = stod(n_tmp);
				df.DefineVar("n", &n);
			}
		}
		cout << "Введите x: ";
		cin >> x_tmp;
		if (!isconvertibleToDouble(x_tmp)) {  // Проверка, что введенный x является числом
			cout << "Ошибка ввода аргумента x" << endl;
			return 1;
		}
		else {
			double x = stod(x_tmp);
			df.DefineVar("x", &x);
			df.SetExpr(dfx);
			double eval = df.Eval();
			cout << "Провизводная функции f(x) = " << fx << " в точке x = " << x << ": f'(x) = " << dfx << " = " << eval << endl;
		}
	}
	catch (mu::Parser::exception_type& e) {// Вывод ошибки, при вычислении табличной производной с ошибкой
		cout << "Ошибка при вычислении функции: " << e.GetMsg() << endl;
	}
}

void table_derivative() { // Функция для вывода табличных производных и их дальнейших подсчет
	int choice;
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Функции: " << endl; // Вывод функций с соответсвующими индексами
	cout << "1: f(x) = c, c = const" << endl;
	cout << "2: f(x) = x^n" << endl;
	cout << "3: f(x) = a^x" << endl;
	cout << "4: f(x) = e^x" << endl;
	cout << "5: f(x) = log_a(x), a - основание логарифма, ОГРАНИЧЕНИЕ: x > 0; a > 0; a != 1" << endl;
	cout << "6: f(x) = ln(x), ОГРАНИЧЕНИЕ: x > 0" << endl;
	cout << "7: f(x) = sin(x)" << endl;
	cout << "8: f(x) = cos(x)" << endl;
	cout << "9: f(x) = sqrt(x)" << endl;
	cout << "10: f(x) = tg(x)" << endl;
	cout << "11: f(x) = ctg(x)" << endl;
	cout << "12: f(x) = arcsin(x)" << endl;
	cout << "13: f(x) = arccos(x)'" << endl;
	cout << "14: f(x) = arctg(x)" << endl;
	cout << "15: f(x) = atcctg(x)" << endl;
	cout << "Выберите функцию, производную которой вы хотите посчитать: ";
	cin >> choice;
	if (choice == 1) cout << "Производная константы всегда равна 0" << endl;
	else if (choice == 2) calculate_table_derivative("x^n", "n*x^(n-1)", false, true);
	else if (choice == 3) calculate_table_derivative("a^x", "a^(x)*ln(a)", true, false);
	else if (choice == 4) calculate_table_derivative("e^x", "e^x");
	else if (choice == 5) calculate_table_derivative("log_a(x)", "1/(x*ln(a))", true);
	else if (choice == 6) calculate_table_derivative("ln(x)", "1/x");
	else if (choice == 7) calculate_table_derivative("sin(x)", "cos(x)");
	else if (choice == 8) calculate_table_derivative("cos(x)", "-sin(x)");
	else if (choice == 9) calculate_table_derivative("sqrt(x)", "1/(2*sqrt(x))");
	else if (choice == 10) calculate_table_derivative("tg(x)", "1/(cos(x)^2)");
	else if (choice == 11) calculate_table_derivative("ctg(x)", "-1/(sin(x)^2)");
	else if (choice == 12) calculate_table_derivative("arcsin(x)", "1/(sqrt(1-x^2))");
	else if (choice == 13) calculate_table_derivative("arccos(x)", "-1/(sqrt(1-x^2))");
	else if (choice == 14) calculate_table_derivative("arctg(x)", "1/(1+x^2)");
	else if (choice == 15) calculate_table_derivative("arcctg(x)", "-1/(1+x^2)");
	else cout << "Несуществующий номер табличной производной..." << endl;
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
}


int main() { // Основная функция
	setlocale(LC_CTYPE, "russian");
	int action = 1;
	while (action != 0) {
		string action_tmp;
		cout << "Выберите действие: " << endl;
		cout << "0 - выход;" << endl;
		cout << "1 - увидеть инструкцию;" << endl;
		cout << "2 - рассчитать производную произвольной функции f(x);" << endl;
		cout << "3 - рассчитать табличную производную;" << endl;
		cout << "Ваше действие: ";
		cin >> action_tmp;
		if (!isconvertibleToDouble(action_tmp)) { // Проверка, что введенное действие является числом
			action = -1;
		}
		else action = stod(action_tmp);
		if (action == 0) exit(0);
		else if (action == 1) manual();
		else if (action == 2) derivative();
		else if (action == 3) table_derivative();
		else cout << "Выберите существующее дейстиве!" << endl;
	}

	return 0;
}