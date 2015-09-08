#include <osg/Camera>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>

class FindTextureVisitor : public osg::NodeVisitor
{
public:
    FindTextureVisitor(osg::Texture* tex)
        : texture_(tex)
    {
    }

    virtual void apply(osg::Node& node)
    {
        replaceTexure(node.getStateSet());
        traverse(node);
    }

    virtual void apply(osg::Geode& geode)
    {
        replaceTexure(geode.getStateSet());
        for (unsigned int i = 0; i < geode.getNumDrawables(); ++i)
        {
            replaceTexure(geode.getDrawable(i)->getStateSet());
        }
        traverse(geode);
    }

    void replaceTexure(osg::StateSet* ss)
    {
        if (ss)
        {
            osg::Texture* oldTexture = dynamic_cast<osg::Texture*>(
                ss->getTextureAttribute(0, osg::StateAttribute::TEXTURE));
            if (oldTexture)
            {
                ss->setTextureAttribute(0, texture_.get());
            }
        }
    }

protected:
    osg::ref_ptr<osg::Texture> texture_;
};

int main(
    int /*argc*/,
    char** /*argv*/)
{
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("lz.osg");
    osg::ref_ptr<osg::Node> sub_model = osgDB::readNodeFile("glider.osg");

    int tex_width = 1024;
    int tex_height = 1024;
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setTextureSize(tex_width, tex_height);
    texture->setInternalFormat(GL_RGBA);
    texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
    texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);

    FindTextureVisitor ftv(texture.get());
    if (model.valid())
    {
        model->accept(ftv);
    }

    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setViewport(0, 0, tex_width, tex_height);
    camera->setClearColor(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera->setRenderOrder(osg::Camera::PRE_RENDER);
    camera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
    camera->attach(osg::Camera::COLOR_BUFFER, texture.get());
    camera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
    camera->addChild(sub_model);

    osgViewer::Viewer viewer;
    viewer.setSceneData(model.get());
    viewer.setCameraManipulator(new osgGA::TrackballManipulator);

    float delta = 0.1f;
    float bias = 0.0f;
    osg::Vec3 eye(0.0f, -5.0f, 5.0f);

    while (!viewer.done())
    {
        if (bias < -1.0f)
        {
            delta = 0.1f;
        }
        else if (bias > 1.0f)
        {
            delta = -0.1f;
        }
        bias += delta;

        camera->setViewMatrixAsLookAt(
            eye,
            osg::Vec3(),
            osg::Vec3(bias, 1.0f, 1.0f));

        viewer.frame();
    }

    return 0;
}
