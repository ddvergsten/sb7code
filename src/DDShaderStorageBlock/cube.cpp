/*
  047- OGSB7 02, interface blocks, uniform blocks, primitive restart, MapBuffer, glBindBufferBase

 OGSB7 Chapter 3. Following the Pipeline,
	Passing Data from Stage to Stage, Interface Blocks, Page 72
  
 OGSB7 Chapter 5. Data, Creating Buffers and Allocating Memory
	Page 143, glMapBuffer, glMapNamedBuffer(), glMapBufferRange(), glMapNamedBufferRange()
 
 OGSB7 Chapter 5. Data, Uniform Blocks, Page 158
 	glBindBufferBase, glUniformBlockBinding, Page 169
 
 OGSB7 Chapter 7. Vertex Processing and Drawing Commands	
	Combining Geometry Using Primitive Restart. Page 291
	
Shader Storage Buffer Object
	https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object
	
Previous Videos

092 - OpenGL Rotating Cube 2, Restart Primitives, Triangle Strips, Vertex Indices
	https://www.youtube.com/watch?v=87oBkyIR144&list=PL1_C6uWTeBDF7kjfRMCmHIq1FncthhBpQ&index=94
	
091 - OpenGL Rotating Cube 1, Restart Primitives, Triangle Strips, Vertex Indices
	https://www.youtube.com/watch?v=E26yOrl97Ac&list=PL1_C6uWTeBDF7kjfRMCmHIq1FncthhBpQ&index=91
    
047- OGSB7 02, interface blocks, uniform blocks, primitive restart, MapBuffer, glBindBufferBase
	https://www.youtube.com/watch?v=zzm0C4rZQpY&list=PL1_C6uWTeBDGdY7x23Xg3MaHKnka5WSKF&index=47

046- OGPG9 06, OpenGL Subroutines, Projection Matrix Transformation
	https://www.youtube.com/watch?v=oKOodsqJRCQ&list=PL1_C6uWTeBDGdY7x23Xg3MaHKnka5WSKF&index=46

045- OGPG9 05, OpenGL Subroutines, Cross Hair, OpenGL Shader Syntax Debugging
	https://www.youtube.com/watch?v=YVw5z22Acm4&list=PL1_C6uWTeBDGdY7x23Xg3MaHKnka5WSKF&index=45
	
044- OGPG9 04, OpenGL Subroutines, matrix and vectors in Shaders
	https://www.youtube.com/watch?v=wsITCmSqE1Y&list=PL1_C6uWTeBDGdY7x23Xg3MaHKnka5WSKF&index=44
	
043- OGPG9 03, Indexed Drawing 2, glDrawElements, OpenGL Camera Eye, frustum, aspect ratio
	https://www.youtube.com/watch?v=6MO8TJT2IxU&list=PL1_C6uWTeBDGdY7x23Xg3MaHKnka5WSKF&index=43

042- OGPG9 02, Indexed Drawing 1, glDrawElements, glNamedBufferData, glNamedBufferSubData, uniform
	https://www.youtube.com/watch?v=XulkB7YcjTo&list=PL1_C6uWTeBDGdY7x23Xg3MaHKnka5WSKF&index=42
	
041- OGPG9 01, OpenGL Songs, Vertex Array Object, Vertex Buffer Object, Vertex Attrib Array
	https://www.youtube.com/watch?v=VzJxxk7mWTU&list=PL1_C6uWTeBDGdY7x23Xg3MaHKnka5WSKF&index=41
	
040- OGSB7 01, OpenGL Shader Programming, Response File
	https://www.youtube.com/watch?v=Wb9yv1z22Wc&list=PL1_C6uWTeBDGdY7x23Xg3MaHKnka5WSKF&index=40
	
039- (SETUP) OpenGL Windows Command-line, Windows on Command Prompt, /SUBSYSTEM:console
	https://www.youtube.com/watch?v=q5S8XrNzrME&list=PL1_C6uWTeBDGdY7x23Xg3MaHKnka5WSKF&index=39
	
038- OpenGL Experiment 2, Matrix Stack, glPushMatrix(), glPopMatrix()
	https://www.youtube.com/watch?v=deHDP5VLbzA&list=PL1_C6uWTeBDGdY7x23Xg3MaHKnka5WSKF&index=38

037- OpenGL Experiment 1, Clipping Plane, Matrix Stack
	https://www.youtube.com/watch?v=_dQCdtYIS3E&list=PL1_C6uWTeBDGdY7x23Xg3MaHKnka5WSKF&index=37
	
036- (SETUP) Environment Variables for OpenGL Tools, Simple Experiments with OpenGL
	https://www.youtube.com/watch?v=mqqE6h6IqUU&list=PL1_C6uWTeBDGdY7x23Xg3MaHKnka5WSKF&index=36
	
035- (SETUP) OpenGL Tools, C++ Library Extensions, Commandline Prompts for CUDA and DPC++
	https://www.youtube.com/watch?v=nKNA3c4CKI0&list=PL1_C6uWTeBDGdY7x23Xg3MaHKnka5WSKF&index=35
	
034- (SETUP) Microsoft Visual Studio, Nvidia CUDA, OpenCL C++ Headers
	https://www.youtube.com/watch?v=2paxQofaeOk&list=PL1_C6uWTeBDGdY7x23Xg3MaHKnka5WSKF&index=34

Downloads:

1. C++ Library Extensions
	https://www.talkplayfun.com/sourcecode/CppExtensions2023/CppExtension.zip
	
2. OpenGL Tools
		
	https://www.talkplayfun.com/sourcecode/ElectricityAndMagnetism/gl-tools.zip
	
	https://www.talkplayfun.com/sourcecode/ElectricityAndMagnetism/ogpg9-tools.zip
	
	https://www.talkplayfun.com/sourcecode/ElectricityAndMagnetism/ogsb7-tools.zip
	
	OpenGL Programming Guide: The Official Guide to Learning OpenGL, Version 4.5 with SPIR-V
		https://tinyurl.com/mr3mhu8p
	
	Sample Code
	https://www.talkplayfun.com/sourcecode/ElectricityAndMagnetism/000-OGPG9-examples-master.zip
	
	OpenGL Superbible: Comprehensive Tutorial and Reference 
		https://tinyurl.com/b235z8cm
		
	Sample Code
	https://www.talkplayfun.com/sourcecode/ElectricityAndMagnetism/000-OGSB7-sb7code-master.zip
		
Command Prompts and Icons
		https://www.talkplayfun.com/sourcecode/ElectricityAndMagnetism/icons.zip
		
	Example:
		https://www.talkplayfun.com/sourcecode/ElectricityAndMagnetism/OpenGL-Debugging-Solution.zip
		
Download Current Video's Source Code
	
	https://www.talkplayfun.com/sourcecode/ElectricityAndMagnetism/047-UniformBlock.zip
	
*/

#include <cpg/cpg_std_extensions.hpp>
#include <ogsb7.hpp>

// icx-cl cube.cpp -o i.exe -Qstd=c++20 /EHsc /MDd /link /SUBSYSTEM:CONSOLE

class Cube: public sb7::application
{
    public:
    using base = sb7::application;

    static GLuint load_shaders()
    {
        GLuint vertex_shader = sb7::shader::load("cube.vert", GL_VERTEX_SHADER);
        GLuint fragment_shader = sb7::shader::load("cube.frag", GL_FRAGMENT_SHADER);

        GLuint program = glCreateProgram();

        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);

        glLinkProgram(program);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return program;
    }

    private:

        GLuint program;
        GLuint vertex_array_object;

        GLuint position_buffer;
        GLuint indices_buffer;
        GLuint transform_buffer;

        GLuint vertex_id_buffer;

        std::vector<GLfloat> vertex_positions;
        std::vector<GLushort> vertex_indices;

        GLint position_loc;
        GLint transform_loc;

    public:

    void run(sb7::application* the_app) override
    {
        bool running = true;
        app = the_app;

        if (!glfwInit())
        {
            fprintf(stderr, "Failed to initialize GLFW\n");
            return;
        }

        init();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, info.majorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, info.minorVersion);

#ifndef _DEBUG
        if (info.flags.debug)
#endif /* _DEBUG */
        {
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        }
        if (info.flags.robust)
        {
            glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET);
        }
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_SAMPLES, info.samples);
        glfwWindowHint(GLFW_STEREO, info.flags.stereo ? GL_TRUE : GL_FALSE);

        {
            window = glfwCreateWindow(info.windowWidth, info.windowHeight, info.title, info.flags.fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
            if (!window)
            {
                fprintf(stderr, "Failed to open window\n");
                return;
            }
        }

        glfwMakeContextCurrent(window);

        glfwSetWindowSizeCallback(window, glfw_onResize);
        glfwSetKeyCallback(window, glfw_onKey);
        glfwSetMouseButtonCallback(window, glfw_onMouseButton);
        glfwSetCursorPosCallback(window, glfw_onMouseMove);
        glfwSetScrollCallback(window, glfw_onMouseWheel);
        if (!info.flags.cursor)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        }

        // info.flags.stereo = (glfwGetWindowParam(GLFW_STEREO) ? 1 : 0);

        gl3wInit();

#ifdef _DEBUG
        fprintf(stderr, "VENDOR: %s\n", (char *)glGetString(GL_VENDOR));
        fprintf(stderr, "VERSION: %s\n", (char *)glGetString(GL_VERSION));
        fprintf(stderr, "RENDERER: %s\n", (char *)glGetString(GL_RENDERER));
#endif
        
        startup();

        do
        {
            render(glfwGetTime());

            // glfwSwapBuffers(window);

            glfwPollEvents();

            running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);
            running &= (glfwWindowShouldClose(window) != GL_TRUE);
        } while (running);

        shutdown();

        glfwDestroyWindow(window);
        glfwTerminate();
    }
    
    void startup() override
    {
        onResize(base::info.windowWidth, base::info.windowHeight);

        program = load_shaders();

        // we initialized vertex positions and indices for our cube
        {
            /*
                092 - OpenGL Rotating Cube 2, Restart Primitives, Triangle Strips, Vertex Indices
                    https://www.youtube.com/watch?v=87oBkyIR144&list=PL1_C6uWTeBDF7kjfRMCmHIq1FncthhBpQ&index=94
            
                091 - OpenGL Rotating Cube 1, Restart Primitives, Triangle Strips, Vertex Indices
                    https://www.youtube.com/watch?v=E26yOrl97Ac&list=PL1_C6uWTeBDF7kjfRMCmHIq1FncthhBpQ&index=91
            */
            constexpr GLfloat vertex_positions_array[] =
            {
                -1, -1, -1,  1, // vertex 0
                -1,  1, -1,  1, // vertex 1
                 1,  1, -1,  1, // vertex 2
                 1, -1, -1,  1, // vertex 3
                -1,  1,  1,  1, // vertex 4
                -1, -1,  1,  1, // vertex 5
                 1, -1,  1,  1, // vertex 6
                 1,  1,  1,  1  // vertex 7
            };

            constexpr GLushort vertex_indices_array[] =
            {
                4, 1, 5, 0, 6, 3, 7, 2,
                (GLushort)(-1), // == 0xFFFF FFFF
                5, 6, 4, 7, 1, 2, 0, 3
            };

            vertex_positions.assign(std::begin(vertex_positions_array), std::end(vertex_positions_array));
            vertex_indices.assign(std::begin(vertex_indices_array), std::end(vertex_indices_array));

            // std::cout <<"Vertex Positions:\n\t" << vertex_positions << cpg::endL;
            // std::cout <<"Vertex Indices  :\n\t" << vertex_indices << cpg::endL;

        }

        position_loc = glGetAttribLocation(program, "position");
        transform_loc = glGetUniformLocation(program, "transform");

        glCreateVertexArrays(1, &vertex_array_object);
        glBindVertexArray(vertex_array_object);

        // create and initialize buffer for vertex positions
        glCreateBuffers(1, &position_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
        glBufferData(GL_ARRAY_BUFFER, 
            vertex_positions.size() * sizeof(GLfloat),
            vertex_positions.data(), GL_STATIC_DRAW);

        // create and initialize buffer for vertex indices
        glCreateBuffers(1, &indices_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            vertex_indices.size() * sizeof(GLushort),
            vertex_indices.data(), GL_STATIC_DRAW);

        // create an uninitialzed buffer for uniform TransformBlock
        glCreateBuffers(1, &transform_buffer);
        glBindBuffer(GL_UNIFORM_BUFFER, transform_buffer);
        glBufferData(GL_UNIFORM_BUFFER, 
            2 * sizeof(vmath::mat4),
            NULL, GL_DYNAMIC_DRAW);

        // create an unitialized buffer for shader storage buffer object
        glCreateBuffers(1, &vertex_id_buffer);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertex_id_buffer);
        glBufferData(GL_SHADER_STORAGE_BUFFER,
            vertex_indices.size() * sizeof(GLuint),
            NULL, GL_DYNAMIC_COPY);

        glVertexAttribPointer(position_loc, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(position_loc);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void render(double currentTime) override
    {
        static const GLfloat green[]{0.0f, 0.25f, 0.0f, 1.0f};
        static const GLfloat one = 1.0f;

        glClearBufferfv(GL_COLOR, 0, green);
        glClearBufferfv(GL_DEPTH, 0, &one);

        glUseProgram(program);

        GLuint transform_binding = 2;
        // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniformBlockBinding.xhtml
        // glUniformBlockBinding(program, transform_loc, transform_binding);

        // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindBufferBase.xhtml
        glBindBufferBase(GL_UNIFORM_BUFFER, transform_binding, transform_buffer);

        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, vertex_id_buffer);

        float f =(float)currentTime * 0.3f;

        /*
            https://registry.khronos.org/OpenGL-Refpages/gl4/html/glMapBufferRange.xhtml
            GL_MAP_INVALIDATE_BUFFER_BIT
            the previous contents of the entire buffer may be discarded.

            OGSB7 Chapter 5. Data, Creating Buffers and Allocating Memory
	        Page 143, glMapBuffer, glMapNamedBuffer(), glMapBufferRange(), glMapNamedBufferRange()
        */
        vmath::mat4* transforms = (vmath::mat4*)
            glMapBufferRange(GL_UNIFORM_BUFFER, 0, 2 * sizeof(vmath::mat4),
                GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

        // mv_matrix;
        transforms[0] = vmath::translate(0.0f, 0.0f, -10.0f) *
                        vmath::translate(sinf(2.1f * f) * 0.5f,
                                    cosf(1.7f * f) * 0.5f,
                                    sinf(1.3f * f) * cosf(1.5f * f) * 2.0f) *
                        vmath::rotate((float)currentTime * 45.0f, 0.0f, 1.0f, 0.0f) *
                        vmath::rotate((float)currentTime * 81.0f, 1.0f, 0.0f, 0.0f);

        // proj_matrix;
        transforms[1] =  vmath::perspective(50.0f,
                            (float)info.windowWidth / (float)info.windowHeight,
                            1.0f,
                            1000.0f);

        glUnmapBuffer(GL_UNIFORM_BUFFER);

        /*
            OGSB7 Chapter 7. Vertex Processing and Drawing Commands	
	            Combining Geometry Using Primitive Restart. Page 291

            092 - OpenGL Rotating Cube 2, Restart Primitives, Triangle Strips, Vertex Indices
	            https://www.youtube.com/watch?v=87oBkyIR144&list=PL1_C6uWTeBDF7kjfRMCmHIq1FncthhBpQ&index=94
	
            091 - OpenGL Rotating Cube 1, Restart Primitives, Triangle Strips, Vertex Indices
	            https://www.youtube.com/watch?v=E26yOrl97Ac&list=PL1_C6uWTeBDF7kjfRMCmHIq1FncthhBpQ&index=91
        */
        glEnable(GL_PRIMITIVE_RESTART);
        glPrimitiveRestartIndex( (GLushort)(-1));

        glDrawElements(GL_TRIANGLE_STRIP, vertex_indices.size(),
            GL_UNSIGNED_SHORT, NULL);

        glfwSwapBuffers(window);

        GLuint* ids = (GLuint*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER,
            0, vertex_indices.size() * sizeof(GLuint), GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

        for(int i = 0; i < (int)vertex_indices.size(); ++i)
        {
            std::cout <<ids[i] <<", ";

            ids[i] = 0;
        }

        std::cout << std::endl;

        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    }
    // end of function render()

    void shutdown() override
    {
        glDeleteProgram(program);

        glDeleteVertexArrays(1, &vertex_array_object);
        
        glDeleteBuffers(1, &position_buffer);
        glDeleteBuffers(1, &indices_buffer);
        glDeleteBuffers(1, &transform_buffer);
    }

    void onResize(int w, int h) override
    {
        // std::cout <<"onResize() called" << cpg::endl;
        std::cout <<"w = " << w <<", h = " << h << cpg::endl;

        base::onResize(w, h);

        if(w > h)
            glViewport( (w - h)/2, 0, h, h);
        else
            glViewport(0, (h - w)/2, w, w);
    }


};

DECLARE_MAIN(Cube)

int main()
{
    auto hInstance = ::GetModuleHandle(NULL);
    WinMain(hInstance, NULL, NULL, SW_SHOW);
}

