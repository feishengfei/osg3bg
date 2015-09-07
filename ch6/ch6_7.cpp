#include <osg/Program>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main(
    int /*argc*/,
    char** /*argv*/)
{
    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(osgDB::readShaderFile("ch6/ch6_7.vert"));
    program->addShader(osgDB::readShaderFile("ch6/ch6_7.frag"));

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("cow.osg");

    osg::StateSet* stateset = model->getOrCreateStateSet();
    stateset->setAttributeAndModes(program.get());
    stateset->addUniform(new osg::Uniform("color1",
        osg::Vec4(1.0f, 0.5f, 0.5f, 1.0f)));
    stateset->addUniform(new osg::Uniform("color2",
        osg::Vec4(0.5f, 0.2f, 0.2f, 1.0f)));
    stateset->addUniform(new osg::Uniform("color3",
        osg::Vec4(0.2f, 0.1f, 0.1f, 1.0f)));
    stateset->addUniform(new osg::Uniform("color4",
        osg::Vec4(0.1f, 0.05f, 0.05f, 1.0f)));

    osgViewer::Viewer viewer;
    viewer.setSceneData(model.get());
    return viewer.run();
}
