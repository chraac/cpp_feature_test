cmake_minimum_required(VERSION 3.6)

project(cpp.feature.test)

add_executable(cpp_feature_test
    common/main.cc
)

target_sources(cpp_feature_test PRIVATE
    array_decay/array_decay.cc
)