#version 330 core

in vec2 outPos;
out vec4 FragOut;

void main()
{
    if (distance(outPos, vec2(0, 0)) < .2)
    {
        if (distance(vec2(outPos.x, outPos.y * .3), vec2(0, 0)) < .05)
        {
            FragOut = vec4(0, 0, 0, 1);
            return;
        }
        FragOut = vec4(1);
        return;
    }
    FragOut = vec4(0.153, 0.588, 0.337, 1.0); // vanessas hand-picked color :))
}
