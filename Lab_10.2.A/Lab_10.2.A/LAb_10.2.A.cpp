#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <Windows.h>
using namespace std;

enum Speciality { ITIS, RE, KN, KI, PZ };
string speciality_str[] = { "�����������", "��������������", "����'����� �����", "����'������ ��������", "��������� ������������" };

struct Student {
    string surname;
    int course;
    Speciality speciality;
    int grade_physics;
    int grade_math;
    int grade_info;
};

void Create(Student* students, int N);
void Print(const Student* students, int N);
void SortStudents(Student* students, int N);
bool BinarySearch(const Student* students, int N, const string& surname, int course, Speciality speciality);
double CalculateAverage(const Student& student);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N;
    cout << "������ ������� ��������: ";
    cin >> N;
    Student* students = new Student[N];

    int choice;
    do {
        cout << "\n������ ��:\n";
        cout << "1 - ������ ���������� ��� ��������\n";
        cout << "2 - ������� ���������� ��� ��������\n";
        cout << "3 - ��������� ���������� ��� ��������\n";
        cout << "4 - ����� ��������\n";
        cout << "0 - ��������� ������ ��������\n";
        cout << "����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            Create(students, N);
            break;
        case 2:
            Print(students, N);
            break;
        case 3:
            SortStudents(students, N);
            Print(students, N);
            break;
        case 4: {
            string surname;
            int course;
            int speciality;
            cout << "������ ������� ��� ������: ";
            cin >> surname;
            cout << "������ ����: ";
            cin >> course;
            cout << "������ ������������ (0 - �����������, 1 - ��������������, 2 - ����'����� �����, 3 - ����'������ ��������, 4 - ��������� ������������): ";
            cin >> speciality;

            if (BinarySearch(students, N, surname, course, static_cast<Speciality>(speciality))) {
                cout << "������� ���������.\n";
            }
            else {
                cout << "�������� �� ��������.\n";
            }
            break;
        }
        case 0:
            cout << "���������� ������.\n";
            break;
        default:
            cout << "������� ����. ��������� �� ���.\n";
            break;
        }
    } while (choice != 0);

    delete[] students;
    return 0;
}

void Create(Student* students, int N) {
    for (int i = 0; i < N; i++) {
        cout << "\n����� ��������: " << i + 1 << endl;
        cout << "�������: "; cin >> students[i].surname;

        do {
            cout << "���� (1-6): "; cin >> students[i].course;
        } while (students[i].course < 1 || students[i].course > 6);

        int spec;
        do {
            cout << "������������ (0 - �����������, 1 - ��������������, 2 - ����'����� �����, 3 - ����'������ ��������, 4 - ��������� ������������): ";
            cin >> spec;
        } while (spec < 0 || spec > 4);
        students[i].speciality = static_cast<Speciality>(spec);

        do {
            cout << "������ � ������ (1-5): "; cin >> students[i].grade_physics;
        } while (students[i].grade_physics < 1 || students[i].grade_physics > 5);

        do {
            cout << "������ � ���������� (1-5): "; cin >> students[i].grade_math;
        } while (students[i].grade_math < 1 || students[i].grade_math > 5);

        do {
            cout << "������ � ����������� (1-5): "; cin >> students[i].grade_info;
        } while (students[i].grade_info < 1 || students[i].grade_info > 5);
    }
}

void Print(const Student* students, int N) {
    cout << "\n=================================================================================================" << endl;
    cout << "| � |   �������   |  ����  |     ������������     |  Գ����  |  ����������  |  �����������  |" << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1 << " | " << setw(12) << students[i].surname << " | "
            << setw(6) << students[i].course << " | " << setw(20) << speciality_str[students[i].speciality]
            << " | " << setw(7) << students[i].grade_physics << " | " << setw(11) << students[i].grade_math
            << " | " << setw(12) << students[i].grade_info << " |\n";
    }
    cout << "=================================================================================================" << endl;
}

void SortStudents(Student* students, int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (students[j].course > students[j + 1].course ||
                (students[j].course == students[j + 1].course && students[j].surname > students[j + 1].surname) ||
                (students[j].course == students[j + 1].course && students[j].surname == students[j + 1].surname && students[j].speciality > students[j + 1].speciality)) {
                swap(students[j], students[j + 1]);
            }
        }
    }
}

bool BinarySearch(const Student* students, int N, const string& surname, int course, Speciality speciality) {
    int left = 0, right = N - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (students[mid].surname == surname && students[mid].course == course && students[mid].speciality == speciality) {
            return true;
        }
        else if (students[mid].course < course || (students[mid].course == course && students[mid].surname < surname) ||
            (students[mid].course == course && students[mid].surname == surname && students[mid].speciality < speciality)) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return false;
}

double CalculateAverage(const Student& student) {
    return (student.grade_physics + student.grade_math + student.grade_info) / 3.0;
}
