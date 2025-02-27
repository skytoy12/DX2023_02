﻿// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <memory>
#include <functional>
#include <wrl/client.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include <d2d1_2.h>
#include <dwrite.h>

#pragma <d2d1.lib>
#pragma <dwrite.lib>
// DirectXTex
#include "../DirectTex/DirectXTex.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

// Imgui
#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_win32.h"
#include "../ImGUI/imgui_impl_dx11.h"

// FMOD
#include "Library/FMOD/inc/fmod.hpp"
#pragma comment(lib, "Library/FMOD/fmod_vc.lib")

using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;

//Types
#include "Types.h"

// Framework
#include "Framework/Device/Device.h"

// Math
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"
#include "Framework/Math/MyMath.h"

// Utility
#include "Framework/Utility/InputManager.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/tinyxml2.h"
#include "Framework/Utility/Sound.h"
#include "Framework/Utility/BinaryWriter.h"
#include "Framework/Utility/BinaryReader.h"

//Render
#include "Framework/Render/ConstantBuffer.h"
#include "Framework/Render/GlobalBuffer.h"
#include "Framework/Render/VertexLayOut.h"
#include "Framework/Render/VertexBuffer.h"
#include "Framework/Render/IndexBuffer.h"
#include "Framework/Render/Shader.h"
#include "Framework/Render/VertexShader.h"
#include "Framework/Render/PixelShader.h"
#include "Framework/Render/ShaderManager.h"
#include "Framework/Render/RenderTarget.h"

//Camera
#include "Framework/Camera/Camera.h"

//Collider
#include "Framework/Collider/Collider.h"
#include "Framework/Collider/RectCollider.h"
#include "Framework/Collider/CircleCollider.h"


//TextureMapping
#include "Framework/TextureMapping/SRV.h"
#include "Framework/TextureMapping/SRVManager.h"
#include "Framework/TextureMapping/SamplerState.h"
#include "Framework/TextureMapping/BlendState.h"
#include "Framework/TextureMapping/StateManager.h"

// Animation
#include "Framework/Animation/Action.h"

//Object
#include "Object/Bagic/Quad.h"
#include "Object/Bagic/Sprite.h"
#include "Object/Bagic/Effect.h"
#include "Object/Bagic/EffectManager.h"
#include "Object/SolarSystem/Planet.h"
#include "Object/Dungreed/DungreedBullet.h"
#include "Object/Dungreed/Dungreed.h"
#include "Object/Dungreed/Dun_Player_Advanced.h"
#include "Object/Dungreed/DungreedBoss.h"



// UI
#include "Object/UI/Button.h"

// Scene
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"

//Program
#include "Program/Program.h"

extern HWND hWnd;