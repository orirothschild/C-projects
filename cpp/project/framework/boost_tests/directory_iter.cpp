
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <iostream>

//gpd11 directory_iter.cpp -lboost_system -lboost_filesystem

int main()
{
    boost::filesystem::path p = boost::filesystem::current_path();
    boost::filesystem::directory_iterator it(p);

    //it->leaf();

    while (it != boost::filesystem::directory_iterator{})
    {
        //void rename( const path & source, const path & target );
        //it-
        std::cout << *it << '\n';
        it++;
    }


    return 0;
}