#include "RemoteCommunication.h"

int32_t main(int32_t argc, char **argv) {
    automotive::miniature::RemoteCommunication p(argc, argv);
    return p.runModule();
}

