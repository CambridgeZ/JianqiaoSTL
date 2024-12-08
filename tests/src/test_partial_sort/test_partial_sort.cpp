//
// Created by Mac on 24-12-8.
//

#include <gtest/gtest.h>
#include <jianqiao/advanced_algorithm/partial_sort.hpp>
#include <jianqiao/jianqiao_vector.hpp>

#include <vector>

TEST(test_partial_sort, test_partial_sort) {
    Jianqiao::vector<int> vec = {3, 2, 1, 5, 4, 6, 7, 9, 8};
    Jianqiao::partial_sort(vec.begin(), vec.begin() + 5, vec.end());
    std::vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(vec[i], vec2[i]);
    }
}

//TEST(test_partial_sort, test_partial_sort) {
//    std::vector<int> vec = {3, 2, 1, 5, 4, 6, 7, 9, 8};
//    Jianqiao::partial_sort(vec.begin(), vec.begin() + 5, vec.end());
//    std::vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//    for (size_t i = 0; i < vec.size(); ++i) {
//        EXPECT_EQ(vec[i], vec2[i]);
//    }
//}

//TEST(test_partial_sort, test_partial_sort_comp) {
//    std::vector<int> vec = {3, 2, 1, 5, 4, 6, 7, 9, 8};
//    Jianqiao::partial_sort(vec.begin(), vec.begin() + 5, vec.end(), std::greater<int>());
//    std::vector<int> vec2 = {9, 8, 7, 6, 5, 1, 2, 3, 4};
//    for (size_t i = 0; i < vec.size(); ++i) {
//        EXPECT_EQ(vec[i], vec2[i]);
//    }
//}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


