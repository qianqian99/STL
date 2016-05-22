#ifndef _FUNCTIONAL_H_
#define _FUNCTIONAL_H_
#include <iostream>
namespace hgg
{
    template <typename _AT, typename _RT>
    struct unary_funtion
    {
        typedef _AT argument_type;
        typedef _RT result_type;
    };
    template <typename _FAT, typename _SAT, typename _RT>
    struct binary_function
    {
        typedef _FAT first_argument_type;
        typedef _SAT second_argument_type;
        typedef _RT result_type;
    };
/////////////////////////////////////////////////////////
    template <typename Type>
    class print_elem : public unary_funtion<Type, void>
    {
        public:
            void operator()(const Type &elem) const
            {
                std::cout << elem << " ";
            }
    };
/////////////////////////////////////////////////////////
/*judge condition*/
    template <typename Type>
    class greater : public binary_function<Type, Type, bool>
    {
        public:
            bool operator()(const Type &left, const Type &right) const
            {
                return left > right;
            }
    };
    template <typename Type>
    class less : public binary_function<Type, Type, bool>
    {
        public:
            bool operator()(const Type &left, const Type &right) const
            {
                return left < right;
            }
    };
    template <typename Type>
    class equal_to: public binary_function<Type, Type, bool>
    {
        public:
            bool operator()(const Type &left, const Type &right) const
            {
                return left == right;
            }
    };
    template <typename Type>
    class not_equal_to: public binary_function<Type, Type, bool>
    {
        public:
            bool operator()(const Type &left, const Type &right) const
            {
                return left != right;
            }
    };
////////////////////////////////////////////////////////////////////
/*binder*/
    template <typename _BFUN>
    class binder2nd : public unary_funtion<typename _BFUN::first_argument_type, typename _BFUN::result_type>
    {
        private:
            typename _BFUN::second_argument_type value;
            _BFUN fun;
        public:
            binder2nd(const _BFUN &f, const typename _BFUN::second_argument_type &val) 
                :fun(f), value(val){}
            typename _BFUN::result_type operator()(const typename _BFUN::first_argument_type &val) const
            {
                return fun(val, value);
            }
    };
    template <typename _BFUN>
    binder2nd<_BFUN> bind2nd(const _BFUN &fun, 
            const typename _BFUN::second_argument_type &value)
    {
        return binder2nd<_BFUN>(fun, value);
    }
    template <typename _BFUN>
    class binder1st : public unary_funtion<typename _BFUN::second_argument_type, typename _BFUN::result_type>
    {
        private:
            typename _BFUN::first_argument_type value;
            _BFUN fun;
        public:
            binder1st(const typename _BFUN::first_argument_type &val, const _BFUN &f) 
                :fun(f), value(val){}
            typename _BFUN::result_type operator()(const typename _BFUN::second_argument_type &val) const
            {
                return fun(value, val);
            }
    };
    template <typename _BFUN>
    binder1st<_BFUN> bind1st(const typename _BFUN::first_argument_type &value, const _BFUN &fun)
    {
        return binder1st<_BFUN>(value, fun);
    }
///////////////////////////////////////////////////////////////////////
/*negate*/
    template <typename _UFUN>
    class unary_negate : public unary_funtion<typename _UFUN::argument_type, typename _UFUN::result_type>
    {
        private:
            _UFUN fun;
        public:
            typedef typename _UFUN::result_type result_type;
            typedef typename _UFUN::argument_type argument_type;
            result_type operator()(const argument_type &val) const
            {
                return !fun(val);
            }
            unary_negate(_UFUN const &f) : fun(f){}
    };
    template <typename _UFUN>
    unary_negate<_UFUN> not1(_UFUN const &fun)
    {
        return unary_negate<_UFUN>(fun);
    }
    template <typename _BFUN>
    class binary_negate 
    : public binary_function<typename _BFUN::first_argument_type,
                             typename _BFUN::second_argument_type,
                             typename _BFUN::result_type>
    {
        private:
            _BFUN fun;
        public:
            typedef typename _BFUN::first_argument_type first_argument_type;
            typedef typename _BFUN::second_argument_type second_argument_type;
            typedef typename _BFUN::result_type result_type;
            result_type operator()(first_argument_type const &left, 
                                   second_argument_type const &right) const
            {
                return !fun(left, right);
            }
            binary_negate(_BFUN const &f) : fun(f){}
    };
    template <typename _BFUN>
    binary_negate<_BFUN> not2(_BFUN const &fun)
    {
        return binary_negate<_BFUN>(fun);
    }
}
#endif
