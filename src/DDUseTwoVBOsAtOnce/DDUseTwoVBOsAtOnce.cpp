/*
 * Copyright © 2012-2015 Graham Sellers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <sb7.h>
#include <vmath.h>
#include <string>
#include <vector>
#include <iostream>
static const float positions[] = {
    0.25, -0.25, 0.5, 1.0,
    -0.25, 0.25, 0.5, 1.0,
    -0.25, -0.25, 0.5, 1.0,
};

static const float colors[] = {
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0,0.0,1.0
};

class singlepoint_app : public sb7::application
{
    void init()
    {
        static const char title[] = "OpenGL SuperBible - Single Triangle";

        sb7::application::init();

        memcpy(info.title, title, sizeof(title));
    }

    virtual void startup()
    {
        static const char* vs_source[] =
        {
            "#version 450 core                                                 \n"
            "                                                                  \n"
            //have to add some vars here for the vertices that will come from buffer
            "out vec4 vs_color;                                                 \n"
            "                                                                   \n"
            "layout (location = 0) in vec4 position;                            \n"
            "layout (location = 1) in vec4 color;                               \n"      
            //don't need the mvmatrix stuff, just use NDC for now for simplicity
            //"uniform mat4 mvMatrix;                                                                  \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            //this will now come from the buffer
            "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
            "                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
            "                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
            "                                                                  \n"
            //colors can stay
            "   const vec4 colors[] = vec4[](vec4(1.0, 0.0, 0.0, 1.0),         \n"
            "                                   vec4(0.0, 1.0, 0.0, 1.0),       \n"
            "                                   vec4(0.0, 0.0, 1.0, 1.0));      \n"

            
             "   gl_Position = position;                                        \n"
             "   vs_color = color;                                              \n"
             "}                                                                 \n"
        };

        static const char* fs_source[] =
        {
            "#version 450 core                                                          \n"
            "                                                                               \n"
            "in  vec4 vs_color;                                                             \n"
            "out vec4 color;                                                                \n"
            "                                                                               \n"
            "vec4 c = vec4(1.0, 0.0, 0.0, 1.0);     \n"
            "void main(void)                                                            \n"
            "{                                                                          \n"
            //this doesn't change
            "   color = vs_color;                                                       \n"
            "}                                                                          \n"
        };

        //none of this changes
        program = glCreateProgram();
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        GLint isCompiled = -1;
        glShaderSource(fs, 1, fs_source, NULL);
        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            //char eerrorlog[maxLength];
            glGetShaderInfoLog(fs, maxLength, &maxLength, &errorLog[0]);

            std::cout << "fs_sourcePhong error:" << std::endl;
            std::string strError(errorLog.begin(), errorLog.end());
            std::cout << strError << std::endl;

            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(fs); // Don't leak the shader.
            return;
        }
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, vs_source, NULL);
        glCompileShader(vs);
        glGetShaderiv(vs, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            //char eerrorlog[maxLength];
            glGetShaderInfoLog(vs, maxLength, &maxLength, &errorLog[0]);

            std::cout << "fs_sourcePhong error:" << std::endl;
            std::string strError(errorLog.begin(), errorLog.end());
            std::cout << strError << std::endl;

            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(vs); // Don't leak the shader.
            return;
        }
        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);

        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);
        GLint numExtensions = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
        for (int i = 0; i < numExtensions; i++) {
            const GLubyte* extName = glGetStringi(GL_EXTENSIONS, i);
            std::string str = (char*)extName;
            str.append("\n");
        }
        //we now wanna create a buffer, allocate to about 1 meg, 
        //set target as GLARRAYBUFFER.
        glCreateBuffers(2, &buffer[0]);

        glNamedBufferStorage(buffer[0], sizeof(positions), positions, 0);
        glVertexArrayVertexBuffer(vao, 0, buffer[0], 0, 4 * sizeof(float));
        //glVertexArrayVertexBuffer(vao, 0, buffer[0], 0, 4 * sizeof(float));
        glVertexArrayAttribBinding(vao, 0, 0);
        glEnableVertexArrayAttrib(vao, 0);

        glNamedBufferStorage(buffer[1], sizeof(colors), colors, 0);
        glVertexArrayVertexBuffer(vao, 1, buffer[1], 0, 3 * sizeof(float));
        //glVertexArrayVertexBuffer(vao, 1, buffer[1], 0, 3 * sizeof(float));
        glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(vao, 1, 1);
        glEnableVertexAttribArray(1);
    }
    GLuint buffer[2];
    double movex = 0.00;
    bool moveright = true;
    GLuint mv_location = 0;

    virtual void render(double currentTime)
    {
        glUseProgram(program);
        //the state of using the 2 buffers with this shader is stored in the vao, so just bind it
        glBindVertexArray(vao);
        static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, green);


        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    virtual void shutdown()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteProgram(program);
    }

private:
    GLuint          program;
    GLuint          vao;
};

DECLARE_MAIN(singlepoint_app)
