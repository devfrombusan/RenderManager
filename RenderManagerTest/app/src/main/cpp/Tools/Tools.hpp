#include "Vec.hpp"
#include <time.h>
#include <cstdlib>

#ifndef TOOLS_HPP
#define TOOLS_HPP

using namespace std;

namespace Tools{

    inline float Distance(float x1, float y1, float x2, float y2) {

        float result = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
        return result;
    }

    inline float Distance(vec::vec2 vector){

        return sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]));
    }

    inline float Distance(vec::vec2 origin, vec::vec2 destination){

        return sqrt(((destination[0] - origin[0]) * (destination[0] - origin[0])) + ((destination[1] - origin[1]) * (destination[1] - origin[1])));
    }

    inline int Distance(int x1, int y1, int x2, int y2){
        int distance[2];

        distance[0] = abs(x2 - x1);
        distance[1] = abs(y2 - y1);

        return distance[0] + distance[1];
    }

    inline float Angle(float x1, float y1, float x2, float y2) {

        float result = atan2(y2 - y1, x2 - x1) * 57.295780f;
        if (result < 0) result = 360.0f + result;
        return result;
    }
    inline float Angle(vec::vec2 origin, vec::vec2 destination) {

        float result = atan2(destination[1] - origin[1], destination[0] - origin[0]) * 57.295780f;
        if (result < 0) result = 360.0f + result;
        return result;
    }
    inline float Angle(vec::vec2 normal) {

        float result = atan2(normal[1], normal[0]) * 57.295780f;
        if (result < 0) result = 360.0f + result;
        return result;
    }
    inline vec::vec2 Normalization(float angle){
        return vec::vec2(cos(angle * PI / 180.0f), sin(angle * PI / 180.0f));
    }

    inline vec::vec2 Normalization(float originX, float originY, float pointX, float pointY) {

        float vectorX = pointX - originX;
        float vectorY = pointY - originY;

        float length = sqrtf((vectorX * vectorX) + (vectorY * vectorY));

        vec::vec2 result(vectorX / length, vectorY / length);

        if(length <= 0.0f) result = vec::vec2(1.0f, 0.0f);

        return result;
    }
    inline vec::vec2 Normalization(vec::vec2 origin) {

        float length = sqrtf((origin[0] * origin[0]) + (origin[1] * origin[1]));

        vec::vec2 result(origin[0] / length, origin[1] / length);

        if(length <= 0.0f) result = vec::vec2(1.0f, 0.0f);

        return result;
    }
    inline vec::vec2 Normalization(vec::vec2 origin, vec::vec2 points) {

        float vectorX = points[0] - origin[0];
        float vectorY = points[1] - origin[1];

        float length = sqrtf((vectorX * vectorX) + (vectorY * vectorY));

        vec::vec2 result(vectorX / length, vectorY / length);

        if(length <= 0.0f) result = vec::vec2(1.0f, 0.0f);

        return result;
    }
    inline vec::vec2 NormalVector(vec::vec2 origin, vec::vec2 points) {

        float RADIAN = atan2(points[1] - origin[1], points[0] - origin[0]) + 1.570796;
        vec::vec2 result(cos(RADIAN), sin(RADIAN));

        return result;
    }
    inline vec::vec2 ProjectionVector(vec::vec2 normalVector, float velocity){

        vec::vec2 result = vec::vec2(normalVector[0] * velocity, normalVector[1] * velocity);

        return result;
    }
    inline vec::vec2 AdditionVector(vec::vec2 origin, vec::vec2 destination){

        vec::vec2 result(destination[0] + origin[0], destination[1] + origin[1]);

        return result;
    }
    inline vec::vec2 SubtractionVector(vec::vec2 origin, vec::vec2 destination){

        vec::vec2 result(destination[0] - origin[0], destination[1] - origin[1]);

        return result;
    }
    inline vec::vec2 ReverseVector(vec::vec2 origin){

        vec::vec2 result(-origin[0], -origin[1]);

        return result;
    }
    inline float Dot(vec::vec2 points1, vec::vec2 points2) {

        float result = (points1[0] * points2[0]) + (points1[1] * points2[1]);

        return result;
    }
    inline float YAxisSymmetryAngle(float angle){
        float X = -cos(angle * 0.017453f);
        float Y = sin(angle * 0.017453f);

        float result = atan2(Y, X) * 57.295780f;

        return result;
    }
    inline float XAxisSymmetryAngle(float angle){
        float X = cos(angle * 0.017453f);
        float Y = -sin(angle * 0.017453f);

        float result = atan2(Y, X) * 57.295780f;

        return result;
    }
    inline int FrameIndex(float frameValue, int section, float speed = 1.0f){

        int result = frameValue * section * speed;
        if(result >= section) result = 0;

        return result;
    }

    inline float LeftTimeValue(float frameValue, int section, float speed = 1.0f){

        float result = frameValue * section * speed;
        int SECTION = result + 1;

        return result = ((float)SECTION - result) / (section * speed);
    }

    inline unsigned int RandomNumber() {

        return ((rand() + 1) * (rand() + 1) * (rand() % 2 + 1)* (rand() % 2 + 1)) + (rand() % 2);
    }

    inline bool Probability(unsigned int numerator, unsigned int denominator) {

        if (denominator > 4294967295) denominator = 4294967295;
        if (denominator <= 0) denominator = 1;
        if (numerator <= 0) numerator = 1;

        unsigned int num = (RandomNumber() ^ RandomNumber() ^ RandomNumber() ^ RandomNumber() ^
                            RandomNumber()) % denominator;

        if (num < numerator) return true;
        else return false;
    }

    inline int ConvertFloatToInt(float value) {
        char byte[4];

        unsigned int result;

        byte[0] = (char)(*((unsigned int*)&value) >> 24);
        byte[1] = (char)(*((unsigned int*)&value) >> 16);
        byte[2] = (char)(*((unsigned int*)&value) >> 8);
        byte[3] = (char)(*((unsigned int*)&value));

        result = (((unsigned int)byte[0] & 0xFF) << 24);
        result += (((unsigned int)byte[1] & 0xFF) << 16);
        result += (((unsigned int)byte[2] & 0xFF) << 8);
        result += (((unsigned int)byte[3] & 0xFF));;

        return result;
    }

    inline float ConvertIntToFloat(int value) {

        float result = *((float*)&value);

        return result;
    }

    inline int EncryptInt(int value, int key){
        return value ^ key;
    }

    inline int IncreaseEncryptedInt(int value1, int value2, int key){
        return ((value1 ^ key) + value2) ^ key;
    }

    inline float EncryptFloat(float value, int key){
        return Tools::ConvertIntToFloat(Tools::ConvertFloatToInt(value) ^ key);
    }

    inline float IncreaseEncryptedFloat(float value1, float value2, int key){
        return Tools::ConvertIntToFloat(Tools::ConvertFloatToInt(
                Tools::ConvertIntToFloat(
                        Tools::ConvertFloatToInt(value1) ^ key) + value2) ^
                                        key);
    }

    inline vec::vec3 CalColor(int R, int G, int B){
        if(R < 0) R = 0;
        if(R > 255) R = 255;

        if(G < 0) G = 0;
        if(G > 255) G = 255;

        if(B < 0) B = 0;
        if(B > 255) B = 255;

        return vec::vec3((float)R / (float)255, (float)G / (float)255, (float)B / (float)255);
    }

}

#endif //TOOLS_HPP
