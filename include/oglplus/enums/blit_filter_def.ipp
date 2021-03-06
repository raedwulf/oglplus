/*
 *  .file oglplus/enums/blit_filter_def.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/blit_filter.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_NEAREST
# if OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined Nearest
#  pragma push_macro("Nearest")
#  undef Nearest
   OGLPLUS_ENUM_CLASS_VALUE(Nearest, GL_NEAREST)
#  pragma pop_macro("Nearest")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Nearest, GL_NEAREST)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LINEAR
# if OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined Linear
#  pragma push_macro("Linear")
#  undef Linear
   OGLPLUS_ENUM_CLASS_VALUE(Linear, GL_LINEAR)
#  pragma pop_macro("Linear")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Linear, GL_LINEAR)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

