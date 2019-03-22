#ifndef sempr-rock_SpatialObjectVisualization_H
#define sempr-rock_SpatialObjectVisualization_H

#include <boost/noncopyable.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <osg/Geode>
#include <sempr/sempr-rock/src/ObjectMessages.hpp>

namespace vizkit3d
{
    class SpatialObjectVisualization
        : public vizkit3d::Vizkit3DPlugin<sempr_rock::SpatialObject>
        , boost::noncopyable
    {
    Q_OBJECT
    public:
        SpatialObjectVisualization();
        ~SpatialObjectVisualization();

    Q_INVOKABLE void updateData(sempr_rock::SpatialObject const &sample)
    {vizkit3d::Vizkit3DPlugin<sempr_rock::SpatialObject>::updateData(sample);}

    protected:
        virtual osg::ref_ptr<osg::Node> createMainNode();
        virtual void updateMainNode(osg::Node* node);
        virtual void updateDataIntern(sempr_rock::SpatialObject const& plan);
        
    private:
        struct Data;
        Data* p;
    };
}
#endif
