OpenSceneGraph 3.0 Beginner's Guide
Rui Wang; Xuelei Qian
Packt Publishing
2010

1. The Journey into OpenSceneGraph

Retained (Deferred) vs Immediate rendering mode

Scene Graph
Root node
Group node
Child node
Leaf node

No directed cycle
No orphan node

1998 Don Burns
1999 Robert Osfield
2005 1.0
2007 2.0
2011 3.0

Core libraries
    OpenThreads
    osg
    osgDB
    osgUtil
NodeKits
    osgAnimation
    osgFX
    osgGA
    osgManipulator
    osgParticle
    osgShadow
    osgSim
    osgTerrain
    osgText
    osgViewer
    osgVolumn
    osgWidget
    osgQt

2. Compilation and Installation of OpenSceneGraph

osgversion
osgconv
osgviewer
    W wireframe
    T texture
    L lighting
    F full-screen
    S statistics

Release
    stable: even minor version number
    un-stable: odd minor version number

Common environment variables
    OSG_FILE_PATH
    OSG_NOTIFY_LEVEL
    OSG_ROOT

3. Creating Your First OSG Program

osg::Geode - geometry node - leaf
    osg::Drawable
        osg::ShapeDrawable (inefficient)
        osg::Geometry

osgUtil::Simplifier
osgUtil::SmoothingVisitor
osgUtil::TangentSpaceGenerator
osgUtil::Tessellator
osgUtil::TriStripVisitor

osg::Drawable::AttributeFunctor
osg::Drawable::ConstAttributeFunctor
osg::PrimitiveFunctor
osg::PrimitiveIndexFunctor

osg::Drawable
    computeBound()
    drawImplementation()
    setUseDisplayList()

4. Building Geometry Models
5. Managing Scene Graph
6. Creating Realistic Rendering Effects
7. Viewing the World
8. Animating Scene Objects
9. Interacting with Outside Elements
10. Saving and Loading Files
11. Developing Visual Components
12. Improving Rendering Efficiency
