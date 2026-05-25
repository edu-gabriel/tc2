#ifndef __RangeTree_h
#define __RangeTree_h

//mudei esse caminho
#include "include/Array.h"

#include "PointTraits.h"

#include <functional>
#include <numeric>

namespace tcii::cg
{ // begin namespace tcii::cg

namespace rtree
{ // begin namespace rtree

    using index_t = unsigned;
    using IndexArray = Array<index_t>;

    template <size_t D, typename P>
    inline auto _x(const P& p)
    {
        if constexpr (std::is_arithmetic_v<P>)
        {
            static_assert(D == 1);
            return p;
        }
        else
            return p[D - 1];
    }

    template <typename A>
    using PointFunc = std::function<bool(const A&, size_t)>;

    template <size_t D, typename P, typename A> class BBST;

    template <typename P, typename A>
    class BBST<1, P, A>
    {
        public:
            using Bounds = typename PointTraits<P>::Bounds;
            using PointFunc = rtree::PointFunc<A>;

            void build(const A& points)
            {
                
            }
 
            //não sei dizer o que difere essa query da outra, talvez nada
            size_t query(const A& points, const Bounds& bounds, PointFunc f) const
            {
                // insert your code here
                return 0;
            }
    }; // BBST
   
    template <size_t D, typename P, typename A>
    class BBST
    {
        private:
            using real = typename P::value_type;
            using AssociatedTree = BBST<D - 1, P, A>;

            struct Node
            {
                float splitValue{};
                Node* left{};
                Node* right{};

                AssociatedTree* atree{};

                float minValue{}, maxValue{};
                int first{}, counter{};
            }; // Node

            Node* _root{};
            IndexArray _indices;

        public:
            using Bounds = typename PointTraits<P>::Bounds;
            using PointFunc = rtree::PointFunc<A>;

            ~BBST()
            {
                //delete _root->left;
                //delete _root->right;
                //delete _root->atree;
                delete _root;
            }

            Node* buildTree(const A& points, int start, int end)
            {
                if(start > end) return nullptr;
                //printf("build [%d, %d]\n", start, end);

                Node* nn = new Node{};

                int middle = start + (end - start)/2;

                auto split = _x<D>(points[_indices[middle]]);
                nn->splitValue = split;
                //printf("middle=%d split=%f\n", middle, split);


                int first = middle;
                while (first > start && std::abs(_x<D>(points[_indices[first-1]]) - split) < 1e-6f)
                {
                    --first;
                }

                int last = middle;
                while (last < end && std::abs(_x<D>(points[_indices[last+1]]) - split) < 1e-6f)
                {
                    ++last;
                }

                nn->first = _indices[first];
                nn->counter = last - first+1;
                //printf("duplicates: first=%d last=%d count=%d\n", first, last, nn->counter);

                //não descomenta saporra
                //nn->atree = new AssociatedTree{};
                
                nn->left = buildTree(points, start, first-1);
                nn->right = buildTree(points, last+1, end);

                nn->minValue = _x<D>(points[_indices[start]]);
                nn->maxValue = _x<D>(points[_indices[end]]);

                return nn;
            }

            void build(const A& points)
            {
                assert(!_root);

                unsigned sz = points.size();

                _indices = IndexArray(sz);
                for (unsigned i = 0; i < sz; ++i) _indices[i] = i;

                std::stable_sort(_indices.begin(), _indices.end(), [&](size_t a, size_t b){
                return _x<D>(points[a]) < _x<D>(points[b]);
                });

                _root = buildTree(points, 0, sz-1);
            }

            //PointFunc foi descrito como um filtro pros pontos
            //o functor seria o Compare pra usar lower_bound e upper_bound?
            size_t query(const A& points, const Bounds& bounds, PointFunc f) const
            {
                // insert your code here
                return 0;
            }
    }; // BBST
} // end namespace rtree

    template <typename P, typename A>
    class RangeTree
    {
        public:
            constexpr static auto D = point_dim_v<P>;

            using Bounds = typename PointTraits<P>::Bounds;
            using PointFunc = rtree::PointFunc<A>;

            RangeTree(const A& points):
                _points{points}
            {
                // do nothing
            }

            auto& points() const
            {
                return _points;
            }

            void build()
            {
                _mainTree.build(_points);
            }

            auto query(const Bounds& bounds, PointFunc f) const
            {
                return _mainTree.query(_points, bounds, f);
            }

        private:
            const A& _points;
            rtree::BBST<D, P, A> _mainTree;
    }; // RangeTree
} // end namespace tcii::cg

#endif // __RangeTree_h
