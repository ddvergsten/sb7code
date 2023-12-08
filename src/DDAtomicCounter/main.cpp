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
static const float data[] = {
    0.25, -0.25, 0.5, 1.0,
    -0.25, 0.25, 0.5, 1.0,
    -0.25, -0.25, 0.5, 1.0,
};

static const float data2[] = {
    0.25, 0.25, 0.5, 1.0,
    -0.25, -0.25, 0.5, 1.0,
    0.25, -0.25, 0.5, 1.0,
};

class singlepoint_app : public sb7::application
{
    int numPoints = 0;
    void init()
    {
        static const char title[] = "OpenGL SuperBible - Single Triangle";

        sb7::application::init();

        memcpy(info.title, title, sizeof(title));
        numPoints = sizeof(data) / 16;
        std::cout << "data size " << numPoints << std::endl;
    }

    virtual void startup()
    {
        static const char* vs_source[] =
        {
            "#version 450 core                                                 \n"
            "                                                                  \n"
            "out vec4 vs_color;                                                 \n"
            "                                                                   \n"
            "uniform mat4 mvMatrix;                                                                  \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
            "                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
            "                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
            "                                                                  \n"
            "   const vec4 colors[] = vec4[](vec4(1.0, 0.0, 0.0, 1.0),         \n"
            "                                   vec4(0.0, 1.0, 0.0, 1.0),       \n"
            "                                   vec4(0.0, 0.0, 1.0, 1.0));      \n"

            // "    gl_Position = vertices[gl_VertexID];                          \n"
             "   gl_Position = mvMatrix * vertices[gl_VertexID];                 \n"
             "   vs_color = colors[gl_VertexID];                                 \n"
             "}                                                                 \n"
        };

        static const char* fs_sourceArea[] =
        {
            "#version 450 core                                                          \n"
            "                                                                               \n"
            "layout (binding = 0, offset = 0) uniform atomic_uint area;                     \n"
            "                                                                               \n"
            "out vec4 color;                                                                \n"
            "void main(void)                                                                \n"
            "{                                                                              \n"
            //"   uint other = uint(area);                                                          \n"
            "   atomicCounterIncrement(area);                                               \n"
            //"       float brightness = clamp(float(area) ,                                  \n"
            //"                           0.0, 1.0);                                          \n"
           // "   color = vec4(1.0, 1.0, 1.0, 1.0);                      \n"
            "}                                                                              \n"
        };

        static const char* fs_sourceBright[] =
        {
            "#version 450 core                                                              \n"
            "                                                                               \n"
            "layout (binding = 0) uniform area_block                                        \n"
            "{                                                                              \n"
            "   uint counter_value;                                                         \n"
            "};                                                                             \n"
            "                                                                               \n"
            "out vec4 color;                                                                \n"
            "uniform float max_area;                                                        \n"
            "                                                                               \n"
            "void main(void)                                                                \n"
            "{                                                                              \n"
            "   float brightness = 0.0;                                                     \n"
            /*"   if(counter_value <= 0){                                                     \n"
            "       brightness = clamp(float(-1.0 * counter_value) / 100000.0,                  \n"
            "                           0.0, 1.0);                                          \n"
            "   }                                                                           \n"*/
            //"   else {                                                                      \n"
            "       brightness = clamp(float(counter_value) / 10000.0,                         \n"
            "                           0.0, 1.0);                                          \n"
            //"   }                                                                           \n"
            "   color = vec4(brightness, brightness, brightness, 1.0);                      \n"
            "}                                                                              \n"
        };

        //none of this changes
        programArea = glCreateProgram();
        programBright = glCreateProgram();
        GLuint fsArea = glCreateShader(GL_FRAGMENT_SHADER);
        GLint isCompiled = -1;
        glShaderSource(fsArea, 1, fs_sourceArea, NULL);
        glCompileShader(fsArea);
        glGetShaderiv(fsArea, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fsArea, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            //char eerrorlog[maxLength];
            glGetShaderInfoLog(fsArea, maxLength, &maxLength, &errorLog[0]);

            std::cout << "fs_sourcePhong error:" << std::endl;
            std::string strError(errorLog.begin(), errorLog.end());
            std::cout << strError << std::endl;

            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(fsArea); // Don't leak the shader.
            return;
        }

        GLuint fsBright = glCreateShader(GL_FRAGMENT_SHADER);
        isCompiled = -1;
        glShaderSource(fsBright, 1, fs_sourceBright, NULL);
        glCompileShader(fsBright);
        glGetShaderiv(fsBright, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fsBright, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            //char eerrorlog[maxLength];
            glGetShaderInfoLog(fsBright, maxLength, &maxLength, &errorLog[0]);

            std::cout << "fs_sourcePhong error:" << std::endl;
            std::string strError(errorLog.begin(), errorLog.end());
            std::cout << strError << std::endl;

            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(fsBright); // Don't leak the shader.
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
        glAttachShader(programArea, vs);
        glAttachShader(programArea, fsArea);
        glLinkProgram(programArea);

        glAttachShader(programBright, vs);
        glAttachShader(programBright, fsBright);
        glLinkProgram(programBright);

        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);
        GLint numExtensions = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
        for (int i = 0; i < numExtensions; i++) {
            const GLubyte* extName = glGetStringi(GL_EXTENSIONS, i);
            std::string str = (char*)extName;
            str.append("\n");
        }

        //////////////////
        
        glGenBuffers(1, &atomicbuf);
        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, atomicbuf);
        glBufferData(GL_ATOMIC_COUNTER_BUFFER, 16 * sizeof(GLuint),
            NULL, GL_DYNAMIC_COPY);
        glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, atomicbuf);//bind to 0 in our shader
        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, atomicbuf);
        const GLuint zero = 0;
        glBufferSubData(GL_ATOMIC_COUNTER_BUFFER, 16 * sizeof(GLuint), sizeof(GLuint), &zero);

        mv_locationBright = glGetUniformLocation(programBright, "mvMatrix");
        mv_locationArea = glGetUniformLocation(programArea, "mvMatrix");


        glVertexArrayVertexBuffer(vao, 0, atomicbuf, 0, 4 * sizeof(float));
        glEnableVertexArrayAttrib(vao, 0);
    }
    GLuint mv_locationArea = 0;
    GLuint mv_locationBright = 0;
    GLuint atomicbuf = 0;
    //GLuint ssbo;
    //GLuint vertex_id_buffer;
    //GLuint buffer;
    //double movex = 0.00;
    //bool moveright = true;
    //GLuint mv_location = 0;
    double movex = 0.00;
    bool moveright = true;

    virtual void render(double currentTime)
    {
        glUseProgram(programArea);

        if (movex > 0.5) {
            moveright = false;
        }
        if (movex < -0.5) {
            moveright = true;
        }
        if (moveright)
            movex += 0.01;
        else
            movex -= 0.01;
        vmath::vec3 view_position = vmath::vec3(0.0, movex, 0.55f);
        vmath::mat4 view_matrix = vmath::lookat(view_position,
            vmath::vec3(0.0, 0.0f, 0.5f),
            vmath::vec3(0.0f, 1.0f, 0.0f));
        vmath::mat4 view_matrixUnit;

        view_matrixUnit = view_matrixUnit.identity();
        glUniformMatrix4fv(mv_locationArea, 1, GL_FALSE, view_matrix);


        const GLuint zero = 0;
        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, atomicbuf);
        glBufferData(GL_ATOMIC_COUNTER_BUFFER,  sizeof(GLuint),
           &zero, GL_DYNAMIC_COPY);
       // glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, atomicbuf);//bind to 0 in our shader
       // glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, atomicbuf);
        //const GLuint zero = 0;
        glClearBufferSubData(GL_ATOMIC_COUNTER_BUFFER, GL_R32UI, sizeof(GLuint), sizeof(GLuint), 
            GL_RED_INTEGER, GL_UNSIGNED_INT, &zero);
        //const GLuint zero = 0;
        //glBufferSubData(GL_ATOMIC_COUNTER_BUFFER, 16 * sizeof(GLuint), sizeof(GLuint), &zero);


        //glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, atomicbuf);//bind to 0 in our shader
        //glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, atomicbuf);
        //const GLuint zero = 0;
        //glBufferSubData(GL_ATOMIC_COUNTER_BUFFER, 2 * sizeof(GLuint), sizeof(GLuint), &zero);

        //glBindBuffer(GL_ARRAY_BUFFER, buffer);
        //glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, ssbo);
        //glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, vertex_id_buffer);
        static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, green);

       // glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glDrawArrays(GL_TRIANGLES, 0, 3);



        glUseProgram(programBright);
        glUniformMatrix4fv(mv_locationBright, 1, GL_FALSE, view_matrix);

        glBindBufferBase(GL_UNIFORM_BUFFER, 0, atomicbuf);//bind to 0 in our shader
        glBindBuffer(GL_UNIFORM_BUFFER, atomicbuf);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
       glDrawArrays(GL_TRIANGLES, 0, 3);


        //this is reading off the buffer that is bound last, in this case vertex_id_buffer at offset 4 in the shader
        /*GLuint* ids = (GLuint*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, numPoints * sizeof(GLuint), GL_MAP_READ_BIT);

        for (int i = 0; i < numPoints; ++i)
        {
            int val = ids[i];
            std::cout << val << ", ";
        }

        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);*/
    }

    virtual void shutdown()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteProgram(programArea);
        glDeleteProgram(programBright);
    }

private:
    GLuint          programArea;
    GLuint          programBright;
    GLuint          vao;
};

DECLARE_MAIN(singlepoint_app)
