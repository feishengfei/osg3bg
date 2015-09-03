#include <GL/glut.h>
#include <osg/Geode>
#include <osg/Geometry>
#include <osgViewer/Viewer>

class TeapotDrawable : public osg::Drawable
{
public:
    TeapotDrawable(
        float size = 1.0f)
            : size_(size)
    {
    }
    TeapotDrawable(
        const TeapotDrawable& copy,
        const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY)
            : osg::Drawable(copy, copyop)
            , size_(copy.size_)
    {
    }
    META_Object(osg, TeapotDrawable);

    virtual osg::BoundingBox computeBoundingBox() const
    {
        const float size = size_ * 2;
        osg::Vec3 min(-size, -size, -size);
        osg::Vec3 max( size,  size,  size);
        return osg::BoundingBox(min, max);
    }

    virtual void drawImplementation(osg::RenderInfo& /*renderInfo*/) const
    {
        //glFrontFace(GL_CW);
        glutSolidTeapot(size_);
        //glFrontFace(GL_CCW);
    }

protected:
    float size_;
};

int main(
    int /*argc*/,
    char** /*argv*/)
{
    osg::ref_ptr<osg::Geode> root = new osg::Geode;
    root->addDrawable(new TeapotDrawable(1.0f));

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
