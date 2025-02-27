#pragma once
class GameScene1 : public Scene
{
public:
	GameScene1();
	~GameScene1();


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

	bool _isOn = true;
	bool _load = true;

	shared_ptr<Player> _player;

	vector<shared_ptr<Wall>> _walls;

	shared_ptr<RushMonster> _rMon;

	shared_ptr<CircleCollider> _Potal;

	vector<shared_ptr<BrickImage>> _images;

	shared_ptr<BackGround> _backGround;
	shared_ptr<BackGround> _backGround1;
};


