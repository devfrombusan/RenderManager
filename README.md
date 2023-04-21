OpenGL 그래픽 API와 Android Studio를 활용하여 앱 제작시 그래픽스 API활용을 쉽게 할 수 있도록 고안된 프로젝트 입니다
<br/>
<br/>
제작기간은 약 1년 6개월 입니다

<br/>
<br/>

1. RenderManagerTest/app/src/main/cpp/Jni
- https://github.com/devfrombusan/RenderManager/tree/main/RenderManagerTest/app/src/main/cpp/Jni
- 안드로이드 환경에서 Java와 통신하기 위한 코드가 작성되어 있습니다

2. RenderManagerTest/app/src/main/cpp/RenderManager
- https://github.com/devfrombusan/RenderManager/tree/main/RenderManagerTest/app/src/main/cpp/RenderManager
- OpenGL를 활용하여 최적화 랜더링을 구현하도록 설계된 코드가 작성되어 있습니다

3. RenderManagerTest/app/src/main/cpp/SampleScene
- https://github.com/devfrombusan/RenderManager/tree/main/RenderManagerTest/app/src/main/cpp/SampleScene
- 간단하게 RenderManager 클래스를 활용하여 랜더링을 테스트를 진행합니다

4. RenderManagerTest/app/src/main/cpp/Tools
- https://github.com/devfrombusan/RenderManager/tree/main/RenderManagerTest/app/src/main/cpp/Tools
- 수학 연산에 사용된 함수들을 정의하였습니다

5. RenderManagerTest\app\src\main\java\com\example\android\RenderManagerTest
-
- 안드로이드 환경에서 수행해야 할 Java코드가 작성되어 있습니다


<br/>
<br/>

실제로 현 프로젝트를 활용하여 간단한 게임을 구현하였습니다 (구글 API활용 등) 단순 테스트 용으로 만든 게임입니다
<br/>

https://play.google.com/store/apps/details?id=com.devnim.android.changecolorspuzzle
<br/>
RenderManager의 Layer 클래스를 기반으로 텍스처아틀라스 하나로 실제 드로우콜이 한번만 일어나는지 테스트 하였습니다
<br/>
<br/>
https://play.google.com/store/apps/details?id=com.devnim.android.dopong_free
<br/>
RenderManager의 Collider 클래스를 기반으로 충돌 테스트를 진행하였으며 코사인을 활용한 진자운동을 공의 탄력성에 적용하였습니다
