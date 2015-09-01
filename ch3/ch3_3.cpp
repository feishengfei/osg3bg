#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main(
    int argc,
    char** argv)
{
    osg::ArgumentParser arguments(&argc, argv);
    std::string fileName;
    arguments.read("--model", fileName);

    osg::ref_ptr<osg::Node> root = osgDB::readNodeFile(fileName);
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
