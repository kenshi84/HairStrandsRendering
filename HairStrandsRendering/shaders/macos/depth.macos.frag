#version 410

in VSOUT
{
    float depth;
}fs_in;

out vec4 frag_out;

void main()
{
    frag_out = vec4(fs_in.depth, fs_in.depth, fs_in.depth, fs_in.depth);
}
