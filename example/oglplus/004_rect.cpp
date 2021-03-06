/**
 *  @example oglplus/004_rect.cpp
 *  @brief Shows how to draw a custom shaded rectangle
 *
 *  @oglplus_screenshot{004_rect}
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

#include "example.hpp"

namespace oglplus {

class RectangleExample : public Example
{
private:
	// wrapper around the current OpenGL context
	Context gl;

	// Vertex and fragment shaders
	Shader vs, fs;

	// Program
	Program prog;

	// A vertex array object for the rendered rectangle
	VertexArray rectangle;

	// VBO for the rectangle's vertices
	Buffer verts;

	// Variables referencing the program's uniforms
	LazyUniform<Vec2f> red_center, green_center, blue_center;
public:
	RectangleExample(void)
	 : vs(ShaderType::Vertex)
	 , fs(ShaderType::Fragment)
	 , prog()
	 , red_center(prog, "RedCenter")
	 , green_center(prog, "GreenCenter")
	 , blue_center(prog, "BlueCenter")
	{
		// Set the vertex shader source
		vs.Source(StrLit(" \
			#version 330\n \
			in vec2 Position; \
			out vec2 vertCoord; \
			void main(void) \
			{ \
				vertCoord = Position; \
				gl_Position = vec4(Position, 0.0, 1.0); \
			} \
		"));
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(StrLit(" \
			#version 330\n \
			const float radius = 0.4; \
			in vec2 vertCoord; \
			uniform vec2 RedCenter, GreenCenter, BlueCenter; \
			out vec4 fragColor; \
			void main(void) \
			{ \
				vec3 dist = vec3( \
					distance(vertCoord, RedCenter), \
					distance(vertCoord, GreenCenter), \
					distance(vertCoord, BlueCenter) \
				); \
				fragColor = vec4( \
					dist.r < radius ? 1.0 : (2*radius - dist.r) / radius, \
					dist.g < radius ? 1.0 : (2*radius - dist.g) / radius, \
					dist.b < radius ? 1.0 : (2*radius - dist.b) / radius, \
					1.0 \
				); \
			} \
		"));
		// compile it
		fs.Compile();

		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(fs);
		// link and use it
		prog.Link();
		prog.Use();

		// bind the VAO for the rectangle
		rectangle.Bind();

		GLfloat rectangle_verts[8] = {
			-1.0f, -1.0f,
			-1.0f,  1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f
		};
		// bind the VBO for the rectangle vertices
		verts.Bind(Buffer::Target::Array);
		// upload the data
		Buffer::Data(Buffer::Target::Array, 8, rectangle_verts);
		// setup the vertex attribs array for the vertices
		VertexAttribArray vert_attr(prog, "Position");
		vert_attr.Setup(2, DataType::Float);
		vert_attr.Enable();
		//
		red_center.Set(-0.141f, 0.141f);
		green_center.Set(0.141f, 0.141f);
		blue_center.Set(0.0f, -0.2f);

		gl.Disable(Capability::DepthTest);
	}

	void Reshape(GLuint width, GLuint height)
	{
		gl.Viewport(width, height);
	}

	void Render(double)
	{
		gl.Clear().ColorBuffer();

		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);
	}
};

void setupExample(ExampleParams& /*params*/){ }

std::unique_ptr<ExampleThread> makeExampleThread(
	Example& /*example*/,
	unsigned /*thread_id*/,
	const ExampleParams& /*params*/
){ return std::unique_ptr<ExampleThread>(); }

std::unique_ptr<Example> makeExample(const ExampleParams& /*params*/)
{
	return std::unique_ptr<Example>(new RectangleExample);
}

} // namespace oglplus
