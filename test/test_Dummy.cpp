#include <boost/test/unit_test.hpp>
#include <sempr/Dummy.hpp>

using namespace sempr;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    sempr::DummyClass dummy;
    dummy.welcome();
}
