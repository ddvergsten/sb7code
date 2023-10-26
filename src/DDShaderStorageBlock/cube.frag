#version 460 core

out vec4 color;

in VS_OUT // interface block name
{
    vec4 color;

} fs_in;

void main()
{
    color = fs_in.color;
}