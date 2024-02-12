#include <osg/Geode>
#include <osg/Geometry>
#include <osgUtil/SmoothingVisitor>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>

int main(
    int /*argc*/,
    char** /*argv*/)
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(5);
    (*vertices)[0].set( 0.0f, 0.0f, 1.0f);
    (*vertices)[1].set(-0.5f,-0.5f, 0.0f);
    (*vertices)[2].set( 0.5f,-0.5f, 0.0f);
    (*vertices)[3].set( 0.5f, 0.5f, 0.0f);
    (*vertices)[4].set(-0.5f, 0.5f, 0.0f);

    osg::ref_ptr<osg::DrawElementsUInt> indices =
        new osg::DrawElementsUInt(GL_TRIANGLES, 18);

    (*indices)[0] = 0;
    (*indices)[1] = 4;
    (*indices)[2] = 1;

    (*indices)[3] = 0;
    (*indices)[4] = 1;
    (*indices)[5] = 2;

    (*indices)[6] = 0;
    (*indices)[7] = 2;
    (*indices)[8] = 3;

    (*indices)[9] = 0;
    (*indices)[10] = 3;
    (*indices)[11] = 4;

    (*indices)[12] = 4;
    (*indices)[13] = 1;
    (*indices)[14] = 3;

    (*indices)[15] = 2;
    (*indices)[16] = 3;
    (*indices)[17] = 1;


    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;;
    geom->setVertexArray(vertices.get());
    geom->addPrimitiveSet(indices.get());
    osgUtil::SmoothingVisitor::smooth(*geom);

    osg::ref_ptr<osg::Geode> root = new osg::Geode;
    root->addDrawable(geom.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    viewer.addEventHandler(new osgViewer::StatsHandler());
    viewer.addEventHandler(new osgViewer::WindowSizeHandler());
    viewer.addEventHandler(new osgGA::StateSetManipulator(
        viewer.getCamera()->getOrCreateStateSet()
    )); 
    return viewer.run();
}
