#include <libc_replacer/cc/interface.h>
#include <testing/testing.h>

#include <stdbool.h>
#include <time.h>

static const clock_t mock_clock_value = 123;
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static bool is_called = false;

static clock_t mock_clock(void) {
  is_called = true;
  return mock_clock_value;
}

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_clock(mock_clock);
  const clock_t got = clock();
  TESTING_ASSERT_EQ(got, mock_clock_value);
  TESTING_ASSERT_TRUE(is_called);

  // Check the value after resetting
  libc_replacer_reset_clock();
  is_called = false;
  const clock_t got_after_reset = clock();
  TESTING_ASSERT_NE(got_after_reset, mock_clock_value);
  TESTING_ASSERT_FALSE(is_called);

  return 0;
}
