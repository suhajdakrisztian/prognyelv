// A vizsgafeladatot (egy lehetséges
// megoldással együtt) csatoltan küldöm: 2 multiset predikátum szerinti
// szétválogatása nézetként az előző hetihez hasonló módon. Most a predikátum
// megjelenik konstruktor paraméterként is, hogy valamilyen értéket meg
// lehessen adni a predikátum funktornak. Tetszőleges predikátummal rendezett
// multiset-ekkel is működjön a nézet.

#include <iostream>
#include <set>
#include "msetsview.h"
#include <string>
#include <algorithm>
#include "msetsview.h"
#include <functional>

class unary_less: public std::unary_function<int, bool>
{

  int i;

public:

  unary_less( int s ): i ( s ) { }

  bool operator()( int x ) const
  {
    return x < i;
  }

};


class starts_with: public std::unary_function<std::string, bool>
{

  char ch;

public:

  starts_with( char c ): ch( c ) { }

  bool operator()( const std::string& s ) const
  {
    return s[ 0 ] == ch;
  }

};


struct is_good_language: std::unary_function<std::string, bool>
{

  bool operator()( const std::string& s ) const
  {
    return "C++" == s || "C" == s;
  }

};


struct string_size_less
{

  bool operator()( const std::string& lhs,
                   const std::string& rhs ) const
  {
    return lhs.size() < rhs.size();
  }

};

const int max = 1000;

bool check()
{
  std::multiset<int> mia;
  std::multiset<int> mib;

  for( int i = 0; i < max; ++i )
  {
    if ( 0 == i % 2 )
    {
      mia.insert( i );
    }
    else
    {
      mib.insert( i );
    }
  }

  std::multiset<std::string> msa;
  msa.insert( "Ada" );
  msa.insert( "C++" );
  msa.insert( "Cobol" );
  std::multiset<std::string> msb;
  msb.insert( "C++" );
  msb.insert( "C" );
  msb.insert( "Brainfuck" );

  bool c = ( 1 == mia.size() );
  
  if ( !c )
  {
    multisets_predicate_view<int, unary_less> vi( mia, mib, unary_less( 1 ) );
    multisets_predicate_view<std::string, starts_with> vs( msa, msb, starts_with( 'C' ) );

    if ( 1 == mia.size() && 1 == msa.count( "C" ) && 2 == msa.count( "C++" ) && 2 == msb.size() )
    {
      c = ( 1 == mib.count( max / 2 ) );
    }

  }
  if ( !c || 3 != msa.size() || 1 != msa.count( "C++" ) || max / 2 != mia.size() )
    return false;

/*
  if ( c )
  {
    multisets_predicate_view<std::string, is_good_language> vs( msa, msb );
    multisets_predicate_view<int, unary_less> vi( mia, mib, unary_less( 2 ) );

    if ( max != vi.size() || 1 != vs.count( "Brainfuck" ) || 2 != vs.count( "C++" ) ||
         6 != vs.size() || 1 != vi.count( 2 ) )
      return false;
  } else
    return false;

  std::multiset<std::string> a;
  std::multiset<std::string, string_size_less> b;

  a.insert( "C++" );
  a.insert( "Cobol" );
  b.insert( "Fortran" );
  b.insert( "Prolog" );

  std::multiset<int, std::greater<int> > s;
  std::multiset<int> t;
  s.insert( 6 );
  t.insert( 1 );

  if ( c )
  {
    multisets_predicate_view<std::string, is_good_language, std::less<std::string>, string_size_less> vs( a, b );

    multisets_predicate_view<int, unary_less, std::greater<int> > vi( s, t, unary_less( 4 ) );

    return 3 == b.size() && 0 == a.count( "Cobol" ) && 1 == b.count( "Haskell" ) && 1 == s.count( 1 );
  }
  */
  return false;
}

int main()
{
  std::cout
    << "Your solution is " << (check() ? "" : "not ")
    << "ready for submission.\n";
}
