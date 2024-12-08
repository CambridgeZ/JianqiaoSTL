//
// Created by Mac on 24-12-8.
//

#include <gtest/gtest.h>
#include <jianqiao/jianqiao_algorithm.hpp>
#include <jianqiao/jianqiao_vector.hpp>
#include <vector>

//TEST(test_sort, test_sort){
//    Jianqiao::vector<int> vec = {1, 3, 2, 4, 5, 6, 7, 8, 9, 10};
//    Jianqiao::sort(vec.begin(), vec.end());
//    for(int i = 0; i < vec.size(); ++i){
//        EXPECT_EQ(vec[i], i+1);
//    }
//}

TEST(test_sort, test_sort){
    std::vector<int> vec = {1, 3, 2, 4, 5, 6, 7, 8, 9, 10};
    Jianqiao::sort(vec.begin(), vec.end());
    for(int i = 0; i < vec.size(); ++i){
        EXPECT_EQ(vec[i], i+1);
    }
}

int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}