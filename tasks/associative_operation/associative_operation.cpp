#include "associative_operation.h"

bool IsAssociative(const std::vector<std::vector<size_t>>& table) {
    int n = table.size();
    for (int i = 0; i < n; ++i) {
        if (table[i].size() != n) {
            return false;
        }
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (table[table[i][j]][k] != table[i][table[j][k]]) {
                    return false;
                }
            }
        }
    }
    return true;
}
