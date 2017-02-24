#include <cstring>
#include <string>

#include "opendavinci/odcore/base/Arguments.h"

namespace odcore {
    namespace base {

        Arguments::Arguments(const std::initializer_list<std::string> & argList)
            : argvValues_()
            , argvPtr_(new char* [argList.size()])
            , argc(argList.size())
            , argv(argvPtr_.get())
        {
            // copy the initializer list into this object
            int32_t i = 0;
            for (const auto &arg : argList) {
                const size_t lengthIncludingTerminatingZero = arg.length() + 1;

                // allocate space
                argvValues_.emplace_back(new char[lengthIncludingTerminatingZero]);

                char * cstring = argvValues_.rbegin()->get();

                // copy content
                std::strncpy(cstring, arg.c_str(), lengthIncludingTerminatingZero);

                argvPtr_[i++] = cstring;
            }
        }

    }
}
