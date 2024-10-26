#include <libc_replacer/cc/interface.h>
#include <testing/testing.h>

#include <stdlib.h>

static const size_t val_init = 0;
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static size_t nmemb_got = val_init;
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static size_t size_got = val_init;

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
static void *mock_calloc(size_t nmemb, size_t size) {
  TESTING_ASSERT_NE(nmemb, val_init); // precondition
  TESTING_ASSERT_NE(size, val_init);  // precondition

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
  TESTING_ASSERT_EQ(got, NULL);
  TESTING_ASSERT_EQ(nmemb_got, nmemb);
  TESTING_ASSERT_EQ(size_got, size);

  // Check the value after resetting
  libc_replacer_reset_calloc();
  nmemb_got = val_init;
  size_got = val_init;
  void *got_after_reset = calloc(nmemb, size);
  TESTING_ASSERT_NE(got_after_reset, NULL);
  TESTING_ASSERT_EQ(nmemb_got, val_init);
  TESTING_ASSERT_EQ(size_got, val_init);

  free(got_after_reset);

  return 0;
}
