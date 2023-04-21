#include "Mesh.hpp"

Shader::UniformData::UniformData() {

    texture = nullptr;
    ortho = vec::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
}

Shader::UniformData::~UniformData() {

}

Shader::Shader::Shader() {

    vao = 0;
    positionVbo = 0;
    texcoordVbo = 0;
    colorVbo = 0;
    shaderProgram = 0;
    texture = 0;
    activated = false;
    uniformData = nullptr;
}

Shader::Shader::~Shader() {

    if (glIsVertexArray(vao)) glDeleteVertexArrays(1, &vao);
    if (glIsBuffer(positionVbo)) glDeleteBuffers(1, &positionVbo);
    if (glIsBuffer(texcoordVbo)) glDeleteBuffers(1, &texcoordVbo);
    if (glIsBuffer(colorVbo)) glDeleteBuffers(1, &colorVbo);
    if (glIsProgram(shaderProgram)) glDeleteProgram(shaderProgram);
    if (glIsTexture(texture)) glDeleteTextures(1, &texture);
}

void Shader::Shader::Activate() {
    CreateShader();
    CreateBuffer();
}

void Shader::Shader::CreateShader() {

    const GLchar *vertexShaderCode = GetVertexShaderCode();
    const GLchar *fragmentShaderCode = GetFragmentShaderCode();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);

    GLint result;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
}

void Shader::Shader::CreateBuffer() {

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &positionVbo);
    glBindBuffer(GL_ARRAY_BUFFER, positionVbo);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    if (uniformData->texture) {

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, uniformData->texture->width,
                     uniformData->texture->height, 0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE, uniformData->texture->bits);

        glGenerateMipmap(GL_TEXTURE_2D);

        delete uniformData->texture;
        uniformData->texture = nullptr;
    }

    glGenBuffers(1, &texcoordVbo);
    glBindBuffer(GL_ARRAY_BUFFER, texcoordVbo);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &colorVbo);
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

}

void Shader::Shader::LoadUniform() {

    GLint perspective = glGetUniformLocation(shaderProgram, "ortho");
    glUniformMatrix4fv(perspective, 1, GL_FALSE, uniformData->ortho);

    glBindTexture(GL_TEXTURE_2D, texture);
    GLint s = glGetUniformLocation(shaderProgram, "s");
    glUniform1i(s, 0);
}

const GLchar * Shader::Default::GetVertexShaderCode() {

    return "#version 300 es\n"
           "layout(location = 0) in vec3 positionAttribute;"
           "layout(location = 1) in vec2 texAttribute;"
           "layout(location = 2) in vec4 colorAttribute;"
           "out vec2 t;"
           "out vec4 out_color;"
           "uniform mat4 ortho;"
           "void main()"
           "{"
           "gl_Position = ortho * vec4(positionAttribute, 1.0);"
           "t = texAttribute;"
           "out_color = colorAttribute;"
           "}";

}

const GLchar * Shader::Default::GetFragmentShaderCode() {

    return "#version 300 es\n"
           "precision mediump float;\n"
           "in vec2 t;"
           "in vec4 out_color;"
           "out vec4 frag_color;"
           "uniform sampler2D s;"
           "void main(){"
           "frag_color = texture(s,t) * out_color;"
           "}";
}