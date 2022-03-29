#include <iostream>
#include <locale>
#include <string>
#include "picture.hpp"

int main() {
    setlocale(LC_ALL, "Russian");

    size_t n1, m1;
    std::cin >> n1 >> m1;
    Picture picture1 = Picture(n1, m1);
    picture1.ReadPicture();

    size_t n2, m2;
    std::cin >> n2 >> m2;
    Picture picture2 = Picture(n2, m2);
    picture2.ReadPicture();

    std::string is_landmark;
    getline(std::cin, is_landmark);
    getline(std::cin, is_landmark);

    if (is_landmark == "non accurate landmark") {
        std::cout << "Центр изображения\n";
        return 0;
    } else if (is_landmark == "accurate landmark") {
        std::cout << picture1.FindLandmark(picture2) << "\n";
    } else {
        std::pair<int, int> ans = picture1.FindOtherPicture(picture2);
        std::cout << ans.first << " " << ans.second << "\n";
    }
    return 0;
}