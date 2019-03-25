require 'vizkit'
Orocos.initialize

# This depends on sempr/orogen/sempr_types, which exports /sempr_rock/SpatialObject.
# Okay, only used for debug purposes, the widget does not need to know the typekit stuff
# for SpatialObject.
Orocos.load_typekit_for('/sempr_rock/SpatialObject')

view3d = Vizkit.vizkit3d_widget
view3d.show()

plugin = Vizkit.default_loader.SpatialObjectVisualization

data = Types::sempr_rock::SpatialObject.new
data.id = "obj1"
data.position = Eigen::Vector3.new(1, 0, 0)
data.orientation = Eigen::Quaternion.new(1, 0, 0, 0)

plugin.updateData(data)
data.id = "obj2"
data.position = Eigen::Vector3.new(-1, 0, 0)
data.orientation = Eigen::Quaternion.new(1, 0, 0, 1)

plugin.updateData(data)

Vizkit.exec()
