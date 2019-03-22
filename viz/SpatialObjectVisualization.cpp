#include <iostream>
#include "SpatialObjectVisualization.hpp"

using namespace vizkit3d;

struct SpatialObjectVisualization::Data {
    // Copy of the value given to updateDataIntern.
    //
    // Making a copy is required because of how OSG works
    sempr_rock::SpatialObject data;
};


SpatialObjectVisualization::SpatialObjectVisualization()
    : p(new Data)
{
}

SpatialObjectVisualization::~SpatialObjectVisualization()
{
    delete p;
}

osg::ref_ptr<osg::Node> SpatialObjectVisualization::createMainNode()
{
    // Geode is a common node used for vizkit3d plugins. It allows to display
    // "arbitrary" geometries
    return new osg::Geode();
}

void SpatialObjectVisualization::updateMainNode ( osg::Node* node )
{
    osg::Geode* geode = static_cast<osg::Geode*>(node);
    // Update the main node using the data in p->data
}

void SpatialObjectVisualization::updateDataIntern(sempr_rock::SpatialObject const& value)
{
    p->data = value;
    std::cout << "got new sample data" << std::endl;
}

//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(SpatialObjectVisualization)

