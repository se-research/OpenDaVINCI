#ifndef ODCORE_BASE_ARGUMENTSTESTSUITE_H_
#define ODCORE_BASE_ARGUMENTSTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include "opendavinci/odcore/base/Arguments.h"

using odcore::base::Arguments;

class ArgumentsTestSuite : public CxxTest::TestSuite {
public:
    void testEmptyInstantiation() {
        Arguments args{};

        TS_ASSERT(0 == args.argc);
    }

    void testInstantiation() {
        Arguments args{"foo", "bara"};

        TS_ASSERT_EQUALS(2, args.argc);

        std::string foo("foo");
        TS_ASSERT_SAME_DATA(foo.c_str(), args.argv[0], foo.length() + 1);

        std::string bara("bara");
        TS_ASSERT_SAME_DATA(bara.c_str(), args.argv[1], bara.length() + 1)
    }

    static void fooBarConsumer(int32_t argc, char ** argv) {
        TS_ASSERT_EQUALS(2, argc);

        std::string foo("foo");
        TS_ASSERT_SAME_DATA(foo.c_str(), argv[0], foo.length() + 1);

        std::string bar("bar");
        TS_ASSERT_SAME_DATA(bar.c_str(), argv[1], bar.length() + 1);

        const size_t blaLength = 4;
        char blaContent[blaLength] = {'b', 'l', 'a', '\0'};
        argv[0] = blaContent;

        std::string bla("bla");
        TS_ASSERT_SAME_DATA(bla.c_str(), argv[0], blaLength);

        argv[1][1] = 'o';
        std::string bor("bor");
        TS_ASSERT_SAME_DATA(bor.c_str(), argv[1], bor.length() + 1);
    }

    void testUseInsideManipulativeMethod() {
        Arguments args{"foo", "bar"};
        fooBarConsumer(args.argc, args.argv);
    }
};

#endif /* ODCORE_BASE_ARGUMENTSTESTSUITE_H_ */
