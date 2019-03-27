#ifndef sempr_rock_SpatialObjectVisualization_H
#define sempr_rock_SpatialObjectVisualization_H

#include <boost/noncopyable.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <osg/Geode>
#include <osgText/Text3D>
#include <sempr_rock/ObjectMessages.hpp>

#include <unordered_map>
#include <iostream>
#include <vector>

namespace vizkit3d
{
    class SpatialObjectVisualization
        : public vizkit3d::Vizkit3DPlugin<sempr_rock::SpatialObject>,
          public vizkit3d::VizPluginAddType<std::vector<sempr_rock::SpatialObject>>
        , boost::noncopyable
    {
    Q_OBJECT
    public:
        SpatialObjectVisualization();
        ~SpatialObjectVisualization();

    Q_INVOKABLE void updateData(sempr_rock::SpatialObject const &sample)
    {
        vizkit3d::Vizkit3DPlugin<sempr_rock::SpatialObject>::updateData(sample);
    }

    Q_INVOKABLE void updateData(std::vector<sempr_rock::SpatialObject> const &sample)
    {
        vizkit3d::Vizkit3DPlugin<sempr_rock::SpatialObject>::updateData(sample);
    }

    /**
     * Remove all objects from the visualization.
     */
    Q_INVOKABLE void clear();

    protected:
        virtual osg::ref_ptr<osg::Node> createMainNode() override;
        virtual void updateMainNode(osg::Node* node) override;
        virtual void updateDataIntern(sempr_rock::SpatialObject const& sample) override;
        virtual void updateDataIntern(std::vector<sempr_rock::SpatialObject> const& sample) override;

        /**
         * Create a marker to represent an object: 3 axis + text
         * x red, y green, z blue
         */
        osg::ref_ptr<osg::PositionAttitudeTransform> createVizNode(const sempr_rock::SpatialObject& object) const;

        /**
         * Helper to set the color of a geode
         */
        void setColor(const osg::Vec4d& color, osg::Geode* geode) const;
        
    private:
        // The main node of this plugin. All objects are attached underneath it.
        osg::ref_ptr<osg::Node> groupNode_;

        // The "raw data" to visualize
        std::unordered_map<std::string, sempr_rock::SpatialObject> objectData_;
        // directly lookup the node of an object
        std::unordered_map<std::string, osg::ref_ptr<osg::PositionAttitudeTransform>> objectNodes_;

        osg::ref_ptr<osgText::Font> textFont_;
        osg::ref_ptr<osgText::Style> textStyle_;

    };
}
#endif
