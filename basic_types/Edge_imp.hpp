#pragma once
#ifndef __EDGE_IMP_HPP__
#define __EDGE_IMP_HPP__

#include "Edge.hpp"

BASIC_NAMESPACE_BEGIN

template<typename _T>
inline bool Edge<_T>::isValid() const
{
    return this->_to != nullptr && this->_rev != nullptr;
}
template<typename _T>
inline void Edge<_T>::setTo( _T* __to )
{
    this->_to = __to;
}
template<typename _T>
inline void Edge<_T>::_access()
{
    if (!this->isValid())
    {
        std::cerr << "Error: Invalid access to a non-exist RevEdge\n";
    }
}
template<typename _T>
Edge<_T>::Edge( _T* __to )
    : _to( __to )
    , _rev( nullptr )
{}
template<typename _T>
Edge<_T> Edge<_T>::generateTemp( _T* __to )
{
    return Edge<_T>( __to );
}
template<typename _T>
_T* Edge<_T>::to()
{
    if (this->_to == nullptr)
    {
        std::cerr << "Error: Invalid access to \"to\" pointer\n";
    }
    return this->_to;
}
template <typename _T>
RevEdge<_T>* Edge<_T>::rev()
{
    if (this->_rev == nullptr)
    {
        std::cerr << "Error: Invalid access to \"rev\" pointer\n";
    }
    return _rev;
}
template<typename _T>
void Edge<_T>::deprecate()
{
    this->_to = nullptr;
}

template<typename _T>
Edge<_T>& Edge<_T>::operator=( _T* __to )
{
    this->_to = __to;
    return *this;
}
template<typename _T>
bool Edge<_T>::operator==( const _T* __to )
{
    return this->_to == __to;
}

template<typename _T>
Edge<_T>::Edge()
    : _to( nullptr )
    , _rev( nullptr )
{}
template <typename _T>
Edge<_T>::Edge( _T* __from, _T* __to )
    : _to( __to )
    , _rev( new RevEdge<_T>( __from, this ) )
{}
template<typename _T>
Edge<_T>::Edge( _T* __to, RevEdge<_T>* __rev )
    : _to( __to )
    , _rev( __rev )
{}
template <typename _T>
Edge<_T>::~Edge()
{
    this->_to = nullptr;
    this->_rev = nullptr;
}


/*
 ** RevEdge **
*/
template<typename _T>
RevEdge<_T>::RevEdge()
    : _to( nullptr )
    , _ori( nullptr )
{}
template<typename _T>
RevEdge<_T>::RevEdge( _T* __from, _T* __to )
    : _to( __to )
    , _ori( new Edge<_T>( __from, this ) )
{}
template <typename _T>
RevEdge<_T>::RevEdge( _T* __to, Edge<_T>* __ori )
    : _to( __to )
    , _ori( __ori )
{}
template<typename _T>
RevEdge<_T>::~RevEdge()
{
    this->_to = nullptr;
    this->_ori = nullptr;
}

template<typename _T>
inline void RevEdge<_T>::_access()
{
    if (!this->isValid())
    {
        std::cerr << "Error: Invalid access to a non-exist RevEdge\n";
    }
}
template<typename _T>
RevEdge<_T>::RevEdge( _T* __to )
    : _to( __to )
    , _ori( nullptr )
{}
template<typename _T>
inline bool RevEdge<_T>::isValid() const
{
    return this->_to != nullptr && this->_ori != nullptr;
}

template<typename _T>
inline void RevEdge<_T>::setTo( _T* __to )
{
    _to = __to;
}

template<typename _T>
RevEdge<_T> RevEdge<_T>::generateTemp( _T* __to )
{
    return RevEdge<_T>( __to );
}

template<typename _T>
_T* RevEdge<_T>::to()
{
    if (this->_to == nullptr)
    {
        std::cerr << "Error: Invalid access to \"to\" pointer\n";
    }
    return this->_to;
}
template <typename _T>
Edge<_T>* RevEdge<_T>::ori()
{
    if (this->_ori == nullptr)
    {
        std::cerr << "Error: Invalid access to \"ori\" pointer\n";
    }
    return this->_ori;
}
template<typename _T>
void RevEdge<_T>::deprecate()
{
    _to = nullptr;
}


template<typename _T>
RevEdge<_T>& RevEdge<_T>::operator=( _T* __to )
{
    this->_to = __to;
    return *this;
}

template<typename _T>
bool RevEdge<_T>::operator==( const _T* __to )
{
    return this->_to == __to;
}


BASIC_NAMESPACE_END


#endif