#include <libc_replacer/cc/interface.h>

#include <assert.h>
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
  assert(got == mock_clock_value);
  assert(is_called);

  // Check the value after resetting
  libc_replacer_reset_clock();
  is_called = false;
  const clock_t got_after_reset = clock();
  assert(got_after_reset != mock_clock_value);
  assert(!is_called);

  return 0;
}
