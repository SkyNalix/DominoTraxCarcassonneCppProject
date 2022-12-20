#ifndef BORD_HPP
#define BORD_HPP

#include<iostream>
using namespace std;

template <typename T> class Bord {
    public :
        T x;
        Bord<T>(T a);
};

template < typename T> Bord<T>::Bord(T a): x{a} {

}

#endif
