#pragma once

#include <random>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_set>
#include <queue>
#include <time.h>

struct Cell {
    size_t x = 0;
    size_t y = 0;

    bool operator==(const Cell& other) const {
        return std::tie(this->x, this->y) == std::tie(other.x, other.y);
    }
};

namespace std {
template<>
struct hash<Cell> {
    inline size_t operator()(const Cell& cell) const {
        return 16769023*cell.x*cell.y + 16127*cell.x +  3967*cell.y + 223;
    }
};
}

class Minesweeper {
public:

    enum class GameStatus {
        NOT_STARTED,
        IN_PROGRESS,
        VICTORY,
        DEFEAT,
    };

    using RenderedField = std::vector<std::string>;

    Minesweeper(size_t width, size_t height, size_t mines_count) {
        std::vector<Cell> shuffled_cells = {};
        for (size_t i = 0; i < height; ++i) {
            field_.emplace_back("");
            for (size_t j = 0; j < width; ++j) {
                const Cell cell = {.x = j, .y = i};
                shuffled_cells.emplace_back(cell);
                field_[i].push_back('-');
            }
        }
        std::shuffle(shuffled_cells.begin(), shuffled_cells.end(), std::mt19937(std::random_device()()));
        for (size_t i = 0; i < mines_count; ++i) {
            cells_with_mines_.insert(shuffled_cells[i]);
        }
    };

    Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
        for (auto cell : cells_with_mines) {
            cells_with_mines_.insert(cell);
        }
        for (size_t i = 0; i < height; ++i) {
            field_.emplace_back("");
            for (size_t j = 0; j < width; ++j) {
                field_[i].push_back('-');
            }
        }
    };

    void NewGame(size_t width, size_t height, size_t mines_count) {
        cells_with_mines_.clear();
        cells_without_mines.clear();
        field_.clear();
        game_status_ = GameStatus::NOT_STARTED;
        std::vector<Cell> shuffled_cells = {};
        for (size_t i = 0; i < height; ++i) {
            field_.emplace_back("");
            for (size_t j = 0; j < width; ++j) {
                const Cell cell = {.x = j, .y = i};
                shuffled_cells.emplace_back(cell);
                field_[i].push_back('-');
            }
        }
        std::shuffle(shuffled_cells.begin(), shuffled_cells.end(), std::mt19937(std::random_device()()));
        for (size_t i = 0; i < mines_count; ++i) {
            cells_with_mines_.insert(shuffled_cells[i]);
        }
    };

    void NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
        cells_with_mines_.clear();
        cells_without_mines.clear();
        field_.clear();
        game_status_ = GameStatus::NOT_STARTED;
        for (auto cell : cells_with_mines) {
            cells_with_mines_.insert(cell);
        }
        for (size_t i = 0; i < height; ++i) {
            field_.emplace_back("");
            for (size_t j = 0; j < width; ++j) {
                field_[i].push_back('-');
            }
        }
    };

    void OpenCell(const Cell& cell) {
        if (game_status_ != GameStatus::DEFEAT && game_status_ != GameStatus::VICTORY) {
        if (game_status_ == GameStatus::NOT_STARTED) {
                begin_ = clock();
                game_status_ = GameStatus::IN_PROGRESS;
        }
        if (cells_with_mines_.contains(cell)) {
            game_status_ = GameStatus::DEFEAT;
            end_ = clock();
            for (size_t i = 0; i < field_.size(); ++i) {
                for (size_t j = 0; j < field_[i].size(); ++j) {
                    Cell curr_cell = {.x = j, .y = i};
                    if (cells_with_mines_.contains(curr_cell)) {
                        field_[i][j] = '*';
                    } else {
                        field_[i][j] = '.';
                    }
                }
            }
        } else {
            std::queue<Cell> queue_of_cells = {};
            queue_of_cells.push(cell);
            std::unordered_set<Cell> cells_that_was_in_queue = {};
            while (!queue_of_cells.empty()) {
                Cell curr_cell = queue_of_cells.front();
                queue_of_cells.pop();
                cells_that_was_in_queue.insert(curr_cell);
                std::vector<Cell> candidates_to_be_in_queue;
                uint8_t amount_of_existing_cells = 0;
                if (curr_cell.x >= 1 && curr_cell.y >= 1) {
                    ++amount_of_existing_cells;
                    Cell check_on_mine = {.x = curr_cell.x - 1, .y = curr_cell.y - 1};
                    if (!cells_with_mines_.contains(check_on_mine)) {
                        candidates_to_be_in_queue.emplace_back(check_on_mine);
                    }
                }
                if (curr_cell.y >= 1) {
                    ++amount_of_existing_cells;
                    Cell check_on_mine = {.x = curr_cell.x, .y = curr_cell.y - 1};
                    if (!cells_with_mines_.contains(check_on_mine)) {
                        candidates_to_be_in_queue.emplace_back(check_on_mine);
                    }
                }
                if (curr_cell.x >= 1) {
                    ++amount_of_existing_cells;
                    Cell check_on_mine = {.x = curr_cell.x - 1, .y = curr_cell.y};
                    if (!cells_with_mines_.contains(check_on_mine)) {
                        candidates_to_be_in_queue.emplace_back(check_on_mine);
                    }
                }
                if (curr_cell.x + 1 < field_[0].size() && curr_cell.y + 1 < field_.size()) {
                    ++amount_of_existing_cells;
                    Cell check_on_mine = {.x = curr_cell.x + 1, .y = curr_cell.y + 1};
                    if (!cells_with_mines_.contains(check_on_mine)) {
                        candidates_to_be_in_queue.emplace_back(check_on_mine);
                    }
                }
                if (curr_cell.x + 1 < field_[0].size()) {
                    ++amount_of_existing_cells;
                    Cell check_on_mine = {.x = curr_cell.x + 1, .y = curr_cell.y};
                    if (!cells_with_mines_.contains(check_on_mine)) {
                        candidates_to_be_in_queue.emplace_back(check_on_mine);
                    }
                }
                if (curr_cell.y + 1 < field_.size()) {
                    ++amount_of_existing_cells;
                    Cell check_on_mine = {.x = curr_cell.x, .y = curr_cell.y + 1};
                    if (!cells_with_mines_.contains(check_on_mine)) {
                        candidates_to_be_in_queue.emplace_back(check_on_mine);
                    }
                }
                if (curr_cell.x >= 1 && curr_cell.y + 1 < field_.size()) {
                    ++amount_of_existing_cells;
                    Cell check_on_mine = {.x = curr_cell.x - 1, .y = curr_cell.y + 1};
                    if (!cells_with_mines_.contains(check_on_mine)) {
                        candidates_to_be_in_queue.emplace_back(check_on_mine);
                    }
                }
                if (curr_cell.x + 1 < field_[0].size() && curr_cell.y >= 1) {
                    ++amount_of_existing_cells;
                    Cell check_on_mine = {.x = curr_cell.x + 1, .y = curr_cell.y - 1};
                    if (!cells_with_mines_.contains(check_on_mine)) {
                        candidates_to_be_in_queue.emplace_back(check_on_mine);
                    }
                }
                if (candidates_to_be_in_queue.size() == amount_of_existing_cells) {
                    for (auto i : candidates_to_be_in_queue) {
                        if (!cells_that_was_in_queue.contains(i)) {
                            queue_of_cells.push(i);
                        }
                    }
                    if (field_[curr_cell.y][curr_cell.x] != '?') {
                        field_[curr_cell.y][curr_cell.x] = '.';
                        cells_without_mines.insert(curr_cell);
                        if (cells_without_mines.size() + cells_with_mines_.size() == field_.size()*field_[0].size()) {
                            game_status_ = GameStatus::VICTORY;
                            end_ = clock();
                        }
                    }
                } else {
                    if (field_[curr_cell.y][curr_cell.x] != '?') {
                        field_[curr_cell.y][curr_cell.x] = (amount_of_existing_cells - candidates_to_be_in_queue.size()) + '0';
                        cells_without_mines.insert(curr_cell);
                        if (cells_without_mines.size() + cells_with_mines_.size() == field_.size()*field_[0].size()) {
                            game_status_ = GameStatus::VICTORY;
                            end_ = clock();
                        }
                    }
                }
                candidates_to_be_in_queue.clear();
            }
        }
    }
    };

    void MarkCell(const Cell& cell) {
        if (game_status_ != GameStatus::DEFEAT && game_status_ != GameStatus::VICTORY) {
            if (game_status_ == GameStatus::NOT_STARTED) {
                begin_ = clock();
                game_status_ = GameStatus::IN_PROGRESS;
            }
            if (field_[cell.y][cell.x] == '?') {
                field_[cell.y][cell.x] = '-';
            } else if (field_[cell.y][cell.x] == '-') {
                field_[cell.y][cell.x] = '?';
            }
        }
    };

    GameStatus GetGameStatus() const {
        return game_status_;
    };

    time_t GetGameTime() const {
        if (game_status_ == GameStatus::NOT_STARTED) {
            return 0;
        }
        if (game_status_ == GameStatus::IN_PROGRESS) {
            clock_t now = clock();
            return static_cast<time_t>((now - begin_) / CLOCKS_PER_SEC);;
        }
        return static_cast<time_t>((end_ - begin_) / CLOCKS_PER_SEC);
    };

    RenderedField RenderField() const {
        return field_;
    };

private:
    std::unordered_set<Cell> cells_with_mines_;
    std::unordered_set<Cell> cells_without_mines;
    std::vector<std::string> field_;
    GameStatus game_status_;
    clock_t begin_;
    clock_t end_;
};
