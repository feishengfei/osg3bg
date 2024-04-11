#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/ref_ptr>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>

#include "utils.hpp"

int main(int argc, char** argv)
{
    // 创建场景根节点
    osg::ref_ptr<osg::Group> root = new osg::Group;

    // 创建正方形的顶点坐标
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back(osg::Vec3(-1.0f, 0, -1.0f)); // 左下角
    vertices->push_back(osg::Vec3(1.0f, 0, -1.0f));  // 右下角
    vertices->push_back(osg::Vec3(1.0f, 0, 1.0f));   // 右上角
    vertices->push_back(osg::Vec3(-1.0f, 0, 1.0f));  // 左上角
                                                     //
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

    // 创建正方形的纹理坐标
    osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array;
    texcoords->push_back(osg::Vec2(0.0f, 0.0f)); // 左下角
    texcoords->push_back(osg::Vec2(1.0f, 0.0f)); // 右下角
    texcoords->push_back(osg::Vec2(1.0f, 1.0f)); // 右上角
    texcoords->push_back(osg::Vec2(0.0f, 1.0f)); // 左上角

    // 创建几何体
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setVertexArray(vertices);
    geom->setTexCoordArray(0, texcoords); // 设置纹理坐标数组
                                          //
    geom->setNormalArray(normals.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

    // 创建正方形的绘制指令
    osg::ref_ptr<osg::DrawElementsUInt> primitiveSet = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    primitiveSet->push_back(0); // 左下角
    primitiveSet->push_back(1); // 右下角
    primitiveSet->push_back(2); // 右上角
    primitiveSet->push_back(3); // 左上角
    geom->addPrimitiveSet(primitiveSet);

    // 加载纹理图像
    osg::ref_ptr<osg::Image> image = osgDB::readImageFile(find_accessible_file("resources/amd_gpu.jpg"));
    if (!image.valid())
    {
        OSG_NOTICE << "Failed to load texture image." << std::endl;
        return 1;
    }

    // 创建纹理对象并设置纹理图像
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setImage(image);

    // 创建几何体的状态集，添加纹理属性
    osg::ref_ptr<osg::StateSet> stateset = geom->getOrCreateStateSet();
    stateset->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);

    // 创建 Geode，并将几何体添加到 Geode 中
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geom);

    // 将 Geode 添加到场景根节点
    root->addChild(geode);

    // 创建查看器并设置场景数据
    osgViewer::Viewer viewer;
    viewer.setSceneData(root);
    viewer.addEventHandler(new osgViewer::StatsHandler());
    viewer.addEventHandler(new osgViewer::WindowSizeHandler());
    viewer.addEventHandler(new osgGA::StateSetManipulator(
        viewer.getCamera()->getOrCreateStateSet()
    )); 

    // 运行查看器
    return viewer.run();
}
