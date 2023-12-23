#ifndef __M_EDGE_HPP__
#define __M_EDGE_HPP__

#include "macros.hpp"
#include <set>
#include <iostream>

BASIC_NAMESPACE_BEGIN


template <typename _T>
class Edge;
template <typename _T>
class RevEdge;

template <typename _T>
class Edge
{
private:
    _T* _to;
    RevEdge<_T>* _rev;
    inline void _access();
    Edge( _T* __to );
public:
    static Edge<_T> generateTemp( _T* __to );
    _T* to();
    RevEdge<_T>* rev();
    inline void deprecate();
    inline bool isValid() const;
    void setTo( _T* __to );

    Edge<_T>& operator=( _T* __to );
    bool operator==( const _T* __to );

    Edge();
    Edge( _T* __from, _T* __to );
    Edge( _T* __to, RevEdge<_T>* __reverse );
    virtual ~Edge();
};

template <typename _T>
class RevEdge
{
private:
    _T* _to;
    Edge<_T>* _ori;
    inline void _access();
    RevEdge( _T* __to );
public:
    static RevEdge<_T> generateTemp( _T* __to );
    _T* to();
    Edge<_T>* ori();
    inline void deprecate();
    inline bool isValid() const;
    void setTo( _T* __to );

    RevEdge<_T>& operator=( _T* __to );
    bool operator==( const _T* __to );

    RevEdge();
    RevEdge( _T* __from, _T* __to );
    RevEdge( _T* __to, Edge<_T>* __origin );
    virtual ~RevEdge();
};

BASIC_NAMESPACE_END

#endif // __EDGE_HPP__}
