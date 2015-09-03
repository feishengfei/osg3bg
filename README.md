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

Depth first traversal
    event
    update
    cull
    draw

Reference frame
    relative
    absolute

OSG uses row-major matrix.

osg::Node
osg::Group

osg::Transform
osg::MatrixTransform
osg::PositionAttitudeTransform

osg::Switch
osg::Simplifier

osg::LOD
osg::ProxyNode
osg::PagedLOD
osg::DatabasePager

6. Creating Realistic Rendering Effects

OpenGL state machine
    attributes
    modes

osg::StateSet
    Non-texture
        setAttribute()
        setMode()
        setAttributeAndModes()
    Texture
        setTextureAttribute()
        setTextureMode()
        setTextureAttributeAndModes()

7. Viewing the World

Object Space (right-handed)
    Modeling Transform
World Space (right-handed)
    View Transform
Eye Space
    Projection Transform
Clip Space
    Perspective Divide
Normalized Device Space (left-handed)
    View and Depth Range Transform
Window Space (left-handed)

osg::Camera
    Matrix and viewport
        setViewMatrix()
        setViewMatrixAsLookAt()
        setProjectionMatrix()
        setProjectionMatrixAsFrustum()
        setProjectionMatrixAsOrtho()
        setProjectionMatrixAsOrtho2D()
        setProjectionMatrixAsPerspective()
        setViewport()
    Clear
        setClearMask()
        setClearColor()
        setClearDepth()
        setClearStensil()
        setClearAccum()
    Context
    Buffer
        color
        depth
        texture
    Other
        setRenderOrder()

osgViewer::Viewer
    run()
        manipulate camera
        modify graphics context
        render frame
    realize()
        initialize graphics context
        initialize resources
        initialize threads

OSG_WINDOW
setUpViewInWindow()
setUpViewOnSingleScreen()
setUpViewFor3dSphericalDisplay()

osgViewer::CompositeViewer

osg::DisplaySettings
    instance()
    setDoubleBuffer()
    setDepthBuffer()
    setMinimumNumAlphaBits()
    setNumMultiSamples()
    stereo mode
osg::GraphicsContext

8. Animating Scene Objects
9. Interacting with Outside Elements

osg::GraphicsContext::createGraphicsContext()
osg::GraphicsContext::Traits

10. Saving and Loading Files
11. Developing Visual Components
12. Improving Rendering Efficiency
