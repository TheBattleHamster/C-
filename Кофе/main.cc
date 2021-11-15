#include <iostream>
#include <iomanip>
#include <sstream>

int main() {
	int v=-2;
	while (v!=0) {
		std::cout << "1.Чай" << std::endl;
		std::cout << "2.Кофе" << std::endl;
		std::cout << "3.Молоко" << std::endl;
		std::cout << "0.Выход" << std::endl;
		std::string s;
		std::getline(std::cin, s);
		std::stringstream ss(s);
		ss >> v;
		if (std::cin.eof()) {
			std::cout << "Ошибка!" << std::endl;
			return 1;
		}
		if (ss.fail()) {
			v = -1;
			std::cout << "Come again?" << std::endl;
		}
		if ((v < 1 || v > 3) && v != 0)
			std::cout << "Не верный выход!" << std::endl;
		switch (v) {
		case 1:
			std::cout << "Чай готовится, ожидайте..." << std::endl;
			break;
		case 2:
			std::cout << "Кофе готовится, ожидайте..." << std::endl;
			break;
		case 3:
			std::cout << "Молоко готово!" << std::endl;
			break;
		}

	}

	return 0;
}

