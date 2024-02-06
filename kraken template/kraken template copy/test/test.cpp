#include "test.hpp"


void KT::func() {}

void KT::subc::subc_func() {}


KT::chas chas(1);

void m() {
    chas.chas_func();

    KT::inn d;

}