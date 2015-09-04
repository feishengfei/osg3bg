#include <osg/GraphicsContext>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main(
    int /*argc*/,
    char** /*argv*/)
{
    osg::ref_ptr<osg::GraphicsContext::Traits> traits =
        new osg::GraphicsContext::Traits;
    traits->x = 50;
    traits->y = 50;
    traits->width = 800;
    traits->height = 600;
    traits->windowDecoration = true;
    traits->doubleBuffer = true;
    traits->samples = 4;

    osg::ref_ptr<osg::GraphicsContext> gc =
        osg::GraphicsContext::createGraphicsContext(traits.get());
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setGraphicsContext(gc.get());
    camera->setViewport(0, 0, traits->width, traits->height);
    camera->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
    camera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    camera->setClearColor(osg::Vec4(0.2f, 0.2f, 0.4f, 1.0f));
    camera->setProjectionMatrixAsPerspective(
        30.0f,
        static_cast<double>(traits->width) / traits->height,
        1.0,
        1000.0);

    osg::ref_ptr<osg::Node> root = osgDB::readNodeFile("cessna.osg");
    osgViewer::Viewer viewer;
    viewer.setCamera(camera.get());
    viewer.setSceneData(root.get());
    return viewer.run();
}
