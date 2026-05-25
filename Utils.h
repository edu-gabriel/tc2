#ifndef __Utils_h
#define __Utils_h

#include "PointTraits.h"
#include <random>

namespace tcii::cg
{ // begin namespace tcii::cg

//P: definição de um ponto
//A: conjunto de pontos

template <typename P, typename A>
class PointSource
{
public:
  //catando a dimensão em tempo de compilação
  constexpr static auto D = point_dim_v<P>;

  //esse value_type é literalmente um tipo
  //real pro trabalho seria um double ou float
  using real = typename P::value_type;
  //o prof usa o Bounds3.h pra isso aqui
  using Bounds = typename PointTraits<P>::Bounds;

  //prototipação da função random
  A random(size_t, const Bounds&) const;

}; // PointSource

//n: qtde de pontos a serem gerados
//bounds: limites

//implementação da função random
//se eu bem entendi, isso serve pra gerar um conjunto de pontos pra teste
//tá sendo usada na Main.cpp
template <typename P, typename A>
A PointSource<P, A>::random(size_t n, const Bounds& bounds) const
{
  using URD = std::uniform_real_distribution<real>;

  std::random_device rd;
  std::mt19937 gen(rd());
  URD dists[D];

  for (size_t d = 0; d < D; ++d)
    dists[d] = URD{bounds[0][d], bounds[1][d]};

  A points(n);

  for (size_t i = 0; i < n; ++i)
  {
    auto& p = points[i];

    for (size_t d = 0; d < D; ++d)
      p[d] = dists[d](gen);
  }
  return points;
}

} // end namesapce tcii::cg

#endif // __Utils_h
