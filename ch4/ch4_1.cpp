#include <osg/Shape>
#include <osgDB/ReadFile>
#include <osg/ShapeDrawable>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>

int main(
    int /*argc*/,
    char** /*argv*/)
{
    osg::ref_ptr<osg::ShapeDrawable> shape1 = new osg::ShapeDrawable;
    shape1->setShape(new osg::Box(osg::Vec3(-3.0f, 0.0f, 0.0f),
        2.0f, 2.0f, 1.0f));
    shape1->setColor(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));

    osg::ref_ptr<osg::ShapeDrawable> shape2 = new osg::ShapeDrawable;
    shape2->setShape(new osg::Sphere(osg::Vec3(3.0f, 0.0f, 0.0f),
        1.0f));
    shape2->setColor(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));

    osg::ref_ptr<osg::ShapeDrawable> shape3 = new osg::ShapeDrawable;
    shape3->setShape(new osg::Cone(osg::Vec3(0.0f, 0.0f, 0.0f),
        1.0f, 1.0f));
    shape3->setColor(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));

    osg::ref_ptr<osg::ShapeDrawable> shape4 = new osg::ShapeDrawable;
    shape4->setShape(new osg::Capsule(osg::Vec3(3.0f, 3.0f, 0.0f),
        1.0f, 1.0f));
    shape4->setColor(osg::Vec4(0.0f, 1.0f, 1.0f, 1.0f));

    osg::ref_ptr<osg::ShapeDrawable> shape5 = new osg::ShapeDrawable;
    shape5->setShape(new osg::Cylinder(osg::Vec3(-3.0f, 3.0f, 0.0f),
        1.0f, 1.0f));
    shape5->setColor(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));

    osg::ref_ptr<osg::Geode> root = new osg::Geode;
    root->addDrawable(shape1.get());
    root->addDrawable(shape2.get());
    root->addDrawable(shape3.get());
    root->addDrawable(shape4.get());
    root->addDrawable(shape5.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    viewer.addEventHandler(new osgViewer::StatsHandler());
    viewer.addEventHandler(new osgViewer::WindowSizeHandler());
    viewer.addEventHandler(new osgGA::StateSetManipulator(
        viewer.getCamera()->getOrCreateStateSet()
    )); 
    return viewer.run();
}
