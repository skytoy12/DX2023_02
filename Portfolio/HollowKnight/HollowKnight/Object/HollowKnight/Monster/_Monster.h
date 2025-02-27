#pragma once
class Monster
{
	friend class Player;
public :

	enum MonsterType
	{
		BOSS,
		FLY,
		JUMP,
		RUSH,
		NONE
	};

	Monster();
	virtual ~Monster() {}

	virtual void Update();
	virtual void Render();

	virtual void PostRender() abstract;
	virtual void Attack() abstract;

	virtual void targetHit(shared_ptr<Collider> col);
	virtual void ExtraHit(shared_ptr<Collider> hitcol, shared_ptr<Collider> dircol);
	virtual void Hitted(shared_ptr<Collider> col);
	virtual void BulletHitted(shared_ptr<Collider> col);
	virtual void HitKnockBack(shared_ptr<Collider> col);
	virtual void UnbeatableToIdle();

	void WeaponActive();

	void SetRGB(float R, float G, float B);

	void EffectSetting();

	void Gravity(shared_ptr<Collider> col);

	void HighGravity(shared_ptr<Collider> col);

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);
protected :

	MonsterType _monsterType = NONE;

	int _hp = 0;
	float _jumpPower = 0.0f;
	float _speed = 150.0f;
	float _KBspeed = 150.0f;
	float _unbeatableTime = 0.0f; // 몬스터 피격시 잠시 무적이 되는 시간
	Vector2 _dir = { 1,0 };
	Vector2 _KBdir = { 1,0 };

	bool _isAlive = true;
	bool _isActive = false;
	bool _isLeft = false;
	bool _isUnbeatable = false;


	//weak_ptr<Transform> _target;
	weak_ptr<class Player> _targetPlayer;

	shared_ptr<Transform> _transform;
	shared_ptr<Collider> _col;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<MonsterBuffer> _monsterBuffer;
};

