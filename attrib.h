#ifndef ATTRIB_H
#define ATTRIB_H 1

/* C2x/C23 or later? */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202000L
    #include <stddef.h>             /* nullptr_t */
#else
    #define nullptr (void *)0
    typedef void *nullptr_t;
#endif                          /* nullptr/nullptr_t */

/*
 * Some notes:
 * 1) All attributes that take an optional or variable number of arguments will
 *    have two versions; one of the form `attr`, and one of the form `attrex`. 
 *    The latter shall expect one or more arguments.
 * 2) The attributes that have no equivalent in GNU C shall be replaced with 
 *    nothing except for `__maybe_unused__`, which would expand to `unused`.
 *    GNU C doesn't have `__reproducible__` or `__unsequenced__`, yet one may 
 *    be interested in looking at `pure` - which is more relaxed than 
 *    `__reproducible__` - and `const` - which is more strict than
 *    `__unsequenced__`.
 *
 * References:
 *  https://en.cppreference.com/w/c/language/attributes
 *  https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html
 *  https://gcc.gnu.org/onlinedocs/gcc/Statement-Attributes.html
 *  https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html#index-common-variable-attribute
 *  https://gcc.gnu.org/onlinedocs/gcc/Common-Type-Attributes.html
 *  https://learn.microsoft.com/en-us/cpp/cpp/attributes?view=msvc-170#microsoft-specific-attribute://learn.microsoft.com/en-us/cpp/cpp/attributes?view=msvc-170#microsoft-specific-attributes
 */

#if defined(__has_c_attribute)
    /* Every standard attribute whose name is of form `attr` can be also 
     * spelled as __attr__ and its meaning is not changed. All attributes
     * are specified with leading pairs of underscores, to avoid that they
     * macro-expand in case that the user had a macro with the same name.
     */
    #if __has_c_attribute(__deprecated__)
    /* Since __deprecated__ and __no_discard__ takes an optional parameter,
     * we define two versions of them.
     */
        #define ATTRIB_DEPRECATED               [[__deprecated__]]
        #define ATTRIB_DEPRECATEDEX(reason)     [[__deprecated__(#reason]]
    #endif                          /* __deprecated__ */

    #if __has_c_attribute(__fallthrough__)
        #define ATTRIB_FALLTHROUGH              [[__fallthrough__]]
    #endif                          /* __fallthrough__ */

    #if __has_c_attribute(__nodiscard__)
        #define ATTRIB_NODISCARD                [[__nodiscard__]]
        #define ATTRIB_NODISCARDEX(reason)      [[__nodiscard__(#reason)]]
    #endif                          /* __nodiscard__ */

    #if __has_c_attribute(__maybe_unused__)
        #define ATTRIB_MAYBE_UNUSED		        [[__maybe_unused__]]
    #endif                          /* __maybe_unused__ */

    #if __has_c_attribute(__noreturn__)
        #define ATTRIB_NORETURN                 [[__noreturn__]]
    #endif                          /* __noreturn__ */

    #if __has_c_attribute(__maybe_unused__)
        #define ATTRIB_MAYBE_UNUSED		        [[__maybe_unused__]]
    #endif                          /* __maybe_unused__ */

    #if __has_c_attribute(__unsequenced__)
        #define ATTRIB_UNSEQUENCED              [[__unsequenced__]]
    #endif                          /* __unsequenced__ */

    #if __has_c_attribute(__reproducible__)
        #define ATTRIB_REPRODUCIBLE             [[__reproducible__]]
    #endif                          /* __reproducible__ */
#elif defined(__has_cpp_attribute)
    #if __has_cpp_attribute(__noreturn__)
        #define ATTRIB_NORETURN                 [[__noreturn__]]
        #endif                          /* __noreturn__ */

    #if __has_cpp_attribute(__carries_dependency__)
        #define ATTRIB_CARRIES_DEPENDENCY       [[__carries_dependency__]]
    #endif                          /* __carries_dependency__ */

    #if __has_cpp_attribute(__deprecated__)
        #define ATTRIB_DEPRECATED               [[__deprecated__]]
        #define ATTRIB_DEPRECATEDEX(reason)     [[__deprecated__(#reason)]]
    #endif                          /* __deprecated__ */

    #if __has_cpp_attribute(__fallthrough__)
        #define ATTRIB_FALLTHROUGH              [[__fallthrough__]]
    #endif                          /* __fallthrough__ */

    #if __has_cpp_attribute(__nodiscard__)
        #define ATTRIB_NODISCARD                [[__nodiscard__]]
        #define ATTRIB_NODISCARDEX(reason)      [[__nodiscard__(#reason)]]
    #endif                          /* __nodiscard__ */

    #if __has_cpp_attribute(__maybe_unused__)
        #define ATTRIB_MAYBE_UNUSED             [[__maybe_unused__]]
    #endif                          /* ____ */

    #if __has_cpp_attribute(__likely__)
        #define ATTRIB_LIKELY                   [[__likely__]]
    #endif                          /* __likely__ */

    #if __has_cpp_attribute(__unlikely__)
        #define ATTRIB_UNLIKELY                 [[__unlikely__]]
    #endif                          /* __unlikely__ */

    #if __has_cpp_attribute(__no_unique_address__)
        #define ATTRIB_NO_UNIQUE_ADDRESS        [[__no_unique_address__]]
    #endif                          /* __no_unique_address__ */

    #if __has_cpp_attribute(__assume__)
        #define ATTRIB_ASSUME(expr)             [[__assume(expr)__]]
    #endif                          /* __assume__ */

    #if __has_cpp_attribute(__optimize_for_synchronized__)
        #define ATTRIB_OPTIMIZE_FOR_SYNCHRONIZED    [[__optimize_for_synchronized__]]
    #endif                          /* __optimize_for_synchronized__ */
#elif defined(__GNUC__) || defined(__clang__) || defined(__INTEL_LLVM_COMPILER)
    /* GNU C doesn't have a __nodiscard__ attribute, but has warn_unused_result, 
     * but that doesn't take an optional argument, and raises a diagnostic message 
     * even after being casted to void, so we do not define it.
     * 
     * GNU C doesn't have maybe_unused, but has unused.
     */
    #define ATTRIB_MAYBE_UNUSED		        __attribute__((unused))
    #define ATTRIB_DEPRECATED               __attribute__((deprecated))
    #define ATTRIB_DEPRECATEDEX(reason)     __attribute__(deprecated(#reason))
    #define ATTRIB_FALLTHROUGH              __attribute__((fallthrough))
    #define ATTRIB_NODISCARD                /**/
    #define ATTRIB_NODISCARDEX(reason)      /**/
    #define ATTRIB_UNSEQUENCED              /**/
    #define ATTRIB_REPRODUCIBLE             /**/
    #define ATTRIB_NORETURN                 __attribute__((noreturn))
    #define ATTRIB_CARRIES_DEPENDENCY       /**/
    #define ATTRIB_MAYBE_UNUSED             /**/
    #define ATTRIB_LIKELY                   /**/
    #define ATTRIB_UNLIKELY                 /**/
    #define ATTRIB_NO_UNIQUE_ADDRESS        /**/
    #define ATTRIB_ASSUME(expr)             __attribute__((assume(expr)))
    #define ATTRIB_OPTIMIZE_FOR_SYNCHRONIZED /**/
#else
    #define ATTRIB_MAYBE_UNUSED             /**/
    #define ATTRIB_DEPRECATED               /**/
    #define ATTRIB_DEPRECATEDEX(reason)     /**/
    #define ATTRIB_FALLTHROUGH              /**/
    #define ATTRIB_NODISCARD                /**/
    #define ATTRIB_NODISCARDEX(reason)      /**/
    #define ATTRIB_UNSEQUENCED              /**/
    #define ATTRIB_REPRODUCIBLE             /**/
    #define ATTRIB_NORETURN                 /**/
    #define ATTRIB_CARRIES_DEPENDENCY       /**/
    #define ATTRIB_LIKELY                   /**/
    #define ATTRIB_UNLIKELY                 /**/
    #define ATTRIB_NO_UNIQUE_ADDRESS        /**/
    #define ATTRIB_ASSUME(expr)             /**/
    #define ATTRIB_OPTIMIZE_FOR_SYNCHRONIZED /**/
#endif                          /* defined(__has_c_attribute) */

#if !defined(ATTRIB_DEPRECATED)
    #define ATTRIB_DEPRECATED               /**/ 
    #define ATTRIB_DEPRECATEDEX(reason)     /**/ 
#endif                          /* __deprecated__ */

#if !defined(ATTRIB_FALLTHROUGH)
    #define ATTRIB_FALLTHROUGH              /**/ 
#endif                          /* __fallthrough__ */

#if !defined(ATTRIB_NODISCARD)
    #define ATTRIB_NODISCARD                /**/
    #define ATTRIB_NODISCARDEX(reason)      /**/
#endif                          /* __nodiscard__ */

#if !defined(ATTRIB_NORETURN)
    #define ATTRIB_NORETURN                 /**/
#endif

#if !defined(ATTRIB_UNSEQUENCED) 
    #define ATTRIB_UNSEQUENCED              /**/ 
#endif                          /* __unsequenced__ */

#if !defined(ATTRIB_REPRODUCIBLE)
    #define ATTRIB_REPRODUCIBLE             /**/
#endif                          /* __reproducible__ */

#if !defined(ATTRIB_MAYBE_UNUSED)
    #define ATTRIB_MAYBE_UNUSED		        /**/
#endif                          /* __maybe_unused__ */

#if !defined(ATTRIB_CARRIES_DEPENDENCY)       
    #define ATTRIB_CARRIES_DEPENDENCY       /**/
#endif                          /* __carries_dependency__ */

#if !defined(ATTRIB_LIKELY)
    #define ATTRIB_LIKELY                   /**/
#endif                          /* __likely__ */

#if !defined(ATTRIB_UNLIKE)
    #define ATTRIB_UNLIKELY                 /**/
#endif                          /* __unlikely__ */

#if !defined(ATTRIB_NO_UNIQUE_ADDRESS)
    #define ATTRIB_NO_UNIQUE_ADDRESS        /**/
#endif                          /* __no_unique_address__ */

#if !defined(ATTRIB_ASSUME)
    #define ATTRIB_ASSUME(expr)             /**/
#endif                          /* __assume__ */

#if !defined(ATTRIB_OPTIMIZE_FOR_SYNCHRONIZED)
    #define ATTRIB_OPTIMIZE_FOR_SYNCHRONIZED    /**/
#endif                          /* __optimize_for_synchronized__ */

#if defined(__clang__) || defined(__INTEL_LLVM_COMPILER)
    #define ATTRIB_MUSTTAIL                 [[clang::musttail]]
#else 
    #define ATTRIB_MUSTTAIL                 /**/
#endif

#if defined(__GNUC__) || defined(__clang__) || defined(__INTEL_LLVM_COMPILER)
    /* To indicate that an allocation function both satisfies the nonaliasing 
     * property and has a deallocator associated with it, both the plain form
     * ot the attribute and the one with the deallocator must be used.
     *
     * Note that this attribute is not accepted on inline functions.
     */
    #define ATTRIB_MALLOC                       __attribute__(malloc)
    #define ATTRIB_MALLOCEX(...)                __attribute__(malloc, malloc (__VA_ARGS__))
    #define ATTRIB_PRINTF_LIKE(n, m) 		    __attribute__((format(printf, n, m)))
    #define ATTRIB_FORMAT(func, n, m) 		    __attribute__((format(func, n, m)))
    #define ATTRIB_COLD                         __attribute__((cold))
    #define ATTRIB_CONST                        __attribute__((const))
    #define ATTRIB_HOT                          __attribute__((hot))
    #define ATTRIB_PURE                         __attribute__((pure))
    #define ATTRIB_NONNULL                      __attribute__((nonnull))
    #define ATTRIB_NONNULLEX(...)               __attribute__((nonnull(__VA_ARGS__)))
    #define ATTRIB_NULL_TERMINATED              __attribute__((null_terminated_string_arg))
    #define ATTRIB_NULL_TERMINATEDEX(...)       __attribute__((null_terminated_string_arg(__VA_ARGS__)))
    #define ATTRIB_UNAVAILABLE                  __attribute__((unavailable))
    #define ATTRIB_UNAVAILABLEEX(reason)        __attribute__((unavailable(#reason)))
    #define ATTRIB_UNUSED                       __attribute__((unused))
    #define ATTRIB_USED                         __attribute__((used))
    #define ATTRIB_WARN_UNUSED_RESULT           __attribute__((warn_unused_result))
    #define ATTRIB_RETURNS_NONNULL			    __attribute__((returns_nonnull))
    #define ATTRIB_ALWAYS_INLINE			    static inline __attribute__((always_inline))
    #define ATTRIB_NOINLINE				        __attribute__((noinline))
    #define ATTRIB_ALIGNED                      __attribute__((aligned))
    #define ATTRIB_ALIGNEDEX(alignment)         __attribute__((aligned(alignment)))
    #define ATTRIB_ALLOC_SIZE                   __attribute__((alloc_size))
    #define ATTRIB_ALLOC_SIZEEX(pos1, pos2)     __attribute__((alloc_size(pos1, pos2)))
    #define ATTRIB_COPY                         __attribute__((copy)) 
    #define ATTRIB_COPYEX(expr)                 __attribute__((copy(expr))) 
    #define ATTRIB_DESIGNATED_INIT              __attribute__((designated_init))
    #define ATTRIB_PACKED                       __attribute__((packed))
    #define ATTRIB_SCALAR_STORAGE_ORDER(endn)   __attribute__((#endn))
    #define ATTRIB_STRUB                        __attribute__((strub))  
    #define ATTRIB_VISIBILITY(visi_type)        __attribute__((visibility(#visi_type)))
    #define ATTRIB_WARN_IF_NOT_ALIGNED(align)   __attribute__((warn_if_not_aligned(align)))
    #define ATTRIB_ALIAS(target)                __attribute__((alias(#target)))
    #define ATTRIB_CLEANUP(func)                __attribute__((cleanup(func)))
    #define ATTRIB_NO_ICF                       __attribute__((no_icf))
    #define ATTRIB_NONSTRING                    __attribute__((nonstring))
#else
    #define ATTRIB_MALLOC                       /**/
    #define ATTRIB_MALLOCEX(...)                /**/
    #define ATTRIB_PRINTF_LIKE(n, m)            /**/
    #define ATTRIB_FORMAT(func, n, m)           /**/
    #define ATTRIB_COLD                         /**/
    #define ATTRIB_CONST                        /**/
    #define ATTRIB_HOT                          /**/
    #define ATTRIB_PURE                         /**/
    #define ATTRIB_NONNULL                      /**/
    #define ATTRIB_NONNULLEX(...)               /**/
    #define ATTRIB_NULL_TERMINATED              /**/
    #define ATTRIB_NULL_TERMINATEDEX(...)       /**/
    #define ATTRIB_UNAVAILABLE                  /**/
    #define ATTRIB_UNAVAILABLEEX(reason)        /**/
    #define ATTRIB_UNUSED                       /**/
    #define ATTRIB_USED                         /**/
    #define ATTRIB_WARN_UNUSED_RESULT           /**/
    #define ATTRIB_RETURNS_NONNULL              /**/
    #define ATTRIB_ALWAYS_INLINE                /**/
    #define ATTRIB_NOINLINE                     /**/
    #define ATTRIB_ALIGNED                      /**/
    #define ATTRIB_ALIGNEDEX(alignment)         /**/ 
    #define ATTRIB_ALLOC_SIZE                   /**/ 
    #define ATTRIB_ALLOC_SIZEEX(pos1, pos2)     /**/
    #define ATTRIB_COPY                         /**/ 
    #define ATTRIB_COPYEX(expr)                 /**/  
    #define ATTRIB_DESIGNATED_INIT              /**/
    #define ATTRIB_PACKED                       /**/ 
    #define ATTRIB_SCALAR_STORAGE_ORDER(endn)   /**/ 
    #define ATTRIB_STRUB                        /**/ 
    #define ATTRIB_VISIBILITY(visi_type)        /**/
    #define ATTRIB_WARN_IF_NOT_ALIGNED(align)   /**/
    #define ATTRIB_ALIAS(target)                /**/
    #define ATTRIB_CLEANUP(func)                /**/
    #define ATTRIB_NO_ICF                       /**/ 
    #define ATTRIB_NONSTRING                    /**/
#endif                          /* __GNUC__ || __clang__ || __INTEL_LLVM_COMPILER */

#if defined(_MSC_VER)
    #define ATTRIB_FLATTEN                      [[msvc::flatten]]
    #define ATTRIB_FORCEINLINE                  [[msvc::forceinline]]
    #define ATTRIB_FORCEINLINE_CALLS            [[msvc::forceinline_calls]]
    #define ATTRIB_INTRINSIC                    [[msvc::intrinsic]]

    #if !defined(ATTRIB_NOINLINE)
        #define ATTRIB_NOINLINE                     [[msvc::noinline]]
    #endif                          /* [[msvc::noinline]] */

    #define ATTRIB_NOINLINE_CALLS               [[msvc::noinline_calls]]
    #define ATTRIB_NO_TLS_GUARD                 [[msvc::no_tls_guard]]
#else
    #define ATTRIB_FLATTEN                      /**/
    #define ATTRIB_FORCEINLINE                  /**/
    #define ATTRIB_FORCEINLINE_CALLS            /**/
    #define ATTRIB_INTRINSIC                    /**/

    #if !defined(ATTRIB_NOINLINE)
        #define ATTRIB_NOINLINE                 /**/
    #endif

    #define ATTRIB_NOINLINE_CALLS               /**/
    #define ATTRIB_NO_TLS_GUARD                 /**/
#endif                          /* _MSC_VER */

/* This is how the Linux kernel defines these two macros, and we follow suit. */
#if defined(__GNUC__) || defined(__clang__) || defined(__INTEL_LLVM_COMPILER)
    #define likely(x)		__builtin_expect((!!(x)), 1)
    #define unlikely(x)		__builtin_expect((!!(x)), 0)
#else
    #define likely(x)		(!!(x))
    #define unlikely(x)		(!!(x))
#endif                          /* __GNUC__ || __clang__ */

#endif                          /* ATTRIB_H */
