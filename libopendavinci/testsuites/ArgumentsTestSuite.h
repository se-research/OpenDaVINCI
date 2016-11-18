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

    void testMoveAssign() {
        Arguments temporaryArgs{"hello", "world's", "end"};
        Arguments args = std::move(temporaryArgs);

        TS_ASSERT_EQUALS(3, args.argc);

        std::string hello("hello");
        TS_ASSERT_SAME_DATA(hello.c_str(), args.argv[0], hello.length() + 1);

        std::string worlds("world's");
        TS_ASSERT_SAME_DATA(worlds.c_str(), args.argv[1], worlds.length() + 1)

        std::string end("end");
        TS_ASSERT_SAME_DATA(end.c_str(), args.argv[2], end.length() + 1);
    }

    void testMoveConstructor() {
        Arguments temporaryArgs{"br", "--bar=1", "--baz=0", "--bass=true"};
        Arguments args(std::move(temporaryArgs));

        TS_ASSERT_EQUALS(4, args.argc);

        std::string arg0("br");
        TS_ASSERT_SAME_DATA(arg0.c_str(), args.argv[0], arg0.length() + 1);

        std::string arg1("--bar=1");
        TS_ASSERT_SAME_DATA(arg1.c_str(), args.argv[1], arg1.length() + 1);

        std::string arg2("--baz=0");
        TS_ASSERT_SAME_DATA(arg2.c_str(), args.argv[2], arg2.length() + 1);

        std::string arg3("--bass=true");
        TS_ASSERT_SAME_DATA(arg3.c_str(), args.argv[3], arg3.length() + 1);
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
