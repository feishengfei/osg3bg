#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>

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
    viewer.addEventHandler(new osgViewer::StatsHandler());
    viewer.addEventHandler(new osgViewer::WindowSizeHandler());
    viewer.addEventHandler(new osgGA::StateSetManipulator(
        viewer.getCamera()->getOrCreateStateSet()
    )); 
    return viewer.run();
}
