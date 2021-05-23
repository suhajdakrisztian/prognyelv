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

template <class TYPE, class PREDICATE, 
          class MSET_COMP_FST = std::less<TYPE>, class MSET_COMP_SND = std::less<TYPE> >

class multisets_predicate_view
{
  private:

    std::multiset<TYPE, MSET_COMP_FST>* _original_address_first_mset;
    std::multiset<TYPE, MSET_COMP_SND>* _original_address_second_mset;

    std::multiset<TYPE, MSET_COMP_FST> _original_values_first_mset;
    std::multiset<TYPE, MSET_COMP_SND> _original_values_second_mset;

    std::multiset<TYPE, MSET_COMP_FST> _valid_elements;
    std::multiset<TYPE, MSET_COMP_SND> _invalid_elements;

    PREDICATE _predicate;

  public:

    multisets_predicate_view(std::multiset<TYPE, MSET_COMP_FST>& first_input_mset,
                             std::multiset<TYPE, MSET_COMP_SND>& second_input_mset)
    {
      _original_address_first_mset = &first_input_mset;
      _original_address_second_mset = &second_input_mset;


      std::copy(first_input_mset.begin(), first_input_mset.end(), 
                std::inserter(_original_values_first_mset, 
                              _original_values_first_mset.begin()) );


      std::copy_if(first_input_mset.begin(), first_input_mset.end(), 
                   std::inserter(_valid_elements, _valid_elements.begin()), 
                   _predicate );

      std::copy_if(first_input_mset.begin(), first_input_mset.end(), 
                   std::inserter(_invalid_elements, _invalid_elements.begin()),
                   std::not1(_predicate) );


      std::copy(second_input_mset.begin(), second_input_mset.end(),
                std::inserter(_original_values_second_mset, 
                              _original_values_second_mset.begin()) );

      std::copy_if(second_input_mset.begin(), second_input_mset.end(),
                   std::inserter(_valid_elements, _valid_elements.begin()),
                   _predicate );

      std::copy_if(second_input_mset.begin(), second_input_mset.end(),
                   std::inserter(_invalid_elements, _invalid_elements.begin()),
                   std::not1(_predicate) );



      first_input_mset.clear();
      second_input_mset.clear();

      std::copy(_valid_elements.begin(), _valid_elements.end(),
                std::inserter(first_input_mset, first_input_mset.begin()));

      std::copy(_invalid_elements.begin(), _invalid_elements.end(),
                std::inserter(second_input_mset, second_input_mset.begin()));
    }

    multisets_predicate_view(std::multiset<TYPE, MSET_COMP_FST>& first_input_mset,
                             std::multiset<TYPE, MSET_COMP_SND>& second_input_mset, PREDICATE p) : _predicate(p)
    {
      _original_address_first_mset = &first_input_mset;
      _original_address_second_mset = &second_input_mset;


      std::copy(first_input_mset.begin(), first_input_mset.end(), 
                std::inserter(_original_values_first_mset, 
                              _original_values_first_mset.begin()) );


      std::copy_if(first_input_mset.begin(), first_input_mset.end(), 
                   std::inserter(_valid_elements, _valid_elements.begin()), 
                   _predicate );

      std::copy_if(first_input_mset.begin(), first_input_mset.end(), 
                   std::inserter(_invalid_elements, _invalid_elements.begin()),
                   std::not1(_predicate) );



      std::copy(second_input_mset.begin(), second_input_mset.end(),
                std::inserter(_original_values_second_mset, 
                              _original_values_second_mset.begin()) );

      std::copy_if(second_input_mset.begin(), second_input_mset.end(),
                   std::inserter(_valid_elements, _valid_elements.begin()),
                   _predicate );

      std::copy_if(second_input_mset.begin(), second_input_mset.end(),
                   std::inserter(_invalid_elements, _invalid_elements.begin()),
                   std::not1(_predicate) );



      first_input_mset.clear();
      second_input_mset.clear();

      std::copy(_valid_elements.begin(), _valid_elements.end(),
                std::inserter(first_input_mset, first_input_mset.begin()));

      std::copy(_invalid_elements.begin(), _invalid_elements.end(),
                std::inserter(second_input_mset, second_input_mset.begin()));
    }

    ~multisets_predicate_view()
    {
      *_original_address_first_mset = _original_values_first_mset;
      *_original_address_second_mset = _original_values_second_mset;
    }

    int size() const
    {
      return _valid_elements.size() + _invalid_elements.size();
    }

    int count(TYPE element_to_count) const
    {
    return _predicate(element_to_count) ? std::count(_valid_elements.begin(), _valid_elements.end(), element_to_count):
                                          std::count(_invalid_elements.begin(), _invalid_elements.end(), element_to_count);
    }
};


#endif