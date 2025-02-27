#pragma once
class GameScene2 : public Scene
{
public:
	GameScene2();
	~GameScene2();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void PreRender() override;

	void CreateMap();

	void MoveCol();

	void DashCut();

	void Save();
	void Load();

	void BrickLoad();

private:
	float _scale = 0.75f;
	int _colNum = 0;

	bool _start = true;
	bool _isOn = true;
	shared_ptr<Player> _player;

	vector<shared_ptr<FlyMonster>> _flies;

	shared_ptr<RushMonster> _RMon;
	shared_ptr<JumpMonster> _JMon;

	shared_ptr<CircleCollider> _Potal;

	vector<shared_ptr<Wall>> _walls;
	vector<shared_ptr<Stool>> _stools;

	vector<shared_ptr<BrickImage>> _images;

	shared_ptr<BackGround> _backGround;
	shared_ptr<BackGround> _backGround1;
	shared_ptr<BackGround> _backGround2;
	shared_ptr<BackGround> _backGround3;

};

