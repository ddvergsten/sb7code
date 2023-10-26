#version 460 core

// vertex attribute array
in vec4 position;

out VS_OUT // interface block
{
    vec4 color;

} vs_out;

// Interface Block (GLSL)
// https://www.khronos.org/opengl/wiki/Interface_Block_(GLSL)
/*
std430 - 
    Note that this layout can only be used
    with shader storage blocks, not uniform blocks.
*/
layout(std140, binding = 2) uniform TransformBlock
{
    mat4 mv_matrix;
    mat4 proj_matrix;

} transform;

// Shader Storage Buffer
layout(std430, binding = 0) buffer VertexIDs
{
    uint ids[];

} vertex_ids;

void main()
{
    gl_Position = transform.proj_matrix * transform.mv_matrix
                    * position;

    vec4 color_offset = vec4(1.0, 1.0, 1.0, 0.0);

    vertex_ids.ids[gl_VertexID] += gl_VertexID;

    vs_out.color = position + color_offset;
}