/**
 *  @file oglplus/transform_feedback.hpp
 *  @brief TransformFeedback object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TRANSFORM_FEEDBACK_1107121519_HPP
#define OGLPLUS_TRANSFORM_FEEDBACK_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/object.hpp>
#include <oglplus/enumerations.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/auxiliary/binding_query.hpp>
#include <cassert>

namespace oglplus {

/// The mode used to capture the varying variables in TF
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(TransformFeedbackMode, GLenum)
#include <oglplus/enums/transform_feedback_mode.ipp>
OGLPLUS_ENUM_CLASS_END

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/transform_feedback_mode_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/transform_feedback_mode_range.ipp>
#endif


/// Transform feedback primitive modes
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(TransformFeedbackPrimitiveType, GLenum)
#include <oglplus/enums/transform_feedback_primitive_type.ipp>
OGLPLUS_ENUM_CLASS_END

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/transform_feedback_primitive_type_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/transform_feedback_primitive_type_range.ipp>
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_transform_feedback2

/// Transform feedback bind targets
OGLPLUS_ENUM_CLASS_BEGIN(TransformFeedbackTarget, GLenum)
#include <oglplus/enums/transform_feedback_target.ipp>
OGLPLUS_ENUM_CLASS_END

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/transform_feedback_target_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/transform_feedback_target_range.ipp>
#endif

/// Wrapper for fransform feedback operations
/** @note Do not use this class directly, use TransformFeedback instead.
 *
 *  @glvoereq{4,0,ARB,transform_feedback2}
 *  @glsymbols
 *  @glfunref{GenTransformFeedbacks}
 *  @glfunref{DeleteTransformFeedbacks}
 *  @glfunref{IsTransformFeedback}
 */
class TransformFeedbackOps
 : public Named
 , public BaseObject<true>
{
public:
	/// Transform feedback bind targets
	typedef TransformFeedbackTarget Target;
protected:
	static void _init(GLsizei count, GLuint* _name, std::true_type)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != nullptr);
		try{OGLPLUS_GLFUNC(GenTransformFeedbacks)(count, _name);}
		catch(...){ }
	}

	static void _init(GLsizei count, GLuint* _name, std::false_type)
	{
		assert(_name != nullptr);
		OGLPLUS_GLFUNC(GenTransformFeedbacks)(count, _name);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GenTransformFeedbacks));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		try{OGLPLUS_GLFUNC(DeleteTransformFeedbacks)(count, _name);}
		catch(...){ }
	}

	static GLboolean _is_x(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != 0);
		try{return OGLPLUS_GLFUNC(IsTransformFeedback)(_name);}
		catch(...){ }
		return GL_FALSE;
	}

#ifdef GL_TRANSFORM_FEEDBACK
	static ObjectType _object_type(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return ObjectType::TransformFeedback;
	}
#endif

	static void _bind(GLuint _name, Target target)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindTransformFeedback)(GLenum(target), _name);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindTransformFeedback));
	}

	friend class FriendOf<TransformFeedbackOps>;

	static GLenum _binding_query(Target target)
	{
		switch(GLenum(target))
		{
#include <oglplus/enums/transform_feedback_target_bq.ipp>
			default:;
		}
		return 0;
	}
	friend class BindingQuery<TransformFeedbackOps>;
public:

	/// Bind this transform feedback object
	/**
	 *  @glsymbols
	 *  @glfunref{BindTransformFeedback}
	 */
	void Bind(Target target = Target::TransformFeedback) const
	{
		_bind(_name, target);
	}

	/// Bind the default transform feedback object
	/**
	 *  @glsymbols
	 *  @glfunref{BindTransformFeedback}
	 */
	static void BindDefault(Target target = Target::TransformFeedback)
	{
		OGLPLUS_GLFUNC(BindTransformFeedback)(GLenum(target), 0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindTransformFeedback));
	}

	/// Begin the transform feedback mode
	/** Consider using an instance of Activator class for more robustness.
	 *  @throws Error
	 *
	 *  @see Activator
	 *  @see End
	 *
	 *  @glsymbols
	 *  @glfunref{BeginTransformFeedback}
	 */
	static void Begin(TransformFeedbackPrimitiveType mode)
	{
		OGLPLUS_GLFUNC(BeginTransformFeedback)(GLenum(mode));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BeginTransformFeedback));
	}

	/// End the transform feedback mode
	/** Consider using an instance of Activator class for more robustness.
	 *  @throws Error
	 *
	 *  @see Activator
	 *  @see Begin
	 *
	 *  @glsymbols
	 *  @glfunref{EndTransformFeedback}
	 */
	static void End(void)
	{
		OGLPLUS_GLFUNC(EndTransformFeedback)();
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(EndTransformFeedback));
	}

	/// Pause the transform feedback mode
	/** Consider using an instance of Pauser class for more robustness.
	 *  @throws Error
	 *
	 *  @see Pauser
	 *  @see Resume
	 *
	 *  @glsymbols
	 *  @glfunref{PauseTransformFeedback}
	 */
	static void Pause(void)
	{
		OGLPLUS_GLFUNC(PauseTransformFeedback)();
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(PauseTransformFeedback));
	}

	/// Resume the transform feedback mode
	/** Consider using an instance of Pauser class for more robustness.
	 *  @throws Error
	 *
	 *  @see Pauser
	 *  @see Pause
	 *
	 *  @glsymbols
	 *  @glfunref{ResumeTransformFeedback}
	 */
	static void Resume(void)
	{
		OGLPLUS_GLFUNC(ResumeTransformFeedback)();
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(ResumeTransformFeedback));
	}

	/// Class lifetime of which controls the (de)activation of TFB
	/** This class activates transform feedback mode when it is
	 *  constructed and deactivates it in destructor. It is a more
	 *  robust and preferred mode of transform feedback activation
	 *  and deactivation.
	 *
	 *  This class is non-copyable.
	 *
	 *  @glsymbols
	 *  @glfunref{BeginTransformFeedback}
	 *  @glfunref{EndTransformFeedback}
	 */
	class Activator
	{
	private:
		bool _active;
	public:
		/// Begins transform feedback
		/**
		 *  @glsymbols
		 *  @glfunref{BeginTransformFeedback}
		 */
		Activator(TransformFeedbackPrimitiveType mode)
		 : _active(true)
		{
			OGLPLUS_GLFUNC(BeginTransformFeedback)(GLenum(mode));
			OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BeginTransformFeedback));
		}

#if !OGLPLUS_NO_DELETED_FUNCTIONS
		/// Copying is disabled
		Activator(const Activator&) = delete;
#else
	private:
		Activator(const Activator&);
	public:
#endif

		Activator(Activator&& tmp)
		 : _active(tmp._active)
		{
			tmp._active = false;
		}

		void Finish(void)
		{
			if(_active)
			{
				OGLPLUS_GLFUNC(EndTransformFeedback)();
				OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(EndTransformFeedback));
				_active = false;
			}
		}

		/// Ends transform feedback
		/**
		 *  @glsymbols
		 *  @glfunref{EndTransformFeedback}
		 */
		~Activator(void)
		{
			try { Finish(); }
			catch(...){ }
		}
	};

	/// Class lifetime of which controls the pausing/resuming of TFB
	/** This class pauses active transform feedback when it is
	 *  constructed and resumes it in destructor. It is a more
	 *  robust and preferred mode of transform feedback activation
	 *  and deactivation.
	 *
	 *  This class is non-copyable.
	 *
	 *  @glsymbols
	 *  @glfunref{PauseTransformFeedback}
	 *  @glfunref{ResumeTransformFeedback}
	 */
	class Pauser
	{
	private:
		bool _paused;
	public:
		/// Pauses transform feedback
		/**
		 *  @glsymbols
		 *  @glfunref{PauseTransformFeedback}
		 */
		Pauser(void)
		 : _paused(true)
		{
			OGLPLUS_GLFUNC(PauseTransformFeedback)();
			OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(PauseTransformFeedback));
		}

#if !OGLPLUS_NO_DELETED_FUNCTIONS
		Pauser(const Pauser&) = delete;
#else
	private:
		Pauser(const Pauser&);
	public:
#endif

		Pauser(Pauser&& tmp)
		 : _paused(tmp._paused)
		{
			tmp._paused = false;
		}

		void Finish(void)
		{
			if(_paused)
			{
				OGLPLUS_GLFUNC(ResumeTransformFeedback)();
				OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(ResumeTransformFeedback));
				_paused = false;
			}
		}

		/// Resumes transform feedback
		/**
		 *  @glsymbols
		 *  @glfunref{ResumeTransformFeedback}
		 */
		~Pauser(void)
		{
			try{ Finish(); }
			catch(...){ }
		}
	};
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL transform feedback functionality
/**
 *  @ingroup objects
 */
class TransformFeedback
 : public TransformFeedbackOps
{ };
#else
typedef Object<TransformFeedbackOps> TransformFeedback;
#endif

#endif // transform feedback 2

} // namespace oglplus

#endif // include guard
