#include "framework.h"
#include "BossScene.h"

BossScene::BossScene()
{
	_player = make_shared<Player>();
	_boss = make_shared<Boss>();
	_startButton = make_shared<CircleCollider>(50);
	_startCollider = make_shared<RectCollider>(Vector2(50, 500));

	_endCollider = make_shared<RectCollider>(Vector2(7500, 300));

	_backGround = make_shared<BackGround>(L"Resource/UI/RealRealBackGround.png", Vector2(3840, 2160));
	_backGround1 = make_shared<BackGround>(L"Resource/UI/RealRealBackGround.png", Vector2(3840, 2160));
	_backGround2 = make_shared<BackGround>(L"Resource/UI/RealRealBackGround.png", Vector2(3840, 2160));


	for (int i = 0; i < 100; i++)
	{
		shared_ptr<BrickImage> image = make_shared<BrickImage>(L"Resource/Deco/44.png", Vector2(275.0f, 273.0f));
		image->_isActive = false;
		_images.push_back(image);
	}
	
	for (int i = 0; i < 5; i++)
	{
		shared_ptr<Wall> wall = make_shared<Wall>(Vector2(50, 50));
		_walls.push_back(wall);
	}


	for (auto wall : _walls)
	{
		wall->SetTarget(_player);
	}

	_boss->SetPlayer(_player);

	//CAMERA->SetTarget(nullptr);
	//CAMERA->SetTarget(_player->GetTransform());

	_player->SetPosition(Vector2(-3400,+ 150));
	_boss->SetPosition(Vector2(0, 500));
	_startButton->SetPosition(Vector2(-1113, -64));
	_startCollider->SetPosition(Vector2(-1373, 116));
	_endCollider->SetPosition(Vector2(0, -2250));

	_backGround->SetPosition(Vector2(-1887, 500));
	_backGround1->SetPosition(Vector2(200, 500));
	_backGround2->SetPosition(Vector2(200, -1500));

	CreateMap();
	BrickLoad();
}

BossScene::~BossScene()
{
}

void BossScene::Update()
{
	if (KEY_DOWN('Q'))
		_isEnd = !_isEnd;
	_player->Update();
	_boss->Update();
	_startButton->Update();
	_endCollider->Update();

	_backGround->Update();
	_backGround1->Update();
	_backGround2->Update();



	if (_isEnd == false)
	{
		CAMERA->SetRightTop(Vector2(+1700, +1100));
		CAMERA->SetLeftBottom(Vector2(-2600, -180));
	}

	if (_isEnd == true)
	{
		CAMERA->SetRightTop(Vector2(+500, +1100));
		CAMERA->SetLeftBottom(Vector2(-800, -2180));
	}



	if (_start == true)
	{
		_start = false;
		Load();
		CAMERA->SetTarget(_player->GetTransform());
	}

	if (_boss->_landBreak == true)
		_isEnd = true;

	if (_startActive == false)
	{
		_startCollider->Update();
		_startCollider->Block(_player->GetCollider());
	}

	if (_endCollider->Block(_player->GetCollider()))
		_player->SetIsJump(false);
	_endCollider->Block(RECT(_boss->GetGravityCollider()));

	if (_player->GetCollider()->IsCollision(_startButton) && _startActive == true)
	{
		_boss->SetStart(false);
		_startActive = false;
	}

	for (auto image : _images)
		image->Update();

	CAMERA->SetScale(Vector2(_scale, _scale));
	MoveCol();

	for (int i = 1; i < 3; i++)
	{
		_walls[i]->Update();
	}

	if (_isEnd == true)
	{
		_walls[3]->Update();
		_walls[4]->Update();
	}

	if (_isEnd == false)
	{
		_walls[0]->Update();
	}

	for (auto wall : _walls)
	{
		if (_isEnd == true)
			return;
		wall->BlockR(RECT(_boss->GetGravityCollider()));
	}

	if (_isEnd == true)
	{
		for(int i = 1; i < 5; i++)
			_walls[i]->BlockR(RECT(_boss->GetGravityCollider()));
	}

	DashCut();

	if (KEY_UP(VK_UP))
		_colNum += 1;

	if (KEY_UP(VK_DOWN))
		_colNum -= 1;
}

void BossScene::Render()
{
	_backGround->Render();
	_backGround1->Render();
	_backGround2->Render();

	_boss->Render();
	_player->Render();
	_startButton->Render();
	_endCollider->Render();
	if (_startActive == false)
		_startCollider->Render();

	for (auto image : _images)
		image->Render();

	for (int i = 1; i < 3; i++)
	{
		_walls[i]->Render();
	}

	if (_isEnd == true)
	{
		_walls[3]->Render();
		_walls[4]->Render();
		_images[5]->_isActive = false;
		_images[52]->_isActive = false;
	}

	if (_isEnd == false)
	{
		_walls[0]->Render();
	}
}

void BossScene::PostRender()
{
	_player->PostRender();

	ImGui::SliderFloat("Scale.x", (float*)&_scale, 0.1f, 2.0f);
	ImGui::Text("colNum : %d", _colNum);
	ImGui::Text("_hp : %d", _boss->GetHead()->GetHP());
	ImGui::Text("land : %.1f, %.1f", _boss->GetLandPoint().x, _boss->GetLandPoint().y);
}

void BossScene::PreRender()
{
}

void BossScene::CreateMap()
{
	_walls[0]->SetPosition(Vector2(+   0, - 250));
	_walls[1]->SetPosition(Vector2(-2000, + 600));
	_walls[2]->SetPosition(Vector2(+1500, + 600));
	_walls[3]->SetPosition(Vector2(- 1035, - 250));
	_walls[4]->SetPosition(Vector2(+ 1035, - 250));


	_walls[0]->SetScale(Vector2(150,  6));
	_walls[1]->SetScale(Vector2( 30, 10));
	_walls[2]->SetScale(Vector2( 15, 50));
	_walls[3]->SetScale(Vector2( 30, 6));
	_walls[4]->SetScale(Vector2( 30, 6));
}

void BossScene::MoveCol()
{
	if (KEY_PRESS(VK_CONTROL))
	{
		if (KEY_PRESS(VK_LBUTTON))
		{
			_walls[_colNum]->SetPosition(W_MOUSE_POS);
		}
	}
}

void BossScene::DashCut()
{
	for (auto wall : _walls)
	{
		_player->CutDashW(wall);
	}


	if (KEY_DOWN(VK_SHIFT))
	{
		_player->Dash();
	}


}

void BossScene::Save()
{
	PlayerInfo playerInfo;


	int Php = _player->GetHP();
	int Pmp = _player->GetMP();

	playerInfo.hp = Php;
	playerInfo.mp = Pmp;

	BinaryWriter writer = BinaryWriter(L"Info/HpMp.save");
	writer.String("PlayerInfo");
	writer.UInt(sizeof(playerInfo));
	writer.Byte(&playerInfo, sizeof(playerInfo));
}

void BossScene::Load()
{
	PlayerInfo playerInfo;

	BinaryReader reader = BinaryReader(L"Info/HpMp.save");
	string infoName = reader.String();

	if (infoName == "PlayerInfo")
	{
		UINT size = reader.UInt();

		void* ptr = &playerInfo;
		reader.Byte(&ptr, size);
	}

	_player->SetHP(playerInfo.hp);
	_player->SetMP(playerInfo.mp);
}

void BossScene::BrickLoad()
{
	vector<BrickInfo> brickInfo;

	BinaryReader reader = BinaryReader(L"Info/BrickInfoGameScene4.BSW");
	string infoName = reader.String();

	if (infoName == "GameScene4")
	{
		UINT size = reader.UInt();
		brickInfo.resize(size);

		void* ptr = brickInfo.data();
		reader.Byte(&ptr, size * sizeof(BrickInfo));
	}

	for (int i = 0; i < brickInfo.size(); i++)
	{
		if (i >= _images.size() - 1)
			break;

		_images[i]->SetPosition(brickInfo[i].pos);
		_images[i]->SetScale(brickInfo[i].Scale);
		_images[i]->_isActive = true;
	}

	BinaryReader data(L"Info/GameScene4.image");

	for (shared_ptr<BrickImage> image : _images)
	{
		image->SetSRV(data.WString());
	}
}
