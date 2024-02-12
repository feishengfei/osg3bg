#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>

int main(
    int /*argc*/,
    char** /*argv*/)
{
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("cessna.osg");

    osg::ref_ptr<osg::MatrixTransform> transformation1 = new osg::MatrixTransform;
    transformation1->setMatrix(osg::Matrix::translate(-25.0f, 0.0f, 0.0f)*osg::Matrix::scale(2.0f, 2.0f, 2.0f));
    transformation1->addChild(model.get());

    osg::ref_ptr<osg::MatrixTransform> transformation2 = new osg::MatrixTransform;
    transformation2->setMatrix(osg::Matrix::translate(25.0f, 0.0f, 0.0f));
    transformation2->addChild(model.get());

    osg::ref_ptr<osg::PositionAttitudeTransform> transformation3 = new osg::PositionAttitudeTransform;
    transformation3->setPosition(osg::Vec3(25.0f, 25.0f, 0.0f));
    transformation3->setAttitude(
        osg::Quat(3.14f, osg::X_AXIS,
            0.0f, osg::Y_AXIS,
            0.0f, osg::Z_AXIS
        ));
    //transformation2->setAttribute(osg::Matrix::translate(25.0f, 25.0f, 0.0f));
    transformation3->addChild(model.get());

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(transformation1.get());
    root->addChild(transformation2.get());
    root->addChild(transformation3.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    viewer.addEventHandler(new osgViewer::StatsHandler());
    viewer.addEventHandler(new osgViewer::WindowSizeHandler());
    viewer.addEventHandler(new osgGA::StateSetManipulator(
        viewer.getCamera()->getOrCreateStateSet()
    ));
    return viewer.run();
}
