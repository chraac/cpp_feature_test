cmake_minimum_required(VERSION 3.6)

project(cpp.feature.test)

add_executable(cpp_feature_test
    common/main.cc
)

target_include_directories(cpp_feature_test PRIVATE
    third_party
)

target_sources(cpp_feature_test PRIVATE
    array_decay/array_decay.cc
)

if(MSVC)
    target_compile_options(cpp_feature_test PRIVATE
        /std:c++14
    )
else()
    target_compile_options(cpp_feature_test PRIVATE
        -std=c++14
    )
endif()
