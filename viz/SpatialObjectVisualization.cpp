#include <iostream>
#include "SpatialObjectVisualization.hpp"

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osgText/Text>
#include <osg/Material>
#include <osgText/Text3D>

using namespace vizkit3d;


SpatialObjectVisualization::SpatialObjectVisualization()
{
}

SpatialObjectVisualization::~SpatialObjectVisualization()
{
}

osg::ref_ptr<osg::Node> SpatialObjectVisualization::createMainNode()
{
    auto group = new osg::Group();
    return group;
}

void SpatialObjectVisualization::updateMainNode ( osg::Node* node )
{
    static size_t count = 0;
    std::cout << "updateMainNode, " << ++count << std::endl;

    auto group = static_cast<osg::Group*>(node);

    for (auto& e : objectData_)
    {
        auto& node = objectNodes_[e.first];
        if (!node) 
        {
            // create a new node
            node = createVizNode(e.second);
            node->setName(e.first);
        }
        else
        {
            // update nodes position
            auto t = e.second.position;
            auto r = e.second.orientation;
            node->setPosition({t.x(), t.y(), t.z()});
            node->setAttitude({r.x(), r.y(), r.z(), r.w()});
        }

        if (!group->containsNode(node)) group->addChild(node);
    }

    // remove nodes representing objects which are no longer present
    std::vector<osg::ref_ptr<osg::Node>> toRemove;
    size_t numChildren = group->getNumChildren();
    for (size_t i = 0; i < numChildren; i++)
    {
        auto child = group->getChild(i);
        if (objectData_.find(child->getName()) == objectData_.end())
        {
            toRemove.push_back(child);
        }
    }

    for (auto node : toRemove)
    {
        group->removeChild(node);
    }
}

void SpatialObjectVisualization::updateDataIntern(sempr_rock::SpatialObject const& value)
{
    std::cout << "got new sample data" << std::endl;
    std::cout << "id: " << value.id << std::endl;

    if (value.mod == sempr_rock::Modification::ADD)
        objectData_[value.id] = value;
    else if (value.mod == sempr_rock::Modification::REMOVE)
        objectData_.erase(value.id);
}


void SpatialObjectVisualization::setColor(const osg::Vec4d& color, osg::Geode* geode) const
{
    osg::Material* material = new osg::Material();
    material->setDiffuse(osg::Material::FRONT,  osg::Vec4(0.1, 0.1, 0.1, 1.0));
    material->setSpecular(osg::Material::FRONT, osg::Vec4(0.6, 0.6, 0.6, 1.0));
    material->setAmbient(osg::Material::FRONT,  osg::Vec4(0.1, 0.1, 0.1, 1.0));
    material->setEmission(osg::Material::FRONT, color);
    material->setShininess(osg::Material::FRONT, 10.0);

    geode->getOrCreateStateSet()->setAttribute(material);
}


osg::ref_ptr<osg::PositionAttitudeTransform> SpatialObjectVisualization::createVizNode(const sempr_rock::SpatialObject& object) const
{
    osg::ref_ptr<osg::PositionAttitudeTransform> group = new osg::PositionAttitudeTransform();

    auto& t = object.position;
    auto& r = object.orientation;
    group->setPosition({t.x(), t.y(), t.z()});
    group->setAttitude({r.x(), r.y(), r.z(), r.w()});

    std::cout << "createVizNode" << std::endl
        << t.matrix().transpose() << std::endl
        << r.x() << "," << r.y() << "," << r.z() << "," << r.w() << std::endl;

    const float size = 0.5;
    // X
    osg::ref_ptr<osg::Geode> c1g = new osg::Geode();
    osg::ref_ptr<osg::Cylinder> c1 = new osg::Cylinder(osg::Vec3f(size/2., 0, 0), size/40., size);
    c1->setRotation(osg::Quat(M_PI/2., osg::Vec3d(0, 1, 0)));
    osg::ref_ptr<osg::ShapeDrawable> c1d = new osg::ShapeDrawable(c1);
    c1g->addDrawable(c1d);
    setColor(osg::Vec4d(1., 0., 0., 1.), c1g);
    group->addChild(c1g);

    // Y
    osg::ref_ptr<osg::Geode> c2g = new osg::Geode();
    osg::ref_ptr<osg::Cylinder> c2 = new osg::Cylinder(osg::Vec3f(0, size/2., 0), size/40., size);
    c2->setRotation(osg::Quat(M_PI/2., osg::Vec3d(1, 0, 0)));
    osg::ref_ptr<osg::ShapeDrawable> c2d = new osg::ShapeDrawable(c2);
    c2g->addDrawable(c2d);
    setColor(osg::Vec4d(0., 1., 0., 1.), c2g);
    group->addChild(c2g);
    
    // z
    osg::ref_ptr<osg::Geode> c3g = new osg::Geode();
    osg::ref_ptr<osg::Cylinder> c3 = new osg::Cylinder(osg::Vec3f(0, 0, size/2.), size/40., size);
    osg::ref_ptr<osg::ShapeDrawable> c3d = new osg::ShapeDrawable(c3);
    c3g->addDrawable(c3d);
    setColor(osg::Vec4d(0., 0., 1., 1.), c3g);
    group->addChild(c3g);

    // text (id)
    osg::ref_ptr<osgText::Text> text = new osgText::Text();
    text->setText(object.id + "\n(" + object.type + ")");
    text->setCharacterSize(0.1);
    text->setAxisAlignment(osgText::Text::AxisAlignment::SCREEN);
    text->setColor({1., 1., 1., 1.});

    osg::ref_ptr<osg::Geode> textGeode = new osg::Geode();
    textGeode->addDrawable(text);
    group->addChild(textGeode);

    return group;
}

void SpatialObjectVisualization::clear()
{
    objectData_.clear();
}


//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(SpatialObjectVisualization)

