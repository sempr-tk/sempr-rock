#include "ObjectMessages.hpp"

namespace sempr_rock {

    void KVMap::fromMap(const std::map<std::string, std::string> &map)
    {
        this->pairs.clear();
        for (auto entry : map)
        {
            KVPair pair;
            pair.key = entry.first;
            pair.value = entry.second;
            this->pairs.push_back(pair);
        }
    }

    void KVMap::toMap(std::map<std::string, std::string> &map) const
    {
        map.clear();
        for (auto p : this->pairs)
        {
            map[p.key] = p.value;
        }
    }

} /* sempr_rock */
