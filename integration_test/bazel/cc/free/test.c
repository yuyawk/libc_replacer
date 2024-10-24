#include <libc_replacer/cc/interface.h>

#include <assert.h>
#include <stdlib.h>

static const int dummy = 123;

static void mock_free(void *ptr) { *(int *)ptr = dummy; }

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_free(mock_free);
  const int value_init = 234;
  assert(value_init != dummy); // invariant
  int value_local = value_init;
  // NOLINTNEXTLINE(clang-analyzer-unix.Malloc)
  free(&value_local);
  assert(value_local == dummy);

  // Check the value after resetting
  libc_replacer_reset_free();
  return 0;
}
