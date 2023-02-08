#include <deque>
#include "tests_checking.h"

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<const StudentAction*> tests_deque = {};
    std::vector<std::string> result = {};
    for (size_t i = 0; i < student_actions.size(); ++i) {
        if (student_actions[i].side == Side::Top) {
            tests_deque.emplace_front(&student_actions[i]);
        } else {
            tests_deque.emplace_back(&student_actions[i]);
        }
    }
    for (auto querie : queries) {
        result.emplace_back(tests_deque.at(querie - 1)->name);
    }
    return result;
}
