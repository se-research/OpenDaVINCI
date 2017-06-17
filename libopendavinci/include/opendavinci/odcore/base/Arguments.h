#ifndef ODCORE_BASE_ARGUMENTS_H_
#define ODCORE_BASE_ARGUMENTS_H_

#include <memory>
#include <vector>

namespace odcore {
    namespace base {

        /**
         * Helper class to easily get argc and argv values from an initializer list.
         *
         * Usage:
         *
         *     Arguments args{"foo", "bar"};
         *     Module mod1(args.argc, args.argv);
         *
         * There is no copy-, but a move-constructor / assignment.
         */
        class Arguments {
            public:
            Arguments(const std::initializer_list<std::string> & argList);

            Arguments(const Arguments &) = delete;
            Arguments(Arguments &&) = delete;

            void operator=(const Arguments &) = delete;
            void operator=(Arguments &&) = delete;

            private:
            /**
             * Vector containing the actual, allocated arguments
             */
            std::vector<std::unique_ptr<char[]>> argvValues_;

            /**
             * C-style array to return when calling argv(). Contains pointers to the
             * entries in argvValues_. Automatically deallocated on Arguments object
             * destruction.
             */
            std::unique_ptr<char* []> argvPtr_;

            public:
            const int32_t argc;
            char ** const argv;
        };
    }
}

#endif /* ODCORE_BASE_ARGUMENTS_H_ */
