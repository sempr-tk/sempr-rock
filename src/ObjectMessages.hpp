#ifndef SEMPR_ROCK_OBJECT_MESSAGES_HPP_
#define SEMPR_ROCK_OBJECT_MESSAGES_HPP_

#include <string>
#include <map>
#include <vector>
#include <utility>

#include <base/Pose.hpp>

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
            (<object_id> <sempr:key> value)
        Where value will be inserted verbatim to allow you to reference literals as well as
        resources.
    */
    struct ObjectAssertion
    {
        std::string objectId;
        std::string key;
        std::string value;
    };

} /* sempr */


#endif /* end of include guard: SEMPR_ROCK_OBJECT_MESSAGES_HPP_ */
