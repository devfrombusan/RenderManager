#include "BdtInfo.h"
#include "../Tools/Tools.hpp"

#ifndef SHADER_HPP
#define SHADER_HPP

namespace Shader {

    class UniformData {
    public:
        UniformData();
        ~UniformData();

        vec::mat4 ortho;
        BDTImage *texture;
    };

    class Shader {
    public:
        Shader();
        virtual ~Shader();

        void Activate();
        void LoadUniform();

        virtual const GLchar *GetVertexShaderCode() = 0;
        virtual const GLchar *GetFragmentShaderCode() = 0;

        GLuint vao;
        GLuint positionVbo, texcoordVbo, colorVbo;
        GLuint texture;
        GLuint shaderProgram;
        UniformData *uniformData;
        bool activated;

    private:
        void CreateShader();
        void CreateBuffer();
    };

    class Default : public Shader{
    public:
        virtual const GLchar *GetVertexShaderCode();
        virtual const GLchar *GetFragmentShaderCode();
    };
}

// 여기서 원하는 Shader를 재정의 한다

#endif //SHADER_HPP
