#include <libc_replacer/cc/interface.h>

#include <assert.h>
#include <time.h>

static time_t mock_time(time_t *tloc) {
  (void)tloc;
  return 123;
}

int main(void) {
  libc_replacer_overwrite_time(mock_time);
  const time_t got = time(NULL);
  libc_replacer_reset_time();
  assert(got == 123);
  const time_t got_after_reset = time(NULL);
  assert(got_after_reset != 123);

  return 0;
}
