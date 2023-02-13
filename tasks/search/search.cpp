#include <unordered_set>
#include <cctype>
#include <unordered_map>
#include <valarray>
#include "search.h"

void SeparateToWords(std::string_view query_item, std::unordered_set<std::string_view>& words) {
    size_t border = 0;
    for (size_t i = 0; i < query_item.length() + 1; ++i) {
        if (i == query_item.length() || !std::isalpha(query_item[i])) {
            std::string_view word = query_item.substr(border, i - border);
            if (!word.empty()) {
                words.insert(word);
            }
            border = i + 1;
        }
    }
}

void SeparateToWords(std::string_view query_item, std::unordered_map<std::string_view, size_t>& str_map,
                     size_t& amount) {
    size_t border = 0;
    for (size_t i = 0; i < query_item.length() + 1; ++i) {
        if (i == query_item.length() || !std::isalpha(query_item[i])) {
            std::string_view word = query_item.substr(border, i - border);
            if (!word.empty()) {
                if (str_map.contains(word)) {
                    str_map[word] += 1;
                } else {
                    str_map[word] = 1;
                }
                amount += 1;
            }
            border = i + 1;
        }
    }
}

void QueryToSet(std::string_view query, std::unordered_set<std::string_view>& query_words) {
    size_t index_of_space = query.find(" ");
    while (index_of_space != std::string_view::npos) {
        std::string_view query_item = query.substr(0, index_of_space);
        SeparateToWords(query_item, query_words);
        query.remove_prefix(index_of_space + 1);
        index_of_space = query.find(" ");
    }
    SeparateToWords(query, query_words);
}

void SeparateTextToStrings (std::string_view text, std::vector<std::string_view>& strings_of_text) {
    size_t index_of_back_slash_n = text.find("\n");
    while (index_of_back_slash_n != std::string_view::npos) {
        std::string_view str = text.substr(0, index_of_back_slash_n);
        for (size_t i = 0; i < str.length(); ++i) {
            if (std::isalpha(str[i])) {
                strings_of_text.emplace_back(str);
                break;
            }
        }
        text.remove_prefix(index_of_back_slash_n + 1);
        index_of_back_slash_n = text.find("\n");
    }
    for (size_t i = 0; i < text.length(); ++i) {
        if (std::isalpha(text[i])) {
            strings_of_text.emplace_back(text);
            break;
        }
    }
}

void StringOfTextToMap (std::string_view str, std::vector<size_t>& strings_amounts_of_words,
                        std::vector<std::unordered_map<std::string_view, size_t>>& strings_maps) {
    size_t index_of_space = str.find(" ");
    size_t amount_of_words = 0;
    std::unordered_map<std::string_view, size_t> string_map = {};
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

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::vector<std::string_view> result = {};
    std::unordered_set<std::string_view> query_words = {};
    QueryToSet(query, query_words);
    std::vector<std::string_view> strings_of_text = {};
    std::vector<size_t> strings_amounts_of_words = {};
    std::vector<std::unordered_map<std::string_view, size_t>> strings_maps = {};
    std::vector<std::unordered_map<std::string_view, float>> self_tfs = {};
    std::vector<std::unordered_map<std::string_view, float>> self_idfs = {};
    std::vector<std::pair<float, size_t>> tf_idfs = {};
    SeparateTextToStrings(text, strings_of_text);
    for (size_t i = 0; i < strings_of_text.size(); ++i) {
        StringOfTextToMap(strings_of_text[i], strings_amounts_of_words, strings_maps);
        std::unordered_map<std::string_view, float> self_tf = {};
        std::unordered_map<std::string_view, float> self_idf = {};
        for (auto query_word : query_words) {
            self_tf[query_word] = static_cast<float>(strings_maps[i][query_word]) / strings_amounts_of_words[i];
            if (self_idf.contains(query_word)) {
                self_idf[query_word] += 1;
            } else {
                self_idf[query_word] = 1;
            }
        }
        self_tfs.emplace_back(self_tf);
        self_idfs.emplace_back(self_idf);
    }

    for (size_t i = 0; i < strings_of_text.size(); ++i) {
        float tf_idf = 0;
        for (auto query_word : query_words) {
            tf_idf += self_tfs[i][query_word] *
                      std::log(static_cast<float>(strings_of_text.size()) / self_idfs[i][query_word]);
        }
        tf_idfs.emplace_back(std::pair(tf_idf, strings_of_text.size() - i));
    }
    std::sort(tf_idfs.begin(), tf_idfs.end());
    size_t index = strings_of_text.size() - 1;
    while (result.size() < results_count && index < tf_idfs.size()) {
        result.emplace_back(strings_of_text[strings_of_text.size() - tf_idfs[index].second]);
        --index;
    }
    return result;
}
