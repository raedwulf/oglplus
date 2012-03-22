/**
 *  @example oglplus/019_helium.cpp
 *  @brief Shows how to draw a naive helium atom model
 *
 *  @image html 019_helium.png
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/sphere.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class Sphere
{
private:
	// helper object building sphere's vertex attributes
	shapes::Sphere make_sphere;
	// helper object encapsulating the drawing instructions
	shapes::DrawingInstructions sphere_instr;
	// indices pointing to the sphere's primitive elements
	typename shapes::Sphere::IndexArray sphere_indices;

	// Fragment shader is owned by each individual sphere
	FragmentShader fs;

	// Shading program
	Program prog;

	// A vertex array object for the rendered sphere
	VertexArray sphere;

	// VBOs for the sphere's vertices and normals
	Buffer verts, normals;
public:
	Sphere(const VertexShader& vs, FragmentShader&& frag)
	 : sphere_instr(make_sphere.Instructions())
	 , sphere_indices(make_sphere.Indices())
	 , fs(std::forward<FragmentShader>(frag))
	{
		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(fs);
		// link and use it
		prog.Link();
		prog.Use();

		// bind the VAO for the sphere
		sphere.Bind();

		const size_t n_attr = 2;
		// pointers to the vertex attribute data build functions
		typedef GLuint (shapes::Sphere::*Func)(std::vector<GLfloat>&) const;
		Func func[n_attr] = {
			&shapes::Sphere::Positions,
			&shapes::Sphere::Normals,
		};
		// managed references to the VBOs
		Managed<Buffer> vbo[n_attr] = {verts, normals};
		// vertex attribute identifiers from the shaders
		const GLchar* ident[n_attr] = {"Position", "Normal"};

		for(size_t i=0; i!=n_attr; ++i)
		{
			// bind the VBO
			vbo[i].Bind(Buffer::Target::Array);
			// make the data
			std::vector<GLfloat> data;
			GLuint n_per_vertex = (make_sphere.*func[i])(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attrib
			VertexAttribArray attr(prog, ident[i]);
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}
	}

	void SetProjection(const Mat4f& projection)
	{
		prog.Use();
		SetUniform(prog, "ProjectionMatrix", projection);
	}

	void SetLightAndCamera(const Vec3f& light, const Mat4f& camera)
	{
		// use the shading program
		prog.Use();
		// set the uniforms
		SetUniform(prog, "LightPos", light);
		SetUniform(prog, "CameraMatrix", camera);
	}

	void Render(const Mat4f& model)
	{
		prog.Use();
		SetUniform(prog, "ModelMatrix", model);
		// bind the VAO
		sphere.Bind();
		// use the instructions to draw the sphere
		// (this basically calls glDrawArrays* or glDrawElements*)
		sphere_instr.Draw(sphere_indices);
	}
};

class SphereExample : public Example
{
private:
	// wrapper around the current OpenGL context
	Context gl;

	// The vertex shader is shader by the spheres
	VertexShader vs;

	// Makes the common shared vertex shader
	static VertexShader make_vs(void)
	{
		VertexShader shader;

		shader.Source(
			"#version 330\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;"
			"in vec4 Position;"
			"in vec3 Normal;"
			"out vec3 vertNormal;"
			"out vec3 vertLight;"
			"out vec3 vertViewNormal;"
			"uniform vec3 LightPos;"
			"void main(void)"
			"{"
			"	vertNormal = ("
			"		ModelMatrix *"
			"		vec4(Normal, 0.0)"
			"	).xyz;"
			"	vertViewNormal = ("
			"		CameraMatrix *"
			"		ModelMatrix *"
			"		vec4(Normal, 0.0)"
			"	).xyz;"
			"	vertLight = ("
			"		vec4(LightPos, 0.0)-"
			"		ModelMatrix * Position"
			"	).xyz;"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		ModelMatrix *"
			"		Position;"
			"}"
		);

		shader.Compile();
		return shader;
	}

	// The common first part of all fragment shader sources
	static const GLchar* fs_prologue(void)
	{
		return
		"#version 330\n"
		"in vec3 vertNormal;"
		"in vec3 vertLight;"
		"in vec3 vertViewNormal;"
		"out vec4 fragColor;"
		"void main(void)"
		"{"
		"	float lighting = dot("
		"		vertNormal, "
		"		normalize(vertLight)"
		"	);"
		"	float intensity = clamp("
		"		0.4 + lighting * 1.0,"
		"		0.0,"
		"		1.0"
		"	);";
	}

	// The common last part of all fragment shader sources
	static const GLchar* fs_epilogue(void)
	{
		return
		"	fragColor = sig?"
		"		vec4(1.0, 1.0, 1.0, 1.0):"
		"		vec4(color * intensity, 1.0);"
		"}";
	}

	// The part calculating the color for the protons
	static const GLchar* fs_proton(void)
	{
		return
		"	bool sig = ("
		"		abs(vertViewNormal.x) < 0.5 &&"
		"		abs(vertViewNormal.y) < 0.2 "
		"	) || ("
		"		abs(vertViewNormal.y) < 0.5 &&"
		"		abs(vertViewNormal.x) < 0.2 "
		"	);"
		"	vec3 color = vec3(1.0, 0.0, 0.0);";
	}

	// The part calculating the color for the neutrons
	static const GLchar* fs_neutron(void)
	{
		return
		"	bool sig = false;"
		"	vec3 color = vec3(0.5, 0.5, 0.5);";
	}

	// The part calculating the color for the electrons
	static const GLchar* fs_electron(void)
	{
		return
		"	bool sig = ("
		"		abs(vertViewNormal.x) < 0.5 &&"
		"		abs(vertViewNormal.y) < 0.2"
		"	);"
		"	vec3 color = vec3(0.0, 0.0, 1.0);";
	}

	// makes a fragment shader from the prologe, custom part and epilogue
	static FragmentShader make_fs(const char* color_fs)
	{
		FragmentShader shader;
		const GLchar* src[3] = {fs_prologue(), color_fs, fs_epilogue()};
		shader.Source(src, 3);
		shader.Compile();
		return shader;
	}

	Sphere proton;
	Sphere neutron;
	Sphere electron;
public:
	SphereExample(void)
	 : vs(make_vs())
	 , proton(vs,make_fs(fs_proton()))
	 , neutron(vs,make_fs(fs_neutron()))
	 , electron(vs,make_fs(fs_electron()))
	{
		gl.ClearColor(0.3f, 0.3f, 0.3f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		auto projection = CamMatrixf::PerspectiveX(
			Degrees(48),
			double(width)/height,
			1, 100
		);
		proton.SetProjection(projection);
		neutron.SetProjection(projection);
		electron.SetProjection(projection);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		// make the light position vector
		auto light = Vec3f(8.0f, 8.0f, 8.0f);
		// make the matrix for camera orbiting the origin
		auto camera = CamMatrixf::Orbiting(
			Vec3f(),
			19.0,
			Degrees(time * 15),
			Degrees(SineWave(time*0.15) * 45)
		);
		auto nucl = ModelMatrixf::RotationA(
			Vec3f(1.0f, 1.0f, 1.0f),
			FullCircles(time)
		);

		proton.SetLightAndCamera(light, camera);
		proton.Render(nucl * ModelMatrixf::Translation(+1.4f,0.0f,0.0f));
		proton.Render(nucl * ModelMatrixf::Translation(-1.4f,0.0f,0.0f));

		neutron.SetLightAndCamera(light, camera);
		neutron.Render(nucl * ModelMatrixf::Translation(0.0f,0.0f,+1.0f));
		neutron.Render(nucl * ModelMatrixf::Translation(0.0f,0.0f,-1.0f));

		electron.SetLightAndCamera(light, camera);
		electron.Render(
			ModelMatrixf::RotationY(FullCircles(time * 0.7)) *
			ModelMatrixf::Translation(10.0f, 0.0f, 0.0f)
		);
		electron.Render(
			ModelMatrixf::RotationX(FullCircles(time * 0.7)) *
			ModelMatrixf::Translation(0.0f, 0.0f, 10.0f)
		);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& params)
{
	return std::unique_ptr<Example>(new SphereExample);
}

} // namespace oglplus
