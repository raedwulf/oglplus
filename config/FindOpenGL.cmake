#  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
include(FindOpenGL)
unset(OPENGL_INCLUDE_DIRS)
set(OPENGL_FOUND false)
#
# try to find GL3/gl3.h
find_path(
	OPENGL_GL3_H_DIR GL3/gl3.h
	PATHS ${HEADER_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
# if that didn't work try the system directories
if((NOT OPENGL_GL3_H_DIR) OR (NOT EXISTS ${OPENGL_GL3_H_DIR}))
	find_path(OPENGL_GL3_H_DIR GL3/gl3.h)
endif()
if(NOT EXISTS ${OPENGL_GL3_H_DIR})
	find_path(OPENGL_GL3_H_DIR gl3.h
		PATHS /System/Library/Frameworks/OpenGL.framework/Versions/A/Headers
	)
endif()
# if found append it to the include directories
if((OPENGL_GL3_H_DIR) AND (EXISTS ${OPENGL_GL3_H_DIR}))
	set(OPENGL_INCLUDE_DIRS ${OPENGL_INCLUDE_DIRS} ${OPENGL_GL3_H_DIR})
	set(OPENGL_FOUND true)
endif()
#
#
# try to find GL/glcorearb.h
find_path(
	OPENGL_GLCOREARB_H_DIR GL/glcorearb.h
	PATHS ${HEADER_SEARCH_PATHS}
	NO_DEFAULT_PATH
)
# if that didn't work try the system directories
if((NOT OPENGL_GLCOREARB_H_DIR) OR (NOT EXISTS ${OPENGL_GLCOREARB_H_DIR}))
	find_path(OPENGL_GLCOREARB_H_DIR GL/glcorearb.h)
endif()
#
if((OPENGL_GLCOREARB_H_DIR) AND (EXISTS ${OPENGL_GLCOREARB_H_DIR}))
	set(OPENGL_INCLUDE_DIRS ${OPENGL_INCLUDE_DIRS} ${OPENGL_GLCOREARB_H_DIR})
	set(OPENGL_FOUND true)
endif()
