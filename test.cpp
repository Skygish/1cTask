#define GTest
#include"picture.hpp"
#include<gtest/gtest.h>

class PictureTester: public ::testing::Test {};


TEST(PictureTester, SimpleTest) {
    Picture picture1({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
    Picture picture2({{0 , 1}, {3, 4}});
    std::pair<int, int> ans = {0, 0};
    ASSERT_EQ(picture1.FindOtherPicture(picture2), ans);
}

TEST(PictureTester, LandMarkTest) {
    Picture picture1({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
    Picture picture2({{0 , 1}, {3, 4}});
    ASSERT_EQ(picture1.FindLandmark(picture2), "Северо-запад");
}

TEST(PictureTester, GetHashTest) {
    Picture picture1({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
    picture1.CalculatePow(picture1.pow_p, picture1.p);
    picture1.CalculatePow(picture1.pow_q, picture1.q);
    picture1.CalculateHash();
    ASSERT_EQ(picture1.GetHash(1, 1, 2, 2), 5);
    ASSERT_EQ(picture1.GetHash(1, 1, 3, 3), 341598);
}

TEST(PictureTester, CheckPositionTest) {
    Picture picture1({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
    Picture picture2({{4, 5}, {7, 8}});
    ASSERT_TRUE(picture1.CheckPosition(1, 1, picture2));
    ASSERT_FALSE(picture1.CheckPosition(0, 0, picture2));
}
