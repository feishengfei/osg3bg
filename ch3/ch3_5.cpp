#include <fstream>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

class LogFileHandler : public osg::NotifyHandler
{
public:
    LogFileHandler(const std::string& file)
    {
        _log.open(file.c_str());
    }
    virtual ~LogFileHandler()
    {
        _log.close();
    }

    virtual void notify(osg::NotifySeverity severity, const char* msg)
    {
        _log << msg;
    }

protected:
    std::ofstream _log;
};

int main(
    int argc,
    char** argv)
{
    osg::setNotifyLevel(osg::INFO);
    osg::setNotifyHandler(new LogFileHandler("output.txt"));

    osg::ArgumentParser arguments(&argc, argv);
    osg::ref_ptr<osg::Node> root = osgDB::readNodeFiles(arguments);
    if (!root)
    {
        OSG_FATAL << arguments.getApplicationName()
            << ": No data loaded." << std::endl;
        return -1;
    }

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
