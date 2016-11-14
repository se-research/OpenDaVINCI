#include <cstring>
#include <memory>
#include <vector>

/**
 * Helper class to easily get argc and argv values from an initializer list.
 *
 * The template parameter is the type to be used for `argc`.
 */
class Arguments {
    public:
    Arguments(std::initializer_list<std::string> argList)
        : argvPtr_(new char *[argList.size()])
        , argc(argList.size())
        , argv(argvPtr_.get())  
    {
        // copy the initializer list into this object
        int32_t i = 0;
        for (const auto &arg : argList) {
            const int32_t lengthIncludingTerminatingZero = arg.length() + 1;

            // allocate space
            argvValues_.emplace_back(new char[lengthIncludingTerminatingZero]);

            char * cstring = argvValues_.rbegin()->get();

            // copy content
            std::strncpy(cstring, arg.c_str(), lengthIncludingTerminatingZero);

            argvPtr_[i++] = cstring;
        }
    }

    const int32_t argc;
    char ** const argv;

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
    std::unique_ptr<char *[]> argvPtr_;
};
