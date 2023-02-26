#pragma once

#include <string_view>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cctype>
#include <string>
#include <valarray>

class SearchEngine {
public:
    void BuildIndex(std::string_view text) {
        strings_of_text_.clear();
        strings_amounts_of_words_.clear();
        strings_maps_.clear();
        self_tfs_.clear();
        self_idfs_.clear();
        tf_idfs_.clear();
        SeparateTextToStrings(text, strings_of_text_);
    };

    std::vector<std::string_view> Search(std::string_view query, size_t results_count) {
        std::vector<std::string_view> result = {};
        std::unordered_set<std::string> query_words = {};
        QueryToSet(query, query_words);
        for (size_t i = 0; i < strings_of_text_.size(); ++i) {
            StringOfTextToMap(strings_of_text_[i], strings_amounts_of_words_, strings_maps_);
            std::unordered_map<std::string, long double> self_tf = {};
            std::unordered_map<std::string, long double> self_idf = {};
            for (auto const& query_word : query_words) {
                self_tf[query_word] =
                    static_cast<long double>(strings_maps_[i][query_word]) / strings_amounts_of_words_[i];
                if (self_idf.contains(query_word)) {
                    self_idf[query_word] += 1;
                } else {
                    self_idf[query_word] = 1;
                }
            }
            self_tfs_.emplace_back(self_tf);
            self_idfs_.emplace_back(self_idf);
        }

        for (size_t i = 0; i < strings_of_text_.size(); ++i) {
            long double tf_idf = 0;
            for (auto const& query_word : query_words) {
                tf_idf += self_tfs_[i][query_word] *
                          std::log(static_cast<long double>(strings_of_text_.size()) / self_idfs_[i][query_word]);
            }
            tf_idfs_.emplace_back(std::pair(tf_idf, strings_of_text_.size() - i));
        }
        std::sort(tf_idfs_.begin(), tf_idfs_.end());
        size_t index = strings_of_text_.size() - 1;
        while (result.size() < results_count && index < tf_idfs_.size() && tf_idfs_[index].first > 0) {
            result.emplace_back(strings_of_text_[strings_of_text_.size() - tf_idfs_[index].second]);
            --index;
        }
        self_idfs_.clear();
        self_idfs_.clear();
        tf_idfs_.clear();
        strings_maps_.clear();
        strings_amounts_of_words_.clear();
        return result;
    };

private:
    std::vector<std::string_view> strings_of_text_ = {};
    std::vector<size_t> strings_amounts_of_words_ = {};
    std::vector<std::unordered_map<std::string, size_t>> strings_maps_ = {};
    std::vector<std::unordered_map<std::string, long double>> self_tfs_ = {};
    std::vector<std::unordered_map<std::string, long double>> self_idfs_ = {};
    std::vector<std::pair<long double, size_t>> tf_idfs_ = {};

    std::string ToLowerCase(std::string_view word) {
        std::string word_lower;
        for (auto j : word) {
            word_lower += static_cast<char>(std::tolower(j));
        }
        return word_lower;
    }

    void SeparateToWords(std::string_view query_item, std::unordered_set<std::string>& words) {
        size_t border = 0;
        for (size_t i = 0; i < query_item.length() + 1; ++i) {
            if (i == query_item.length() || !std::isalpha(query_item[i])) {
                std::string_view word = query_item.substr(border, i - border);
                if (!word.empty()) {
                    words.insert(ToLowerCase(word));
                }
                border = i + 1;
            }
        }
    }

    void SeparateToWords(std::string_view query_item, std::unordered_map<std::string, size_t>& str_map,
                         size_t& amount) {
        size_t border = 0;
        for (size_t i = 0; i < query_item.length() + 1; ++i) {
            if (i == query_item.length() || !std::isalpha(query_item[i])) {
                std::string_view word = query_item.substr(border, i - border);
                if (!word.empty()) {
                    if (str_map.contains(static_cast<std::string>(word))) {
                        str_map[ToLowerCase(word)] += 1;
                    } else {
                        str_map[ToLowerCase(word)] = 1;
                    }
                    amount += 1;
                }
                border = i + 1;
            }
        }
    }

    void QueryToSet(std::string_view query, std::unordered_set<std::string>& query_words) {
        size_t index_of_space = query.find(" ");
        while (index_of_space != std::string_view::npos) {
            std::string_view query_item = query.substr(0, index_of_space);
            SeparateToWords(query_item, query_words);
            query.remove_prefix(index_of_space + 1);
            index_of_space = query.find(" ");
        }
        SeparateToWords(query, query_words);
    }

    void SeparateTextToStrings(std::string_view text, std::vector<std::string_view>& strings_of_text) {
        size_t index_of_back_slash_n = text.find("\n");
        while (index_of_back_slash_n != std::string_view::npos) {
            std::string_view str = text.substr(0, index_of_back_slash_n);
            for (auto i : str) {
                if (std::isalpha(i)) {
                    strings_of_text.emplace_back(str);
                    break;
                }
            }
            text.remove_prefix(index_of_back_slash_n + 1);
            index_of_back_slash_n = text.find("\n");
        }
        for (auto i : text) {
            if (std::isalpha(i)) {
                strings_of_text.emplace_back(text);
                break;
            }
        }
    }

    void StringOfTextToMap(std::string_view str, std::vector<size_t>& strings_amounts_of_words,
                           std::vector<std::unordered_map<std::string, size_t>>& strings_maps) {
        size_t index_of_space = str.find(" ");
        size_t amount_of_words = 0;
        std::unordered_map<std::string, size_t> string_map = {};
        while (index_of_space != std::string_view::npos) {
            std::string_view query_item = str.substr(0, index_of_space);
            SeparateToWords(query_item, string_map, amount_of_words);
            str.remove_prefix(index_of_space + 1);
            index_of_space = str.find(" ");
        }
        SeparateToWords(str, string_map, amount_of_words);
        strings_amounts_of_words.emplace_back(amount_of_words);
        strings_maps.emplace_back(string_map);
    }
};
