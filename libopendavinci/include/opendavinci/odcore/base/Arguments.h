#include <cstring>
#include <memory>
#include <vector>

/**
 * Helper class to easily get argc and argv values from an initializer list.
 *
 * The template parameter is the type to be used for `argc`.
 */
template <typename I>
class ArgumentsT {
    public:
    ArgumentsT(std::initializer_list<std::string> argList)
        : argvPtr_(std::make_unique<char *[]>(argList.size()))
    {

        // copy the initializer list into this object
        I i = 0;
        for (const auto &arg : argList) {
            I lengthIncludingTerminatingZero = std::strlen(arg.c_str()) + 1;

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
    I argc() const
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
        I i = 0;
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

typedef ArgumentsT<int32_t> Arguments;
