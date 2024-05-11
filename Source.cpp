#include <iostream>
#include <string>
#include <locale.h>
#include <muParser.h> 
using namespace std;

bool isconvertibleToDouble(const std::string& s) { // ������� ��� �������� �������� ����������
	try {
		size_t pos;
		double value = std::stod(s, &pos);

		// ���������, ��� ��� ������ ���� ������������ ��� ��������������
		return pos == s.length();
	}
	catch (const std::invalid_argument&) {
		return false; // ������������ �������� (������ �� �����)
	}
	catch (const std::out_of_range&) {
		return false; // ��� ��������� ����� ���� double
	}
}

void manual() { // ����� ����������
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	cout << "����������: " << endl;
	cout << "��� ����� ������� f(x) ����������� � �������� ���������� ������ x" << endl;
	cout << "��� ���������� ����������� x ����� ���� ������ ������, ����� ��������� ����������" << endl;
	cout << "��� ��������� ���������� ����������� �������� ������������ �� ����������, ��������� � ��������� �������" << endl;
	cout << "�� ������ ������������ ��������� ��������� � ����� �������: " << endl;
	cout << "_pi = 3,14159 " << endl;
	cout << "_e = 2,71828 " << endl;
	cout << "�������������� ������� ������������ ������ � ��������� ����: " << endl;
	cout << "sin(x)     cos(x)     tan(x)" << endl;
	cout << "asin(x)    acos(x)    atan(x)" << endl;
	cout << "��������: ������� cot � acot ��� �������� ����������� ������������ ������� �������� �� ��������, ������ ��� �����������:" << endl;
	cout << "cot(x) ~ 1/tan(x)" << endl;
	cout << "acot(x) ~ atan(1/x)" << endl;
	cout << "����������� ��������: ln(x), �����������: x > 0" << endl;
	cout << "�������� � ���������� A: logA(x), �����������: x > 0; A > 0; A != 1" << endl;
	cout << "��� ���������� ��������� ����������� �����������: '+', '-', '*', '/', '^', '(', ')'" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
}

int derivative() { // ������� ��� �������� ����������� ������� ����� ����������
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	string function;
	string x_tmp;
	cout << "������� ������� f(x): ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ��� ���������� ������ getline()
	getline(cin, function); // ���� ������� f(x)
	cout << "���� ������� f(x) = " << function << endl;
	cout << "������� �������� x: ";
	cin >> x_tmp; // ���� �������� x
	if (!isconvertibleToDouble(x_tmp)) { // ��������, ��� ��������� x �������� ������
		cout << "������ ����� ��������� x" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		return 1;
	}
	double x, h = 0.001;
	x = stod(x_tmp);
	double tmp_1 = x + h; // tmp_1(2) ���������� ��� ����������� ���������� �����������
	double tmp_2 = x - h;

	mu::Parser parser_fx_minus_h;
	mu::Parser parser_fx_plus_h;

	try { // ������� ���������� ����������� (�����������, ���� �������� �� ���������� ���� x ���� ��������
		parser_fx_plus_h.SetExpr(function);
		parser_fx_plus_h.DefineVar("x", &tmp_1);
		double fx_plus = parser_fx_plus_h.Eval();
		parser_fx_minus_h.SetExpr(function);
		parser_fx_minus_h.DefineVar("x", &tmp_2);
		double fx_minus = parser_fx_minus_h.Eval();
		double derivative = (fx_plus - fx_minus) / (2 * h);
		cout << "������������ ������� f(x) = " << function << " � ����� x = " << x << " �����: " << derivative << endl;
	}
	catch (mu::Parser::exception_type& e) { // ����� ������, ��� ���������� ����������� � �������
		cout << "������ ��� ���������� �������: " << e.GetMsg() << endl;
	}
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	return 0;
}

int calculate_table_derivative(string fx, string dfx, bool fl_a = false, bool fl_n = false) { // ������� ��� �������� ��������� �����������
	cout << "���� f(x) = " << fx << ", �� f'(x) = " << dfx << endl;
	string x_tmp, n_tmp, a_tmp;
	mu::Parser df;
	try { // ������� ���������� ��������� �����������
		if (fl_a) {
			cout << "������� a: ";
			cin >> a_tmp;
			if (!isconvertibleToDouble(a_tmp)) { // ��������, ��� ��������� a �������� ������
				cout << "������ ����� ��������� a" << endl;
				return 1;
			}
			else {
				double a = stod(a_tmp);
				df.DefineVar("a", &a);
			}
		}
		if (fl_n) {
			cout << "������� n: ";
			cin >> n_tmp;
			if (!isconvertibleToDouble(n_tmp)) { // ��������, ��� ��������� n �������� ������
				cout << "������ ����� ��������� n" << endl;
				return 1;
			}
			else {
				double n = stod(n_tmp);
				df.DefineVar("n", &n);
			}
		}
		cout << "������� x: ";
		cin >> x_tmp;
		if (!isconvertibleToDouble(x_tmp)) {  // ��������, ��� ��������� x �������� ������
			cout << "������ ����� ��������� x" << endl;
			return 1;
		}
		else {
			double x = stod(x_tmp);
			df.DefineVar("x", &x);
			df.SetExpr(dfx);
			double eval = df.Eval();
			cout << "������������ ������� f(x) = " << fx << " � ����� x = " << x << ": f'(x) = " << dfx << " = " << eval << endl;
		}
	}
	catch (mu::Parser::exception_type& e) {// ����� ������, ��� ���������� ��������� ����������� � �������
		cout << "������ ��� ���������� �������: " << e.GetMsg() << endl;
	}
}

void table_derivative() { // ������� ��� ������ ��������� ����������� � �� ���������� �������
	int choice;
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	cout << "�������: " << endl; // ����� ������� � ��������������� ���������
	cout << "1: f(x) = c, c = const" << endl;
	cout << "2: f(x) = x^n" << endl;
	cout << "3: f(x) = a^x" << endl;
	cout << "4: f(x) = e^x" << endl;
	cout << "5: f(x) = log_a(x), a - ��������� ���������, �����������: x > 0; a > 0; a != 1" << endl;
	cout << "6: f(x) = ln(x), �����������: x > 0" << endl;
	cout << "7: f(x) = sin(x)" << endl;
	cout << "8: f(x) = cos(x)" << endl;
	cout << "9: f(x) = sqrt(x)" << endl;
	cout << "10: f(x) = tg(x)" << endl;
	cout << "11: f(x) = ctg(x)" << endl;
	cout << "12: f(x) = arcsin(x)" << endl;
	cout << "13: f(x) = arccos(x)'" << endl;
	cout << "14: f(x) = arctg(x)" << endl;
	cout << "15: f(x) = atcctg(x)" << endl;
	cout << "�������� �������, ����������� ������� �� ������ ���������: ";
	cin >> choice;
	if (choice == 1) cout << "����������� ��������� ������ ����� 0" << endl;
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
	else cout << "�������������� ����� ��������� �����������..." << endl;
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
}


int main() { // �������� �������
	setlocale(LC_CTYPE, "russian");
	int action = 1;
	while (action != 0) {
		string action_tmp;
		cout << "�������� ��������: " << endl;
		cout << "0 - �����;" << endl;
		cout << "1 - ������� ����������;" << endl;
		cout << "2 - ���������� ����������� ������������ ������� f(x);" << endl;
		cout << "3 - ���������� ��������� �����������;" << endl;
		cout << "���� ��������: ";
		cin >> action_tmp;
		if (!isconvertibleToDouble(action_tmp)) { // ��������, ��� ��������� �������� �������� ������
			action = -1;
		}
		else action = stod(action_tmp);
		if (action == 0) exit(0);
		else if (action == 1) manual();
		else if (action == 2) derivative();
		else if (action == 3) table_derivative();
		else cout << "�������� ������������ ��������!" << endl;
	}

	return 0;
}