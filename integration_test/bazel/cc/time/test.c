#include <libc_replacer/cc/interface.h>

#include <assert.h>
#include <stdbool.h>
#include <time.h>

static const time_t mock_time_value = 123;
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static bool is_called = false;

// NOLINTNEXTLINE(readability-non-const-parameter)
static time_t mock_time(time_t *tloc) {
  (void)tloc;
  is_called = true;
  return mock_time_value;
}

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_time(mock_time);
  const time_t got = time(NULL);
  assert(got == mock_time_value);
  assert(is_called);

  // Check the value after resetting
  libc_replacer_reset_time();
  is_called = false;
  const time_t got_after_reset = time(NULL);
  assert(got_after_reset != mock_time_value);
  assert(!is_called);

  return 0;
}
