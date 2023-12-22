#if !defined(__EDGE_HPP__)
#define __EDGE_HPP__

#include "macros.hpp"
#include <set>
#include <stdexcept>

BASIC_NAMESPACE_BEGIN


template <typename _T>
struct Edge;
template <typename _T>
struct RevEdge;

template <typename _T>
struct Edge
{
private:
    _T* _to;
    struct RevEdge<_T>* _rev;
    inline void _access();
public:
    _T* to();
    struct RevEdge<_T>* rev() const;
    void deprecate() const;
    inline bool isValid() const;

    Edge<_T> operator=( _T* __to );
    bool operator==( const _T* __to );

    Edge();
    Edge( _T* __from, _T* __to );
    Edge( _T* __to, RevEdge<_T>* __reverse );
    virtual ~Edge();
};

template <typename _T>
struct RevEdge
{
private:
    _T* _to;
    Edge<_T>* _ori;
    inline void _access();
public:
    _T* to();
    Edge<_T>* ori() const;
    void deprecate() const;
    inline bool isValid() const;

    RevEdge<_T> operator=( _T* __to );
    bool operator==( const _T* __to );

    RevEdge();
    RevEdge( _T* __from, _T* __to );
    RevEdge( _T* __to, Edge<_T>* __origin );
    virtual ~RevEdge();
};


BASIC_NAMESPACE_END

#endif // __EDGE_HPP__
