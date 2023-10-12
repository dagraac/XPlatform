﻿#include "InitializeOnLoadScene.h"
#include "Node.h"
#include "Shader.h"


//namespace XPlatform
//{
//	const char g_VertexShader[256] = R"(
//		void main() {
//			gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
//		}
//	)";
//}

/////////////////////////////////////////////////////////////////////////////
// @ 생성됨.
/////////////////////////////////////////////////////////////////////////////
void InitializeOnLoadScene::OnCreate()
{
	Base::OnCreate();

	auto shader = CreateRef<Shader>();
	//shader->SetProperty();
}

/////////////////////////////////////////////////////////////////////////////
// @ 파괴됨.
/////////////////////////////////////////////////////////////////////////////
void InitializeOnLoadScene::OnDestroy()
{
	Base::OnDestroy();
}

/////////////////////////////////////////////////////////////////////////////
// @ 일시정지됨.
/////////////////////////////////////////////////////////////////////////////
void InitializeOnLoadScene::OnPause()
{
	Base::OnPause();
}

/////////////////////////////////////////////////////////////////////////////
// @ 재개됨.
/////////////////////////////////////////////////////////////////////////////
void InitializeOnLoadScene::OnResume()
{
	Base::OnResume();
}

/////////////////////////////////////////////////////////////////////////////
// @ 갱신됨.
/////////////////////////////////////////////////////////////////////////////
void InitializeOnLoadScene::OnUpdate(float deltaTime)
{
	Base::OnUpdate(deltaTime);
}

/////////////////////////////////////////////////////////////////////////////
// @ 출력됨.
/////////////////////////////////////////////////////////////////////////////
void InitializeOnLoadScene::OnRender(Ref<IGL> gl)
{
	Base::OnRender(gl);

	// 사각형 출력.
	gl->Clear(IGL::AttribMask::GL_COLOR_BUFFER_BIT);
	gl->LoadIdentity();

	// glDrawArrays

	gl->Begin(IGL::BeginMode::GL_QUADS);
	gl->Vertex3f(-0.5f, -0.5f, 0.0f); // 좌하.
	gl->Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	gl->Vertex3f(0.5f, -0.5f, 0.0f); // 우하.
	gl->Color4f(1.0f, 0.0f, 1.0f, 1.0f);
	gl->Vertex3f(0.5f, 0.5f, 0.0f); // 우상.
	gl->Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	gl->Vertex3f(-0.5f, 0.5f, 0.0f); // 좌상.
	gl->Color4f(1.0f, 1.0f, 0.0f, 1.0f);
	gl->End();
	gl->Flush();
}
