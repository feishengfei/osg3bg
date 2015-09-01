#include <iostream>
#include <osg/Referenced>
#include <osg/ref_ptr>

class MonitoringTarget : public osg::Referenced
{
public:
    MonitoringTarget(unsigned int id) : id_(id)
    {
        std::cout << "Constructing target " << id_ << std::endl;
    }

protected:
    virtual ~MonitoringTarget()
    {
        std::cout << "Destroying target " << id_ << std::endl;
    }

    unsigned int id_;
};

MonitoringTarget* createMonitoringTarget(unsigned int id)
{
    osg::ref_ptr<MonitoringTarget> target = new MonitoringTarget(id);
    return target.release();
}

int main(
    int /*argc*/,
    char** /*argv*/)
{
    osg::ref_ptr<MonitoringTarget> target = new MonitoringTarget(0);
    std::cout << "Reference count before referring: "
        << target->referenceCount() << std::endl;
    osg::ref_ptr<MonitoringTarget> anotherTarget = target;
    std::cout << "Reference count after referring: "
        << target->referenceCount() << std::endl;

    for (unsigned int i = 1; i < 5; ++i)
    {
        osg::ref_ptr<MonitoringTarget> subTarget =
#if 0
            new MonitoringTarget(i);
#else
            createMonitoringTarget(i);
#endif
    }
}
