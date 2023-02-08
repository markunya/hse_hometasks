#include <unordered_map>
#include "scorer.h"

bool CompareEvents(const Event* event_1, const Event* event_2) {
    return event_1->time < event_2->time;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    ScoreTable scored_students = {};
    std::unordered_map<std::string, bool> students_merge;
    std::vector<const Event*> interesting_events = {};
    for (size_t i = 0; i < events.size(); ++i) {
        if (events[i].time <= score_time) {
            interesting_events.emplace_back(&events[i]);
        }
    }
    std::sort(interesting_events.begin(), interesting_events.end(), CompareEvents);
    for (size_t i = 0; i < interesting_events.size(); ++i) {
        if (interesting_events[i]->event_type == EventType::CheckSuccess && !students_merge[interesting_events[i]->student_name]) {
            scored_students[interesting_events[i]->student_name].insert(interesting_events[i]->task_name);
        }
        if (interesting_events[i]->event_type == EventType::MergeRequestClosed) {
            students_merge[interesting_events[i]->student_name] = false;
        }
        if (interesting_events[i]->event_type == EventType::MergeRequestOpen) {
            students_merge[interesting_events[i]->student_name] = true;
        }
    }
    return scored_students; // test
}
