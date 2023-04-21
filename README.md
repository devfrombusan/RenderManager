OpenGL 그래픽 API와 Android Studio를 활용하여 앱 제작시 그래픽스 API활용을 쉽게 할 수 있도록 고안된 프로젝트 입니다
<br/>
<br/>
혼자 학습용으로 개발하였으며 제작기간은 약 1년 6개월 입니다

<br/>
<br/>

1. RenderManagerTest/app/src/main/cpp/RenderManager
- https://github.com/devfrombusan/RenderManager/tree/main/RenderManagerTest/app/src/main/cpp/RenderManager
- OpenGL를 활용하여 최적화 랜더링을 구현하도록 설계된 코드가 작성되어 있습니다

2. RenderManagerTest/app/src/main/cpp/Jni
- https://github.com/devfrombusan/RenderManager/tree/main/RenderManagerTest/app/src/main/cpp/Jni
- 안드로이드 환경에서 Java와 통신하기 위한 코드가 작성되어 있습니다

3. RenderManagerTest/app/src/main/cpp/SampleScene
- https://github.com/devfrombusan/RenderManager/tree/main/RenderManagerTest/app/src/main/cpp/SampleScene
- 간단하게 RenderManager 클래스를 활용하여 랜더링을 테스트를 진행합니다

4. RenderManagerTest/app/src/main/cpp/Tools
- https://github.com/devfrombusan/RenderManager/tree/main/RenderManagerTest/app/src/main/cpp/Tools
- 수학 연산에 사용된 함수들을 정의하였습니다

5. RenderManagerTest\app\src\main\java\com\example\android\RenderManagerTest
- https://github.com/devfrombusan/RenderManager/tree/main/RenderManagerTest/app/src/main/java/com/example/android/RenderManagerTest
- 안드로이드 환경에서 수행해야 할 Java코드가 작성되어 있습니다


<br/>
<br/>

RenderManager는 다양한 클래스로 구성되어 있습니다
<br/>
1. RenderManager
- 메쉬와 블랜딩, 스텐실등 랜더링에 관련된 모든 부분을 담당합니다
- Java의 랜더링 스레드와 연결되어 독립적으로 작동합니다
- Java의 업데이트 스레드와 랜더 스레드와 서로 통신하여 null ptr 참조를 방지합니다

2. Layer
- 한 번 수행되는 드로우콜을 담당합니다
- 같은 Layer에 속한 메쉬는 한 번의 드로우콜에 속하게 됩니다
- 드로우콜이 아닌 OpenGL의 블랜딩과 스탠실을 담당할 수 있습니다(해당 Layer는 드로우콜을 발생시키지 않습니다)
- 가지고 있는 모든 메쉬를 n * 1 벡터로 변환한 후 연산을 수행합니다
- 변환된 벡터는 각각 코사인 유사도를 사용해서 충돌 연산을 수행할 수 있습니다
- 유니티의 Material과 유사한 동작을 합니다. 유니티에서 사용되는 번거로운 sharedMaterial을 설정하지 않습니다
- 4개의 버텍스를 담도록 최적화 되어 있기 때문에 drawElements가 아닌 drawArrays를 사용합니다
- Layer가 가진 orthographic은 각 메쉬를 해당 orthographic 값으로 그려지도록 합니다(10.0f의 경우 그 범위를 기준으로 그림)

3. Object
- 메쉬 데이터를 담고 실제로 업데이트 스레드와 상호작용을 합니다
- 업데이트는 Object클래스와 상호작용을 하고 렌더러 스레드에 업데이트를 요청합니다
- 요청받는 렌더러는 Object가 가지고 있는 메쉬데이터 연산을 시작 합니다

4. Mesh
- 실제 버텍스, 텍스처 좌표, 컬러 데이터를 가지고 있는 클래스 입니다
- 업데이트 스레드에서는 직접 접근할 수 없으며 오직 Layer 클래스가 이를 담당합니다
- Mesh가 표현하는 텍스쳐는 Layer가 가지고 있으며 Layer의 Shader아래 표현이 됩니다

5. Shader
- 실제 버텍스, 텍스처, 컬러 데이터를 바인딩하여 GLSL를 설정하고 사용해서 그리도록 합니다
- 한 Layer당 한 Shader를 가지고 있습니다
- 유니티의 Shader와 같은 동작을 합니다.
- 구현 되지는 않았지만 재정의된 Shader를 만들어서 원하는 효과를 줄 수 있습니다
- 블랜딩과 같은 요소를 담당하는 Layer는 Shader를 가지고 있지 않습니다

6. Collider
- AABB, OBB의 벽뚫기를 방지하기 위해 연구된 충돌연산을 담당하는 클래스입니다
- 벡터연산을 사용해서 nPn 연산을 최소화 하고 timeDelta(deltaTime)와 같은 프레임연산에 적합하도록 계산됩니다
- UDP방식에서 발생하는 지연현상에도 시간에 상관없이 단 한번만 연산을 수행합니다
<br/>
<br/>

실제로 현 프로젝트를 활용하여 간단한 게임을 구현하였습니다. 단순 테스트 용으로 만든 게임입니다. 사용된 에셋과 아이디어는 지인들의 참고로 제작되었습니다.
<br/>

https://play.google.com/store/apps/details?id=com.devnim.android.changecolorspuzzle
<br/>
RenderManager의 Layer 클래스를 기반으로 텍스처아틀라스 하나로 실제 드로우콜이 한번만 일어나는지 테스트 하였습니다
<br/>
<br/>
https://play.google.com/store/apps/details?id=com.devnim.android.dopong_free
<br/>
RenderManager의 Collider 클래스를 기반으로 충돌 테스트를 진행하였으며 코사인을 활용한 진자운동을 공의 탄력성에 적용하였습니다
<br/>
<br/>
