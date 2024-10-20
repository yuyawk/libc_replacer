#include <libc_replacer/cc/interface.h>

#include <assert.h>
#include <time.h>

static clock_t mock_clock(void) { return 123.0; }

int main(void) {
  libc_replacer_overwrite_clock(mock_clock);
  const clock_t got = clock();
  libc_replacer_reset_clock();
  assert(got == 123.0);
  const clock_t got_after_reset = clock();
  assert(got_after_reset != 123.0);

  return 0;
}
