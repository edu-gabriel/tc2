//esse arquivo tá aqui pra servir de base pros outros, não tem nada implementado aqui
//o include manda size_t pros outros arquivos, bom saber kk

#ifndef __PointTraits_h
#define __PointTraits_h

//<stddef.h> -> adiciona alguns tipos fundamentais e macros (size_t, byte, NULL etc.)
#include <cstddef>

namespace tcii::cg
{ // begin namespace tcii::cg

//PointTraits tá implementada na Main.cpp
//não me pergunte como ela tá sendo acessada antes disso
//ah, pq é um template kk
template <typename P> struct PointTraits;

template <typename P> 
inline constexpr size_t point_dim_v = PointTraits<P>::dim;

} // end namesapce tcii::cg

#endif // __PointTraits_h