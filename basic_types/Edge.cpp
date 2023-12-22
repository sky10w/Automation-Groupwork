#include "Edge.hpp"

BASIC_NAMESPACE_BEGIN


template<typename _T>
inline bool Edge<_T>::isValid() const
{
    return this->_to != nullptr && this->rev != nullptr;
}
template<typename _T>
inline void Edge<_T>::_access()
{
    if (!this->isValid())
    {
        throw std::runtime_error( "Invalid access to an non-exist Edge" );
    }
}
template<typename _T>
_T* Edge<_T>::to()
{
    this->_acess();
    return this->_to;
}
template <typename _T>
RevEdge<_T>* Edge<_T>::rev() const
{
    this->_access();
    return _rev;
}
template<typename _T>
void Edge<_T>::deprecate() const
{
    this->_to == nullptr;
}

template<typename _T>
Edge<_T> Edge<_T>::operator=( _T* __to )
{
    return this->_to = __to;
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
    , _rev( new Edge<_T>( __from, this ) )
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
        throw std::runtime_error( "Invalid access to a non-exist RevEdge" );
    }
}
template<typename _T>
inline bool RevEdge<_T>::isValid() const
{
    return this->_to != nullptr && this->_ori != nullptr;
}

template<typename _T>
_T* RevEdge<_T>::to()
{
    this->_access();
    return this->_to;
}
template <typename _T>
Edge<_T>* RevEdge<_T>::ori() const
{
    this->_access();
    return this->_ori;
}
template<typename _T>
void RevEdge<_T>::deprecate() const
{
    _to == nullptr;
}


template<typename _T>
RevEdge<_T> RevEdge<_T>::operator=( _T* __to )
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

