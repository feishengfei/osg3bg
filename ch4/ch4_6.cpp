#include <glut.h>
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
        osg::Vec3 min(-size_, -size_, -size_);
        osg::Vec3 max( size_,  size_,  size_);
        return osg::BoundingBox(min, max);
    }

    virtual void drawImplementation(const osg::RenderInfo& renderInfo) const
    {
        //glDisable(GL_CULL_FACE);
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
