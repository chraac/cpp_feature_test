
#include <catch2/catch.hpp>
#include <cstdint>

namespace {

extern const char kTestString[] = "this is a test string";

template <const char arr[]>
struct TemplateParamArray {
  enum { SizeOfArray = sizeof(arr) };
};

template <const char *arr>
struct TemplateParamArrayPointer {
  enum { SizeOfArray = sizeof(arr) };
};

template <const char arr[], typename type>
struct TemplateParamArrayPartial {};

template <const char arr[], size_t count>
struct TemplateParamArrayPartial<arr, const char[count]> {
  enum { SizeOfArray = count };
};

template <const char arr[]>
struct TemplateParamArray2 {
  template <size_t size>
  static constexpr size_t GetArraySize(const char[size]) {
    return size;
  }

  enum { SizeOfArray = GetArraySize(arr) };
};

template <const char arr[], typename type = decltype(arr)>
struct TemplateParamArrayRedecl {
  enum { SizeOfArray = sizeof(type) };
};

/*
template <const char (&arr)[], typename type = decltype(arr)>
struct TemplateParamArrayReference {
  enum { SizeOfArray = sizeof(type) };
};
*/

}  // namespace

TEST_CASE("test for array decay", "cpp.feature.test") {
  auto TestArray = [](const char arr[]) {
    INFO("size of const char arr = " << sizeof(arr));
    REQUIRE(sizeof(arr) == sizeof(void *));
  };

  TestArray(kTestString);

  REQUIRE(TemplateParamArray<kTestString>::SizeOfArray == sizeof(void *));

  REQUIRE(TemplateParamArrayPointer<kTestString>::SizeOfArray ==
          sizeof(void *));

  REQUIRE(TemplateParamArrayPartial<kTestString,
                                    decltype(kTestString)>::SizeOfArray ==
          sizeof(kTestString));

  REQUIRE(TemplateParamArrayRedecl<kTestString>::SizeOfArray == sizeof(void *));

  // REQUIRE(TemplateParamArrayReference<kTestString>::SizeOfArray ==
  // sizeof(void *));
  // REQUIRE(TemplateParamArray2<kTestString>::SizeOfArray ==
  // sizeof(kTestString));
}
