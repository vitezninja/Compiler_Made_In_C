#include "../VM/vm.h"

int main(int argc, char *argv[])
{
    int result = runVM(argc, argv);
    if (result == -1)
    {
        return -1;
    }

    return 0;
}