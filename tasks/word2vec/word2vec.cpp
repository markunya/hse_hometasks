#include "word2vec.h"

#include <vector>

int DotProduct(std::vector<int> vector_1, std::vector<int> vector_2) {
    int dot_product = 0;
    for (size_t i = 0; i < vector_1.size(); ++i) {
        dot_product +=vector_1[i] * vector_2[i];
    }
    return dot_product;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    if (vectors.size() < 2) {
        return {};
    }
    std::vector<std::string> closest_words = {words[1]};
    int current_max_dot_product = DotProduct(vectors[0], vectors[1]);
    for (size_t i = 2; i < vectors.size(); ++i) {
        int current_dot_product = DotProduct(vectors[0], vectors[i]);
        if (current_dot_product > current_max_dot_product) {
            closest_words.clear();
            closest_words.emplace_back(words[i]);
            current_max_dot_product = current_dot_product;
        } else if (current_dot_product == current_max_dot_product) {
            closest_words.emplace_back(words[i]);
        }
    }
    return closest_words;
}
