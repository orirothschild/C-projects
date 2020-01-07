
#include "threadpool.hpp"
#include "utils.hpp"

using namespace ilrd;

int main()
{
    ThreadPool pool(1);

    pool.Shutdown(1);

    return 0;
}