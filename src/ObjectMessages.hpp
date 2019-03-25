#ifndef SEMPR_ROCK_OBJECT_MESSAGES_HPP_
#define SEMPR_ROCK_OBJECT_MESSAGES_HPP_

#include <string>
#include <map>
#include <vector>
#include <utility>

#include <base/Pose.hpp>
#include <base/Eigen.hpp>

/**
    This file introduces messages that are used to communicate with the environment representation
    through ROCK.
    TODO: should this also be done in the orogen-component?
*/

namespace sempr_rock {

    /**
        Just a struct with basic object informations.
        TODO: Henning will implement the MARS side of things --> provide id, name, pose, bbox
        I'll wait for the message type he implements. :)
    */
    // struct ObjectInfo
    // {
    //     /// a unique id of the object
    //     std::string id;
    //
    //     /**
    //         The object type as an integer. The environment representation keeps a mapping between
    //         URIs and integer ids (to be able to use vision_msgs/Detection3D in a ROS setting --
    //         lets at least try to follow one consistent path here).
    //     */
    //     int type;
    //
    //
    // };

    /**
        While a SPARQL-Query is simply a string, the response is structured. E.g.
            SELECT * WHERE { ?a rdf:type ?b . }
        could result in:
            - (a: obj1), (b: type1)
            - (a: obj1), (b: type2)
            - (a: obj2), (b: type3)
            - [...]
        So we have a list of matches, where each match is a mapping of the used variable names in
        the query to their values.
        --> vector<map<string, string>>
        But orogen does not support maps. So we need to implement something our own.
    */


    // orogon refuses to process std::pair<std::string, std::string>
    struct KVPair
    {
        std::string key;
        std::string value;
    };

    struct KVMap
    {
        std::vector<KVPair> pairs;
        void toMap(std::map<std::string, std::string>& map) const;
        void fromMap(const std::map<std::string, std::string>& map);
    };

    struct SPARQLResult
    {        // typedef std::map<std::string, std::string> Result;
        std::vector<KVMap> results;
    };


    /**
        The ObjectAssertion represents a semantic annotation that is bound to an object. This is
        used by the environment representation to add additional properties to object instances:
        Given an id, a key and a value (all as strings), it will add a triple:
            (<sempr:object_id> <sempr:key> value)
        Where value will be inserted verbatim to allow you to reference literals as well as
        resources. If you want to add a property with a different namespace, e.g. rdf:type etc,
        use the baseURI. It will be used for the key only, so setting the baseURI to
        "http://foo.bar/" will result in (<sempr:object_id> <http://foo.bar/key> value).
    */
    struct ObjectAssertion
    {
        std::string objectId;
        std::string baseURI;
        std::string key;
        std::string value;
    };


    /**
        This struct is used to communicate plain triples between components. It can e.g. be used
        to allow the input of triples to be stored in a central place of the environment
        representation.

        It is assumed that the subject, predicate and object variables are valid resources or
        literals.
    */
    struct Triple
    {
        std::string subject_;
        std::string predicate_;
        std::string object_; // "object" clashes with keyword "Object" -- wtf...
    };


    /**
        Used for visualization purposes, to be published by the sempr environment representation.
        Represents an object with an id, a type and a pose.
    */
    struct SpatialObject
    {
        std::string id;
        std::string type;
        base::Vector3d position;
        base::Quaterniond orientation;
    };

} /* sempr */


#endif /* end of include guard: SEMPR_ROCK_OBJECT_MESSAGES_HPP_ */
