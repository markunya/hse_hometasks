#include "sort_students.h"
#include "tuple"

bool CompareStudentsWithDate(Student student_1, Student student_2) {
    std::tuple<int, int, int, std::string, std::string> student_1_tuple(student_1.birth_date.year, student_1.birth_date.month, student_1.birth_date.day, student_1.last_name, student_1.name);
    std::tuple<int, int, int, std::string, std::string> student_2_tuple(student_2.birth_date.year, student_2.birth_date.month, student_2.birth_date.day, student_2.last_name, student_2.name);
    return student_1_tuple < student_2_tuple;
}

bool CompareStudentsWithName(Student student_1, Student student_2) {
        std::tuple<std::string, std::string, int, int, int> student_1_tuple(student_1.last_name, student_1.name, student_1.birth_date.year, student_1.birth_date.month, student_1.birth_date.day);
        std::tuple<std::string, std::string, int, int, int> student_2_tuple(student_2.last_name, student_2.name, student_2.birth_date.year, student_2.birth_date.month, student_2.birth_date.day);
        return student_1_tuple < student_2_tuple;
    }

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    if (sortKind == SortKind::Date) {
        std::sort(students.begin(), students.end(), CompareStudentsWithDate);
    } else {
        std::sort(students.begin(), students.end(), CompareStudentsWithName);
    }
}
