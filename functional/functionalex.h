#ifndef _FUNCTIONALEX_H_
#define _FUNCTIONALEX_H_
#include "functional.h"
namespace hgg
{
    template <typename _T, typename _R>
    class mem_fun_t : public unary_funtion<_T *, _R>
    {
        private:
            /* the mem data is a pointer of member funtion;*/
            _R (_T:: *pfun)(); 
        public:
            mem_fun_t(_R (_T:: *fun)()) : pfun(fun){}
            _R operator()(_T *pobj) const
            {
                /* maybe the fun() is not a const method*/
                return (pobj->*pfun)();
            }
    };
    /*const method way*/
    template <typename _T, typename _R>
    class const_mem_fun_t : public unary_funtion<_T *, _R>
    {
        private:
            _R (_T::*pfun)() const;
        public:
            const_mem_fun_t(_R (_T::*fun)() const) 
                : pfun(fun){}
            _R operator()(const _T *pobj) const
            {
                return (pobj->*pfun)();
            }
    };
    /*call from reference*/
    template <typename _T, typename _R>
    class mem_fun_ref_t : public unary_funtion<_T *, _R>
    {
        private:
            _R (_T::*pfun)();
        public:
            mem_fun_ref_t(_R (_T::*fun)())
                : pfun(fun){}
            _R operator()(_T &instance) const
            {
                /*notice the pro of  the diff operator*/
                return (instance.*pfun)();
            }
    };
    template <typename _T, typename _R>
    class const_mem_fun_ref_t : public unary_funtion<_T *, _R>
    {
        private:
            _R (_T::*pfun)() const;
        public:
            const_mem_fun_ref_t(_R (_T::*fun)() const) 
                : pfun(fun){}
            _R operator()(const _T &instance) const
            {
                return (instance.*pfun)();
            }
    };
//////////////////////////////////////////////////////////////////
    /*in this I only finish void argument fun, and the type argument is oposite*/
    template <typename _T, typename _R>
    inline mem_fun_t<_T, _R>
    mem_fun(_R (_T::*pfun)())
    {
        return mem_fun_t<_T, _R>(pfun);
    }
    template <typename _T, typename _R>
    inline const_mem_fun_t<_T, _R>
    mem_fun(_R (_T::*pfun)() const)
    {
        return const_mem_fun_t<_T, _R>(pfun);
    }
    template <typename _T, typename _R>
    inline const_mem_fun_ref_t<_T, _R>
    mem_fun_ref(_R (_T::*pfun)() const)
    {
        return const_mem_fun_ref_t<_T, _R>(pfun);
    }
    template <typename _T, typename _R>
    inline mem_fun_ref_t<_T, _R>
    mem_fun_ref(_R (_T::*pfun)() const)
    {
        return mem_fun_ref_t<_T, _R>(pfun);
    }
}
#endif
