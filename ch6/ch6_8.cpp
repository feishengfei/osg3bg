#include <osg/LineWidth>
#include <osg/Program>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main(
    int /*argc*/,
    char** /*argv*/)
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(1.0f, 1.0f, 1.0f));
    vertices->push_back(osg::Vec3(2.0f, 1.0f,-1.0f));
    vertices->push_back(osg::Vec3(3.0f, 0.0f, 0.0f));

    osg::ref_ptr<osg::Geometry> controlPoints = new osg::Geometry;
    controlPoints->setVertexArray(vertices.get());
    controlPoints->addPrimitiveSet(
        new osg::DrawArrays(GL_LINES_ADJACENCY_EXT, 0, 4));

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(controlPoints.get());

    int segments = 10;

    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(osgDB::readShaderFile("ch6/ch6_8.vert"));
    program->addShader(osgDB::readShaderFile("ch6/ch6_8.geom"));
    program->setParameter(GL_GEOMETRY_VERTICES_OUT_EXT,
        segments + 1);
    program->setParameter(GL_GEOMETRY_INPUT_TYPE_EXT,
        GL_LINES_ADJACENCY_EXT);
    program->setParameter(GL_GEOMETRY_OUTPUT_TYPE_EXT,
        GL_LINE_STRIP);

    osg::ref_ptr<osg::LineWidth> lineWidth = new osg::LineWidth;
    lineWidth->setWidth(2.0f);

    osg::StateSet* stateset = geode->getOrCreateStateSet();
    stateset->setAttributeAndModes(program.get());
    stateset->setAttribute(lineWidth.get());
    stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    stateset->addUniform(new osg::Uniform("segments", segments));

    osgViewer::Viewer viewer;
    viewer.setSceneData(geode.get());
    return viewer.run();
}
