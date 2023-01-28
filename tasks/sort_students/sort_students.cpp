#include "sort_students.h"
#include "tuple"

bool CompareStudentsWithDate(Student student_1, Student student_2) {
    return std::tie(student_1.birth_date.year, student_1.birth_date.month, student_1.birth_date.day, student_1.last_name, student_1.name) < std::tie(student_2.birth_date.year, student_2.birth_date.month, student_2.birth_date.day, student_2.last_name, student_2.name);
}

bool CompareStudentsWithName(Student student_1, Student student_2) {
    return std::tie(student_1.last_name, student_1.name, student_1.birth_date.year, student_1.birth_date.month, student_1.birth_date.day) < std::tie(student_2.last_name, student_2.name, student_2.birth_date.year, student_2.birth_date.month, student_2.birth_date.day);
}

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    if (sortKind == SortKind::Date) {
        std::sort(students.begin(), students.end(), CompareStudentsWithDate);
    } else {
        std::sort(students.begin(), students.end(), CompareStudentsWithName);
    }
}
