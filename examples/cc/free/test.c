#include <libc_replacer/cc/interface.h>

#include <assert.h>
#include <stdlib.h>

static const int dummy = 123;

static void mock_free(void *ptr) { *(int *)ptr = dummy; }

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_free(mock_free);
  int value_local = 234;
  free(&value_local);
  assert(value_local == dummy);

  // Check the value after resetting
  libc_replacer_reset_free();
  return 0;
}
