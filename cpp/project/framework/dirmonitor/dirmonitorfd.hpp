#ifndef ILRD_DIRMONITORFD_HPP
#define ILRD_DIRMONITORFD_HPP

#include <string>

namespace ilrd
{

class DirMonitorFD
{
public:
    explicit DirMonitorFD();
    explicit DirMonitorFD(DirMonitorFD& fd, const std::string& path);
    ~DirMonitorFD();


    int GetDirMonitorFD() const;

private:
    int InitFDInitializer();
    int WatchFDInitializer(DirMonitorFD& fd, const std::string& path);



    int m_fd;
};

} // DirMonitorFD

#endif //ILRD_DIRMONITORFD_HPP
