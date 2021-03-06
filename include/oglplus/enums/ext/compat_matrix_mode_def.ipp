/*
 *  .file oglplus/enums/ext/compat_matrix_mode_def.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/compat_matrix_mode.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_PROJECTION
# if OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined Projection
#  pragma push_macro("Projection")
#  undef Projection
   OGLPLUS_ENUM_CLASS_VALUE(Projection, GL_PROJECTION)
#  pragma pop_macro("Projection")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Projection, GL_PROJECTION)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_MODELVIEW
# if OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined Modelview
#  pragma push_macro("Modelview")
#  undef Modelview
   OGLPLUS_ENUM_CLASS_VALUE(Modelview, GL_MODELVIEW)
#  pragma pop_macro("Modelview")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Modelview, GL_MODELVIEW)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

