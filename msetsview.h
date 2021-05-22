// A vizsgafeladatot (egy lehetséges
// megoldással együtt) csatoltan küldöm: 2 multiset predikátum szerinti
// szétválogatása nézetként az előző hetihez hasonló módon. Most a predikátum
// megjelenik konstruktor paraméterként is, hogy valamilyen értéket meg
// lehessen adni a predikátum funktornak. Tetszőleges predikátummal rendezett
// multiset-ekkel is működjön a nézet.

#ifndef MSETSVIEW__H
#define MSETSVIEW__H

#include <set>
#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>

template <class TYPE, class PREDICATE, class Comp = std::less<TYPE>, class Compp = std::less<TYPE>>
class multisets_predicate_view
{
  private:

    std::multiset<TYPE, Comp>* _original_elements_first;
    std::multiset<TYPE, Compp>* _original_elements_second;

    std::multiset<TYPE, Comp> _a;
    std::multiset<TYPE, Compp> _b;

    std::multiset<TYPE, Compp> _ta;
    std::multiset<TYPE, Compp> _tb;

    PREDICATE _predicate;

  public:

    multisets_predicate_view( std::multiset<TYPE, Comp>& m1, std::multiset<TYPE, Compp>& m2)
    {
      _original_elements_first = &m1;
      _original_elements_second = &m2;

      for (TYPE element : m1) {
        _a.insert(element);
        if ( !_predicate(element)) {
          _tb.insert(element);
        }
        else {
          _ta.insert(element);
        }
      }

      for (TYPE element : m2) {
        _b.insert(element);
        if (_predicate(element)) {
          _ta.insert(element);
        }
        else {
          _tb.insert(element);
        }
      }
      m1.clear();
      m2.clear();
      std::copy(_ta.begin(), _ta.end(), std::inserter(m1, m1.begin()));
      std::copy(_tb.begin(), _tb.end(), std::inserter(m2, m2.begin()));
    }

    multisets_predicate_view(std::multiset<TYPE, Comp>& m1, std::multiset<TYPE, Compp>& m2, PREDICATE p) : _predicate(p)
    {
      _original_elements_first = &m1;
      _original_elements_second = &m2;

      for (TYPE element : m1) {
        _a.insert(element);
        if ( !_predicate(element)) {
          _tb.insert(element);
        }
        else {
          _ta.insert(element);
        }
      }

      for (TYPE element : m2) {
        _b.insert(element);
        if (_predicate(element)) {
          _ta.insert(element);
        }
        else {
          _tb.insert(element);
        }
      }

      m1.clear();
      m2.clear();

      std::copy(_ta.begin(), _ta.end(), std::inserter(m1, m1.begin()));
      std::copy(_tb.begin(), _tb.end(), std::inserter(m2, m2.begin()));

    }
    ~multisets_predicate_view()
    {
      *_original_elements_first = _a;
      *_original_elements_second = _b;
    }

    int size()
    {
      return _ta.size() + _tb.size();
    }

    int count(TYPE k)
    {
    return _predicate(k) ? std::count(_ta.begin(), _ta.end(), k):
                           std::count(_tb.begin(), _tb.end(), k);
    }

};


#endif