#include "cc/time/time.h"

#include <stdatomic.h>
#include <time.h>

/// @brief Real @c time() API provided by libc.
/// @param tloc Nullable pointer to store the time.
/// @return Return value of @c time().
// NOLINTNEXTLINE(bugprone-reserved-identifier)
time_t __real_time(time_t *tloc);

/// @brief Wrapped @c time() API.
/// @param tloc Nullable pointer to store the time.
/// @return Wrapped value of @c time().
// NOLINTNEXTLINE(bugprone-reserved-identifier)
time_t __wrap_time(time_t *tloc);

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static _Atomic(time_func_ptr_t) func = __real_time;

void libc_replacer_overwrite_time(time_func_ptr_t func_new)
{
    atomic_store(&func, func_new);
}

void libc_replacer_reset_time(void)
{
    atomic_store(&func, __real_time);
}

time_t __wrap_time(time_t *tloc)
{
    time_func_ptr_t func_got = atomic_load(&func);
    return func_got(tloc);
}
