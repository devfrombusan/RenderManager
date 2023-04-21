#include "../RenderManager/RenderManager.hpp"

#ifndef RENDERMANAGERTEST_SAMPLESCENE_HPP
#define RENDERMANAGERTEST_SAMPLESCENE_HPP

class SampleScene{
public:
    SampleScene();
    ~SampleScene();

    void SetLayerCount(int totalLayerCount, int width, int height, float ortho);
    void Update(JNIEnv* env, jobject mainActivity, float deltaTime);

    Object* object;
    int width, height;
};

extern SampleScene* sampleScene;

#endif //RENDERMANAGERTEST_SAMPLESCENE_HPP
