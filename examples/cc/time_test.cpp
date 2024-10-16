#include <gtest/gtest.h>
#include <libc_replacer/cc/interface.h>

#include <ctime>

namespace
{

    time_t MockTime(time_t * /* tloc */)
    {
        return 123;
    }

}

GTEST_TEST(TimeTest, ReplaceTime)
{
    libc_replacer_overwrite_time(MockTime);
    const auto got = time(nullptr);
    libc_replacer_reset_time();
    GTEST_ASSERT_EQ(got, 123);
}
