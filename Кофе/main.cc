#include <iostream>
#include <iomanip>
#include <sstream>

int main() {
	int v=-2;
	while (v!=0) {
		std::cout << "1.���" << std::endl;
		std::cout << "2.����" << std::endl;
		std::cout << "3.������" << std::endl;
		std::cout << "0.�����" << std::endl;
		std::string s;
		std::getline(std::cin, s);
		std::stringstream ss(s);
		ss >> v;
		if (std::cin.eof()) {
			std::cout << "������!" << std::endl;
			return 1;
		}
		if (ss.fail()) {
			v = -1;
			std::cout << "Come again?" << std::endl;
		}
		if ((v < 1 || v > 3) && v != 0)
			std::cout << "�� ������ �����!" << std::endl;
		switch (v) {
		case 1:
			std::cout << "��� ���������, ��������..." << std::endl;
			break;
		case 2:
			std::cout << "���� ���������, ��������..." << std::endl;
			break;
		case 3:
			std::cout << "������ ������!" << std::endl;
			break;
		}

	}

	return 0;
}

