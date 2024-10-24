#include <libc_replacer/cc/interface.h>

#include <assert.h>
#include <stdlib.h>

static void *mock_calloc(size_t nmemb, size_t size) {
  (void)nmemb;
  (void)size;
  return NULL;
}

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_calloc(mock_calloc);
  const size_t nmemb = 1;
  const size_t size = 1;
  const void *got = calloc(nmemb, size);
  assert(got == NULL);

  // Check the value after resetting
  libc_replacer_reset_calloc();
  const void *got_after_reset = calloc(nmemb, size);
  assert(got_after_reset != NULL);

  return 0;
}
