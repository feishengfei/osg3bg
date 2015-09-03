#include <istream>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

class InfoVisitor : public osg::NodeVisitor
{
public:
    InfoVisitor()
        : level_(0)
    {
        setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);
    }

    std::string spaces() const
    {
        return std::string(level_ * 2, ' ');
    }

    virtual void apply(osg::Node& node)
    {
        std::cout
            << spaces()
            << node.libraryName()
            << "::"
            << node.className()
            << std::endl;

        level_++;
        traverse(node);
        level_--;
    }

    virtual void apply(osg::Geode& geode)
    {
        std::cout
            << spaces()
            << geode.libraryName()
            << "::"
            << geode.className()
            << std::endl;

        level_++;
        for (unsigned int i = 0; i < geode.getNumDrawables(); ++i)
        {
            osg::Drawable* drawable = geode.getDrawable(i);
            std::cout
                << spaces()
                << drawable->libraryName()
                << "::"
                << drawable->className()
                << std::endl;
        }

        traverse(geode);
        level_--;
    }

protected:
    unsigned int level_;
};

int main(
    int argc,
    char** argv)
{
    osg::ArgumentParser arguments(&argc, argv);
    osg::ref_ptr<osg::Node> root = osgDB::readNodeFiles(arguments);
    if (!root)
    {
        OSG_FATAL
            << arguments.getApplicationName()
            << ": No data loaded."
            << std::endl;
    }

    InfoVisitor infoVisitor;
    root->accept(infoVisitor);

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
