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
    for (auto event : interesting_events) {
        if (event->event_type == EventType::CheckSuccess) {
            scored_students[event->student_name].insert(event->task_name);
        } else if (event->event_type == EventType::MergeRequestClosed) {
            scored_students[event->student_name].insert(event->task_name);
        } else if (event->event_type == EventType::MergeRequestOpen) {
            scored_students[event->student_name].erase(event->task_name);
        }
    }
    return scored_students;  // test
}
