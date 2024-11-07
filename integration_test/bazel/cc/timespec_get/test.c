#include <libc_replacer/cc/timespec_get.h>
#include <testing/testing.h>

#include <stdbool.h>
#include <time.h>

static const time_t mock_tv_sec_value = 123;
static const long mock_tv_nsec_value = 123000000000L;
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static bool is_called = false;

static int mock_timespec_get(struct timespec *ts_ptr, int base) {
  ts_ptr->tv_sec = mock_tv_sec_value;
  ts_ptr->tv_nsec = mock_tv_nsec_value;
  is_called = true;
  return base;
}

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_timespec_get(mock_timespec_get);
  struct timespec ts_value = {0};
  const int base = 1234;
  const int got = timespec_get(&ts_value, base);
  TESTING_ASSERT_EQ(got, base);
  TESTING_ASSERT_EQ(ts_value.tv_sec, mock_tv_sec_value);
  TESTING_ASSERT_EQ(ts_value.tv_nsec, mock_tv_nsec_value);
  TESTING_ASSERT_TRUE(is_called);

  // Check the values after resetting
  libc_replacer_reset_timespec_get();
  is_called = false;
  ts_value.tv_sec = 0;
  ts_value.tv_nsec = 0;
  const int new_base = 12;
  TESTING_ASSERT_NE(base, new_base); // invariant
  const int got_after_reset = timespec_get(&ts_value, new_base);
  TESTING_ASSERT_NE(got_after_reset, base);
  TESTING_ASSERT_NE(ts_value.tv_sec, mock_tv_sec_value);
  TESTING_ASSERT_NE(ts_value.tv_nsec, mock_tv_nsec_value);
  TESTING_ASSERT_FALSE(is_called);

  return 0;
}
