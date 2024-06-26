#include <iostream>
#include <vector>
#include <Windows.h>

class Alternative {
private:
    int AlternativeNumber;
    int Q1;
    int Q2;

public:
    Alternative(int alternativeNumber, int q1, int q2) : AlternativeNumber(alternativeNumber), Q1(q1), Q2(q2) {}

    bool Dominates(const Alternative& other) const {
        return Q1 >= other.Q1 && Q2 >= other.Q2 && (Q1 > other.Q1 || Q2 > other.Q2);
    }

    bool StrictlyDominates(const Alternative& other) const {
        return Q1 > other.Q1 && Q2 > other.Q2;
    }

    friend std::ostream& operator<<(std::ostream& os, const Alternative& alt) {
        os << "A" << alt.AlternativeNumber << ": Q1 = " << alt.Q1 << ", Q2 = " << alt.Q2;
        return os;
    }

    static std::vector<Alternative> createAlternativesList(const std::vector<int>& alternativesInt) {
        std::vector<Alternative> alternatives;

        for (int i = 0; i < alternativesInt.size(); i++) {
            int item = alternativesInt[i];
            int q1 = item / 10;
            int q2 = item % 10;

            alternatives.push_back(Alternative(i + 1, q1, q2));
        }
        return alternatives;
    }

    static std::vector<Alternative> Pareto(const std::vector<Alternative>& alternatives) {
        std::vector<Alternative> paretoList;

        for (size_t i = 0; i < alternatives.size(); i++) {
            bool isPareto = true;
            for (size_t j = 0; j < alternatives.size(); j++) {
                if (i != j && alternatives[j].Dominates(alternatives[i])) {
                    isPareto = false;
                    break;
                }
            }
            if (isPareto) {
                paretoList.push_back(alternatives[i]);
            }
        }
        return paretoList;
    }

    static std::vector<Alternative> Slater(const std::vector<Alternative>& alternatives) {
        std::vector<Alternative> slateList;

        for (size_t i = 0; i < alternatives.size(); i++) {
            bool isPareto = true;
            for (size_t j = 0; j < alternatives.size(); j++) {
                if (i != j && alternatives[j].StrictlyDominates(alternatives[i])) {
                    isPareto = false;
                    break;
                }
            }
            if (isPareto) {
                slateList.push_back(alternatives[i]);
            }
        }
        return slateList;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::vector<int> alternativesInt = { 90, 54, 50, 31, 13, 57, 94, 81, 81, 3, 20, 33, 82, 81, 87, 15, 96, 25, 4, 22 };
    std::vector<Alternative> alternatives = Alternative::createAlternativesList(alternativesInt);

    std::cout << std::endl;

    if (!alternatives.empty()) {
        for (const Alternative& alternative : alternatives) {
            std::cout << "(" << alternative << ")" << std::endl;
        }

        std::cout << std::endl << "�� ������:" << std::endl;
        std::vector<Alternative> paretoList = Alternative::Pareto(alternatives);
        for (const Alternative& alternative : paretoList) {
            std::cout << "(" << alternative << ")" << std::endl;
        }

        std::cout << std::endl << "�� ���������:" << std::endl;
        std::vector<Alternative> slateList = Alternative::Slater(alternatives);
        for (const Alternative& alternative : slateList) {
            std::cout << "(" << alternative << ")" << std::endl;
        }
    }
    else {
        std::cout << "������ ����������� ��������." << std::endl;
    }

    return 0;
}
