#include <libc_replacer/cc/interface.h>

#include <assert.h>
#include <time.h>

static const clock_t mock_clock_value = 123;

static clock_t mock_clock(void) { return mock_clock_value; }

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_clock(mock_clock);
  const clock_t got = clock();
  assert(got == mock_clock_value);

  // Check the value after resetting
  libc_replacer_reset_clock();
  const clock_t got_after_reset = clock();
  assert(got_after_reset != mock_clock_value);

  return 0;
}
