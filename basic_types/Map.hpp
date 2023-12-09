#if !defined(__MAP_HPP__)
#define __MAP_HPP__

#include "macros.hpp"
#include "Edge.hpp"
#include <unordered_map>
#include <vector>

BASIC_NAMESPACE_BEGIN

class Map
{
private:
    std::unordered_map<id_t, Edge> _edgeList;

public:
    Map() = delete;
    Map(size_t __nodeNum);
    ~Map();
    void insertEdge(id_t __fromId, id_t __toId);
};

BASIC_NAMESPACE_END

#endif // __MAP_HPP__
