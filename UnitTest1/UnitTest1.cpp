#include "pch.h"
#include "CppUnitTest.h"
#include "../AP_Lab№10.2B/AP_Lab№10.2B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(StudentSystemTests)
    {
    public:
        TEST_METHOD(TestSort)
        {
            const int N = 3;
            Student* s = new Student[N];

            s[0].surname = "Петров";
            s[0].course = 2;
            s[0].specialty = COMP_SCIENCE;
            s[0].physics = 85;
            s[0].math = 90;
            s[0].programming = 95;

            s[1].surname = "Іванов";
            s[1].course = 1;
            s[1].specialty = COMP_SCIENCE;
            s[1].physics = 80;
            s[1].math = 85;
            s[1].programming = 95;

            s[2].surname = "Сидоров";
            s[2].course = 3;
            s[2].specialty = INFORMATICS;
            s[2].physics = 90;
            s[2].math = 95;
            s[2].numerical_methods = 88;

            Sort(s, N);

            Assert::AreEqual(s[0].surname, string("Іванов"));
            Assert::AreEqual(s[1].surname, string("Петров"));
            Assert::AreEqual(s[2].surname, string("Сидоров"));

            delete[] s;
        }

        TEST_METHOD(TestBinSearch)
        {
            const int N = 3;
            Student* s = new Student[N];

            s[0].surname = "Іванов";
            s[0].specialty = COMP_SCIENCE;
            s[0].programming = 95;

            s[1].surname = "Петров";
            s[1].specialty = COMP_SCIENCE;
            s[1].programming = 95;

            s[2].surname = "Сидоров";
            s[2].specialty = INFORMATICS;
            s[2].numerical_methods = 88;

            int found = BinSearch(s, N, "Петров", COMP_SCIENCE, 95);
            Assert::AreEqual(1, found);

            found = BinSearch(s, N, "Неіснуючий", COMP_SCIENCE, 95);
            Assert::AreEqual(-1, found);

            delete[] s;
        }
    };
}