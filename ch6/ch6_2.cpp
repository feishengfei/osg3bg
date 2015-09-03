#include <osg/MatrixTransform>
#include <osg/PolygonMode>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main(
    int /*argc*/,
    char** /*argv*/)
{
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("glider.osg");

    osg::ref_ptr<osg::MatrixTransform> transformation1 = new osg::MatrixTransform;
    transformation1->setMatrix(osg::Matrix::translate(-0.5f, 0.0f, 0.0f));
    transformation1->addChild(model.get());
    transformation1->getOrCreateStateSet()->setMode(GL_LIGHTING,
        osg::StateAttribute::OFF);

    osg::ref_ptr<osg::MatrixTransform> transformation2 = new osg::MatrixTransform;
    transformation2->setMatrix(osg::Matrix::translate(0.5f, 0.0f, 0.0f));
    transformation2->addChild(model.get());
    transformation2->getOrCreateStateSet()->setMode(GL_LIGHTING,
        osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(transformation1.get());
    root->addChild(transformation2.get());
    root->getOrCreateStateSet()->setMode(GL_LIGHTING,
        osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
