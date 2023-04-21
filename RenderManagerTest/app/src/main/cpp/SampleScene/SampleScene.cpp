#include "SampleScene.hpp"

using namespace std;

SampleScene::SampleScene() {

    SetLayerCount(1, 100, 100, 15.0f);

    /*

     SetLayerCount(int1, int2, int3, float4);

     1. 레이어 개수
     2. 가로 개수
     3. 세로 개수
     4. 표시할 월드 좌표 길이

     레이어가 많아질수록 프레임이 떨어집니다.

     */
}

SampleScene::~SampleScene() {

    delete[] object;
}

void SampleScene::Update(JNIEnv *env, jobject mainActivity, float deltaTime) {

    for(int y = 0; y < height; y++) for(int x = 0; x < width; x++){
             object[width * y + x].Rotation(90.0f * deltaTime)->ConvertMatrix();
        }
}

void SampleScene::SetLayerCount(int totalLayerCount, int width, int height, float ortho) {

    this->width = width;
    this->height = height;

    float distance = 1.5f;

    int totalMeshCount = width * height;

    this->object = new Object[totalMeshCount];

    int meshCount = totalMeshCount / totalLayerCount;

    for(int i = 0; i < totalLayerCount; i++){

        renderManager->CreateMeshLayer(i, meshCount, "whiteBox.bdt");
        renderManager->SetOrthographic(i, ortho, Device::windowWidth, Device::windowHeight, true);

        for(int j = 0; j < meshCount; j++) renderManager->CreateObject(i, &object[meshCount * i + j]);

    }

    for(int y = 0; y < height; y++) for(int x = 0; x < width; x++){

        renderManager->CreateObject(y, &object[width * y + x])
        ->SetVertexData(-0.5f, 0.5f, -0.5f, 0.5f)
        ->SetColorData(1.0f, 0.75f, 0.5f, 1.0f)
        ->SetPosition(-((float)width * 0.5f * distance) + (x * distance), -((float)height * 0.5f * distance) + (y * distance))
        ->Visible();
    }
}

SampleScene *sampleScene = nullptr;
