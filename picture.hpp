#pragma once

#include <iostream>
#include <string>
#include <vector>
#ifdef GTest
#include <gtest/gtest_prod.h>
#endif

using std::vector;

class Picture {
public:
    Picture() = default;
    Picture (size_t n, size_t m) : n(n), m(m) {
        field = vector<vector<uint8_t>>(n, vector<uint8_t>(m, 0));
        pow_p = vector<int64_t>(n, 1);
        pow_q = vector<int64_t>(m, 1);
        hash = vector<vector<int64_t>>(n + 1, vector<int64_t>(m + 1, 0));
    }

    Picture (const vector<vector<uint8_t>>& field) : n(field.size()), m(field[0].size()), field(field) {
        pow_p = vector<int64_t>(n, 1);
        pow_q = vector<int64_t>(m, 1);
        hash = vector<vector<int64_t>>(n + 1, vector<int64_t>(m + 1, 0));
    }

    //Считать картинку
    void ReadPicture() {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                int a;
                std::cin >> a;
                field[i][j] = a;
            }
        }
        CalculatePow(pow_p, p);
        CalculatePow(pow_q, q);
        CalculateHash();
    }

    //Найти картинку в нашей картинке, если не нашли возвращаем -1, -1
    std::pair<int, int> FindOtherPicture(const Picture& other) const {
        int64_t other_hash = other.hash[other.n][other.m];
        vector<std::pair<size_t, size_t>> ans;
        for (size_t i = 0; i <= n - other.n; ++i) {
            for (size_t j = 0; j <= m - other.m; ++j) {
                if (GetHash(i, j, i + other.n, j + other.m) == other_hash) {
                    ans.emplace_back(std::make_pair(i, j));
                }
            }
        }
        for (auto [x, y] : ans) {
            if (CheckPosition(x, y, other)) {
                return {x, y};
            }
        }
        return {-1, -1};
    }

    std::string FindLandmark(const Picture& other) const {
        std::pair<int, int> ans = FindOtherPicture(other);
        if (ans == std::make_pair(-1, -1)) {
            return "No picture =(";
        }
        else {
            return landmark[ans.first / (n / 3)][ans.second / (m / 3)];
        }
    }

private:
    //Подсчет хэша всех префиксных подматриц
    void CalculateHash() {
        for (size_t i = 1; i <= n; ++i) {
            for (size_t j = 1; j <= m; ++j) {
                hash[i][j] = 1 + field[i - 1][j - 1] + hash[i][j - 1] * p + hash[i - 1][j] * q - (hash[i - 1][j - 1] * p * q) % MOD;
                if (hash[i][j] < 0) {
                    hash[i][j] += MOD;
                }
                if (hash[i][j] > MOD) {
                    hash[i][j] %= MOD;
                }
            }
        }
    }

    //Получить хэш подматрицы (левые концы включены, правые не включены)
    int64_t GetHash(size_t x1, size_t y1, size_t x2, size_t y2) const {
        int64_t res = hash[x2][y2] - hash[x2][y1] * pow_p[y2 - y1] % MOD;
        res -= hash[x1][y2] * pow_q[x2 - x1] % MOD;
        res += (hash[x1][y1] * pow_p[y2 - y1]) % MOD * pow_q[x2 - x1];
        if (res < 0) {
            res += 2 * MOD;
        }
        if (res > MOD) {
            res %= MOD;
        }
        return res;
    }

    //Предподсчитаем все степени p и q (они используются в GetHash)
    void CalculatePow(vector<int64_t>& pow, int pp) {
        for (size_t i = 1; i < pow.size(); ++i) {
            pow[i] = pow[i - 1] * pp;
            if (pow[i] > MOD) {
                pow[i] %= MOD;
            }
        }
    }

    //Хэши могут заколлизиться из-за этого надо проверить, что подматрица с началами в x, y точно нужная подматрица
    bool CheckPosition(size_t x, size_t y, const Picture& other) const {
        for (size_t i = x; i < x + other.n; ++i) {
            for (size_t j = y; j < y + other.m; ++j) {
                if (field[i][j] != other.field[i - x][j - y])
                    return false;
            }
        }
        return true;
    }

private:
    size_t n, m; //Размеры картинки
    vector<vector<uint8_t>> field; //Сама картинка
    vector<vector<int64_t>> hash; //Все хэши префиксных подматриц
    vector<int64_t> pow_p; //Все степени p
    vector<int64_t> pow_q; //Все степени q

    vector<vector<std::string>> landmark = {{"Северо-запад", "Север", "Северо-восток"},
                                            {"Запад", "Центр изображения", "Восток"},
                                            {"Юго-запад", "Юг", "Юго-восток"}};

    static const int MOD = 1e9 + 7; //Модуль для хэшей
    static const int p = 257;
    static const int q = 263;
#ifdef GTest
    FRIEND_TEST(PictureTester, GetHashTest);
    FRIEND_TEST(PictureTester, CheckPositionTest);
#endif
};