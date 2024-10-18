#include <gtest/gtest.h>
#include <libc_replacer/cc/interface.h>

#include <ctime>

namespace {

auto MockTime(time_t * /* tloc */) noexcept -> time_t {
  static constexpr time_t mock_time{123};
  return mock_time;
}

} // namespace

GTEST_TEST(TimeTest, ReplaceTime) {
  libc_replacer_overwrite_time(MockTime);
  const auto got = time(nullptr);
  libc_replacer_reset_time();
  GTEST_ASSERT_EQ(got, 123);
}
