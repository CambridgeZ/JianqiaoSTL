//
// Created by Mac on 24-12-8.
//

#include <gtest/gtest.h>
#include <jianqiao/jianqiao_algorithm.hpp>
#include <jianqiao/jianqiao_vector.hpp>
#include <iostream>
#include <vector>
#include <random>

TEST(test_random_shuffle, test_random_shuffle) {
    Jianqiao::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Jianqiao::random_shuffle(vec.begin(), vec.end());
    for (auto i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

TEST(test_random_shuffle_std, test_random_shuffle_std) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Jianqiao::random_shuffle(vec.begin(), vec.end());
    for (auto i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

//TEST(test_random_shuffle_std_notdefault, test_random_shuffle2_std_notdefault) {
//    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//    std::default_random_engine rng;
//    Jianqiao::random_shuffle(vec.begin(), vec.end(), rng);
//    for (auto i : vec) {
//        std::cout << i << " ";
//    }
//    std::cout << std::endl;
//}

//TEST(test_random_shuffle, test_random_shuffle3) {
//    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//    Jianqiao::random_shuffle(vec.begin(), vec.end(), std::default_random_engine());
//    for (auto i : vec) {
//        std::cout << i << " ";
//    }
//    std::cout << std::endl;
//}
//
//TEST(test_random_shuffle, test_random_shuffle4) {
//    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//    Jianqiao::random_shuffle(vec.begin(), vec.end(), std::default_random_engine());
//    for (auto i : vec) {
//        std::cout << i << " ";
//    }
//    std::cout << std::endl;
//}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
