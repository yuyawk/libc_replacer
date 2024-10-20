#include <libc_replacer/cc/interface.h>

#include <assert.h>
#include <time.h>

static const time_t mock_tv_sec_value = 123;
static const long mock_tv_nsec_value = 123000000000L;

static int mock_timespec_get(struct timespec *ts, int base) {
  ts->tv_sec = mock_tv_sec_value;
  ts->tv_nsec = mock_tv_nsec_value;
  return base;
}

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_timespec_get(mock_timespec_get);
  struct timespec ts = {0};
  const int base = 1234;
  const int got = timespec_get(&ts, base);
  assert(got == base);
  assert(ts.tv_sec == mock_tv_sec_value);
  assert(ts.tv_nsec == mock_tv_nsec_value);

  // Check the values after resetting
  libc_replacer_reset_timespec_get();
  ts.tv_sec = 0;
  ts.tv_nsec = 0;
  const int new_base = 12;
  assert(base != new_base); // invariant
  const int got_after_reset = timespec_get(&ts, new_base);
  assert(got_after_reset != base);
  assert(ts.tv_sec != mock_tv_sec_value);
  assert(ts.tv_nsec != mock_tv_nsec_value);

  return 0;
}
