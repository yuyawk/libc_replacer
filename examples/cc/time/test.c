#include <libc_replacer/cc/interface.h>

#include <assert.h>
#include <time.h>

static const time_t mock_time_value = 123;

// NOLINTNEXTLINE(readability-non-const-parameter)
static time_t mock_time(time_t *tloc) {
  (void)tloc;
  return mock_time_value;
}

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_time(mock_time);
  const time_t got = time(NULL);
  assert(got == mock_time_value);

  // Check the value after resetting
  libc_replacer_reset_time();
  const time_t got_after_reset = time(NULL);
  assert(got_after_reset != mock_time_value);

  return 0;
}
