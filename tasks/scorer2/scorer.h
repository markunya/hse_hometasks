#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

using StudentName = std::string;
using TaskName = std::string;

using ScoreTable = std::map<StudentName, std::set<TaskName>>;

enum class EventType {
    CheckFailed,
    CheckSuccess,
    MergeRequestOpen,
    MergeRequestClosed,
};

class Scorer {
public:
    void OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
        if (!students_states_[student_name].contains(task_name)) {
            students_states_[student_name][task_name] =
                std::pair(EventType::CheckFailed, EventType::MergeRequestClosed);
        }
        students_states_[student_name][task_name].first = EventType::CheckFailed;
    };

    void OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
        if (!students_states_[student_name].contains(task_name)) {
            students_states_[student_name][task_name] =
                std::pair(EventType::CheckFailed, EventType::MergeRequestClosed);
        }
        students_states_[student_name][task_name].first = EventType::CheckSuccess;
    };

    void OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
        if (!students_states_[student_name].contains(task_name)) {
            students_states_[student_name][task_name] =
                std::pair(EventType::CheckFailed, EventType::MergeRequestClosed);
        }
        students_states_[student_name][task_name].second = EventType::MergeRequestOpen;
    };

    void OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
        if (!students_states_[student_name].contains(task_name)) {
            students_states_[student_name][task_name] =
                std::pair(EventType::CheckFailed, EventType::MergeRequestClosed);
        }
        students_states_[student_name][task_name].second = EventType::MergeRequestClosed;
    };

    void Reset() {
        students_states_.clear();
    };

    ScoreTable GetScoreTable() const {
        ScoreTable scored_students = {};
        for (auto it_1 = students_states_.begin(); it_1 != students_states_.end(); ++it_1) {
            for (auto it_2 = it_1->second.begin(); it_2 != it_1->second.end(); ++it_2) {
                if (it_2->second.first == EventType::CheckSuccess && it_2->second.second == EventType::MergeRequestClosed) {
                    scored_students[it_1->first].insert(it_2->first);
                }
            }
        }
        return scored_students;
    };

private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::pair<EventType, EventType>>> students_states_ =
        {};
};
