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

#include <sb7.h>
#include <iostream>
#include <vector>
class singlepoint_app : public sb7::application
{
    void init()
    {
        static const char title[] = "OpenGL SuperBible - Single Point";

        sb7::application::init();

        memcpy(info.title, title, sizeof(title));
    }

    virtual void startup()
    {
        static const char* vs_source[] =
        {
            "#version 330                                                       \n"


            "flat out vec3 startPos;                                            \n"
            "out vec3 vertPos;                                                  \n"


            "void main()                                                        \n"
            "{                                                                  \n"
            "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),   \n"
            "                                   vec4(-0.25, -0.25, 0.5, 1.0),   \n"
            "                                   vec4( 0.25,  0.25, 0.5, 1.0));  \n"
            "                                                                   \n"
            "    gl_Position = vertices[gl_VertexID];                           \n"
            "   vec4 posone = vertices[gl_VertexID];                            \n"
            "   vec3 pos = vec3(posone.x, posone.y, posone.z);                  \n"
            "    vertPos = pos;                                     \n"
            "    startPos = pos;                                            \n"
            "                                                                   \n"
            "}                                                                  \n"     
        };

        static const char* fs_source[] =
        {
            "#version 330                                                           \n"

            "flat in vec3 startPos;                                                 \n"
            "in vec3 vertPos;                                                       \n"

            "out vec4 fragColor;                                                    \n"

            "uniform vec2  u_resolution;                                            \n"
            "uniform uint  u_pattern;                                               \n"
            "uniform float u_factor;                                                \n"

            "void main()                                                            \n"
            "{                                                                      \n"
            "    vec2  dir = (vertPos.xy - startPos.xy) * u_resolution / 2.0;       \n"
            "    float dist = length(dir);                                          \n"

                "uint bit = uint(round(dist / u_factor)) & 15U;                     \n"
                "if ((u_pattern & (1U << bit)) == 0U)                               \n"
                "    discard;                                                       \n"
                "fragColor = vec4(1.0);                                             \n"
            "}                                                                      \n"


        };
        GLint isCompiled = -1;
        program = glCreateProgram();
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
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

            //std::cout << "fs_sourcePhong error:" << std::endl;
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

         loc_res = glGetUniformLocation(program, "u_resolution");
         loc_pattern = glGetUniformLocation(program, "u_pattern");
         loc_factor = glGetUniformLocation(program, "u_factor");

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }

    virtual void render(double currentTime)
    {
        static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, red);

        glUseProgram(program);

        glPointSize(40.0f);
        GLushort pattern = 0x0f0f;
        GLfloat  factor = 2.0f;
        glUniform1ui(loc_pattern, pattern);
        glUniform1f(loc_factor, factor);
        glUniform2f(loc_res, (float)info.windowWidth, (float)info.windowHeight);
        glDrawArrays(GL_LINE_STRIP, 0, 3);
    }

    virtual void shutdown()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteProgram(program);
    }

private:
    GLint loc_res;
    GLint loc_pattern;
    GLint loc_factor;
    GLuint          program;
    GLuint          vao;
};

DECLARE_MAIN(singlepoint_app)
