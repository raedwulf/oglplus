/**
 *  @file oglplus/context/synchronization.hpp
 *  @brief Wrappers for synchronization operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_SYNCHRONIZATION_1201040722_HPP
#define OGLPLUS_CONTEXT_SYNCHRONIZATION_1201040722_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/memory_barrier.hpp>
#include <oglplus/bitfield.hpp>

namespace oglplus {
namespace context {

/// Wrapper for synchronization operations
/**
 *  @ingroup ogl_context
 */
class Synchronization
{
public:

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_2 || GL_ARB_shader_image_load_store
	/// Defines a barrier for memory transactions
	/**
	 *  example:
	 *  @code
	 *  Context gl;
	 *  gl.MemoryBarrier({MemoryBarrierBit::VertexAttribArray});
	 *  gl.MemoryBarrier({
	 *      MemoryBarrierBit::ElementArray,
	 *      MemoryBarrierBit::Uniform
	 *  });
	 *  gl.MemoryBarrier({
	 *      MemoryBarrierBit::TextureFetch,
	 *      MemoryBarrierBit::TextureUpdate
	 *  });
	 *  @endcode
	 *
	 *  @throws Error
	 *
	 *  @glvoereq{4,2,ARB,shader_image_load_store}
	 *  @glsymbols
	 *  @glfunref{MemoryBarrier}
	 */
	static void MemoryBarrier(Bitfield<MemoryBarrierBit> bits)
	{
		OGLPLUS_GLFUNC(MemoryBarrier)(GLbitfield(bits));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MemoryBarrier));
	}
#endif

	/// Indicate that all previous GL commands must finish in finite time
	static void Flush(void)
	{
		OGLPLUS_GLFUNC(Flush)();
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Flush));
	}

	/// Force all previous GL commands to complete before returning
	static void Finish(void)
	{
		OGLPLUS_GLFUNC(Finish)();
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Finish));
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
