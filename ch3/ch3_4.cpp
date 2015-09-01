#include <osg/Notify>

int main(
    int /*argc*/,
    char** /*argv*/)
{
    osg::notify(osg::WARN) << "Some warning message." << std::endl;
    return 0;
}
