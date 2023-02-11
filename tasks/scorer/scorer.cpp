#include <unordered_map>
#include "scorer.h"

bool CompareEvents(const Event* event_1, const Event* event_2) {
    return event_1->time < event_2->time;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    ScoreTable scored_students = {};
    std::vector<const Event*> interesting_events = {};
    for (size_t i = 0; i < events.size(); ++i) {
        if (events[i].time <= score_time) {
            interesting_events.emplace_back(&events[i]);
        }
    }
    std::sort(interesting_events.begin(), interesting_events.end(), CompareEvents);
    std::unordered_map<std::string, std::unordered_map<std::string, std::pair<EventType, EventType>>> students_states = {};
    for (auto student : interesting_events) {
        if (!students_states[student->student_name].contains(student->task_name)) {
            students_states[student->student_name][student->task_name] = std::pair(EventType::CheckFailed, EventType::MergeRequestClosed);
        }
        if (student->event_type == EventType::MergeRequestOpen) {
            students_states[student->student_name][student->task_name].second = EventType::MergeRequestOpen;
        }
        if (student->event_type == EventType::MergeRequestClosed) {
            students_states[student->student_name][student->task_name].second = EventType::MergeRequestClosed;
        }
        if (student->event_type == EventType::CheckSuccess) {
            students_states[student->student_name][student->task_name].first = EventType::CheckSuccess;
        }
        if (student->event_type == EventType::CheckFailed) {
            students_states[student->student_name][student->task_name].first = EventType::CheckFailed;
        }
    }
    for (auto it_1 = students_states.begin(); it_1 != students_states.end(); ++it_1) {
        for (auto it_2 = it_1->second.begin(); it_2 != it_1->second.end(); ++it_2) {
            if (it_2->second.first == EventType::CheckSuccess && it_2->second.second == EventType::MergeRequestClosed) {
                scored_students[it_1->first].insert(it_2->first);
            }
        }
    }
    return scored_students;  // test
}
