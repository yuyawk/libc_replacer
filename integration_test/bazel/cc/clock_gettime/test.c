#include <libc_replacer/cc/interface.h>
#include <testing/testing.h>

#include <stdbool.h>
#include <time.h>

static const int mock_return_value = 123;
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static bool is_called = false;
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static clockid_t clock_id_got = -1;

// NOLINTNEXTLINE(readability-non-const-parameter)
static int mock_clock_gettime(clockid_t clk_id, struct timespec *ts_ptr) {
  (void)ts_ptr;
  is_called = true;
  clock_id_got = clk_id;
  return mock_return_value;
}

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_clock_gettime(mock_clock_gettime);
  const int got = clock_gettime(CLOCK_MONOTONIC, NULL);
  TESTING_ASSERT_EQ(got, mock_return_value);
  TESTING_ASSERT_TRUE(is_called);
  TESTING_ASSERT_EQ(clock_id_got, CLOCK_MONOTONIC);

  // Check the value after resetting
  libc_replacer_reset_clock_gettime();
  is_called = false;
  clock_id_got = -1;
  const time_t got_after_reset = clock_gettime(CLOCK_MONOTONIC, NULL);
  TESTING_ASSERT_NE(got_after_reset, mock_return_value);
  TESTING_ASSERT_FALSE(is_called);
  TESTING_ASSERT_EQ(clock_id_got, -1);

  return 0;
}
