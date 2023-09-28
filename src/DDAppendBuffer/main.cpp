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

            // 
             "   gl_Position = position;//vertices[gl_VertexID];//position;                                        \n"//mvMatrix * vertices[gl_VertexID];                 \n"
             "   vs_color = colors[gl_VertexID];                                          \n"//gl_VertexID % 3];                                 \n"
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
            //OutputDebugString((LPCWSTR)extName);
            std::string str = (char*)extName;
            str.append("\n");
            //OutputDebugString(str.c_str());

        }
        //we now wanna create a buffer, allocate to about 1 meg, 
        //set target as GLARRAYBUFFER.
        glCreateBuffers(1, &buffer);
        glNamedBufferStorage(buffer, 1024 * 1024, NULL, GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        glBufferSubData(GL_ARRAY_BUFFER,
            0, 4 * 3 * sizeof(float), data2);
       void* ptr2 = glMapNamedBufferRange(buffer, 4 * 3 * sizeof(float), 4 * 3 * sizeof(float), GL_MAP_WRITE_BIT);
        memcpy(ptr2, data, sizeof(data));
        glUnmapNamedBuffer(GL_ARRAY_BUFFER);

        glVertexArrayVertexBuffer(vao, 0, buffer, 0, 4 * sizeof(float));
        glEnableVertexArrayAttrib(vao, 0);
    }
    GLuint buffer;
    double movex = 0.00;
    bool moveright = true;
    GLuint mv_location = 0;

    virtual void render(double currentTime)
    {
        glUseProgram(program);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

       // int vertexCoordLoc = glGetAttribLocation(program, "position");
       // int textureCoordLoc = glGetAttribLocationRIT(program, "a_texcoord");

        //glVertexAttribPointer(vertexCoordLoc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0 * sizeof(GLfloat)));
        //glEnableVertexAttribArray(vertexCoordLoc);

        /*glVertexAttribPointerRIT(textureCoordLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArrayRIT(textureCoordLoc);*/
        //lets add a triangle slightly shifted every second or so, append it to the end
        // of the buffer we created above, and in gldraw draw 3 more each time we add another triangle
        
        //remove the gl lookat stuff
        //mv_location = glGetUniformLocation(program, "mvMatrix");
        //if (movex > 1.0) {
        //    moveright = false;
        //}
        //if (movex < -1.0) {
        //    moveright = true;
        //}
        //if (moveright)
        //    movex += 0.001;
        //else
        //    movex -= 0.001;
        //vmath::vec3 view_position = vmath::vec3(movex, 0.0, 0.55f);
        //vmath::mat4 view_matrix = vmath::lookat(view_position,
        //    vmath::vec3(0.0, 0.0f, 0.5f),
        //    vmath::vec3(0.7f, 0.7f, 0.0f));
        //vmath::mat4 view_matrixUnit;

        ////this can all come out
        //view_matrixUnit = view_matrixUnit.identity();
        //glUniformMatrix4fv(mv_location, 1, GL_FALSE, view_matrix);
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
