#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_10.2.A/LAb_10.2.A.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestCalculateAverage)
        {
           
            Student student;
            student.grade_physics = 4;
            student.grade_math = 5;
            student.grade_info = 3;

            double expected_average = (4 + 5 + 3) / 3.0;
            double actual_average = CalculateAverage(student);

            Assert::AreEqual(expected_average, actual_average, 0.001, L"—редний балл рассчитан неправильно");
        }

        TEST_METHOD(TestSortStudents)
        {
           
            Student students[3];
            students[0] = { "Ivanov", 2, ITIS, 5, 4, 3 };
            students[1] = { "Petrov", 1, KN, 3, 4, 5 };
            students[2] = { "Sidorov", 2, RE, 4, 5, 4 };

            SortStudents(students, 3);

           
            Assert::AreEqual(string("Petrov"), students[0].surname, L"—ортировка студентов по курсу и фамилии не удалась");
            Assert::AreEqual(string("Ivanov"), students[1].surname, L"—ортировка студентов по курсу и фамилии не удалась");
            Assert::AreEqual(string("Sidorov"), students[2].surname, L"—ортировка студентов по курсу и фамилии не удалась");
        }

        TEST_METHOD(TestBinarySearch)
        {
            
            Student students[3];
            students[0] = { "Ivanov", 2, ITIS, 5, 4, 3 };
            students[1] = { "Petrov", 1, KN, 3, 4, 5 };
            students[2] = { "Sidorov", 2, RE, 4, 5, 4 };

            SortStudents(students, 3); 

            bool found = BinarySearch(students, 3, "Petrov", 1, KN);
            Assert::IsTrue(found, L"—тудент Petrov не найден, хот€ должен быть найден");

            bool notFound = BinarySearch(students, 3, "Ivanov", 1, ITIS);
            Assert::IsFalse(notFound, L"—тудент Ivanov найден на неверном курсе");
        }
    };
}
