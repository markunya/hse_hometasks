#include "admission.h"

bool CompareStudents(const Applicant* applicant_1, const Applicant* applicant_2) {
    int student_1_points_inv = -applicant_1->points;
    int student_2_points_inv = -applicant_2->points;
    return std::tie(student_1_points_inv, applicant_1->student.birth_date.year, applicant_1->student.birth_date.month, applicant_1->student.birth_date.day, applicant_1->student.name) < std::tie(student_2_points_inv,applicant_2->student.birth_date.year, applicant_2->student.birth_date.month, applicant_2->student.birth_date.day, applicant_2->student.name);
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::unordered_map<std::string, std::vector<const Student*>> result;
    std::unordered_map<std::string, size_t> universities_max_students;
    std::vector<const Applicant*> applicants_pointers;
    for (size_t i = 0; i < applicants.size(); ++i) {
        applicants_pointers.emplace_back( &applicants[i]);
    }
    std::sort(applicants_pointers.begin(), applicants_pointers.end(), CompareStudents);
    for (size_t i = 0; i < universities.size(); ++i) {
        universities_max_students[universities[i].name] = universities[i].max_students;
        result[universities[i].name] = {};
    }
    for (size_t i = 0; i < applicants_pointers.size(); ++i) {
        for (size_t j = 0; j < applicants_pointers[i]->wish_list.size(); ++j) {
            if (result[applicants_pointers[i]->wish_list[j]].size() < universities_max_students[applicants_pointers[i]->wish_list[j]]) {
                result[applicants_pointers[i]->wish_list[j]].emplace_back(&applicants_pointers[i]->student);
                break;
            }
        }
    }
    return result;
}
