#version 330

in vec3 vertexColor;
in vec2 texcoord;

uniform sampler2D texBuffer;
uniform vec2 offset;

out vec4 color;
void main() {
    color = texture(texBuffer, texcoord+offset);
}