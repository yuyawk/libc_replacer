#include <libc_replacer/cc/interface.h>

#include <assert.h>
#include <stdlib.h>

static const size_t val_init = 0;
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static size_t nmemb_got = val_init;
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static size_t size_got = val_init;

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
static void *mock_calloc(size_t nmemb, size_t size) {
  assert(nmemb != val_init); // precondition
  assert(size != val_init);  // precondition

  nmemb_got = nmemb;
  size_got = size;
  return NULL;
}

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_calloc(mock_calloc);
  const size_t nmemb = 1;
  const size_t size = 1;
  const void *got = calloc(nmemb, size);
  assert(got == NULL);
  assert(nmemb_got == nmemb);
  assert(size_got == size);

  // Check the value after resetting
  libc_replacer_reset_calloc();
  nmemb_got = val_init;
  size_got = val_init;
  void *got_after_reset = calloc(nmemb, size);
  assert(got_after_reset != NULL);
  assert(nmemb_got == val_init);
  assert(size_got == val_init);

  free(got_after_reset);

  return 0;
}
