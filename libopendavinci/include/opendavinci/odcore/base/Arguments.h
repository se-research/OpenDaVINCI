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
        : argvPtr_(std::make_unique<char *[]>(argList.size()))
    {

        // copy the initializer list into this object
        int32_t i = 0;
        for (const auto &arg : argList) {
            int32_t lengthIncludingTerminatingZero = std::strlen(arg.c_str()) + 1;

            // allocate space
            auto cArg = std::make_unique<char[]>(lengthIncludingTerminatingZero);

            // copy content
            std::strncpy(cArg.get(), arg.c_str(), lengthIncludingTerminatingZero);

            // save in the vector
            argvValues_.push_back(std::move(cArg));
        }
    }

    /**
     * Get the number of arguments.
     */
    int32_t argc() const
    {
        return argvValues_.size();
    }

    /**
     * Get a C-style string array containing the arguments. This gets freed
     * when the Arguments object is destructed, so manual freeing is not needed,
     * but it should be taken care of that the Arguments object lifetime is
     * longer than the last use of the return value of this function.
     */
    char **argv() const
    {
        // build the argvPtr_ object to contain pointers to the strings
        // in argvValues_.
        int32_t i = 0;
        for (const auto &arg : argvValues_) {
            argvPtr_[i++] = arg.get();
        }

        return argvPtr_.get();
    }

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
