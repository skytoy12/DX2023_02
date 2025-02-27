#pragma once
class BossHead;

class Boss : public Monster
{
public :
	enum State_Boss
	{
		IDLE,
		TURN,
		ATTACKREADY,
		ATTACK,
		ATTACKFINISH,
		JUMPREADY,
		JUMP,
		JUMPATTACK,
		BACKSTEP,
		JUMPTOIDLE,
		GROGYATTACK,
		GROGYSTART,
		GROGYROLLING,
		GROGY,
		GROGYHEAD,
		LAST
	};

	struct WeaponMove
	{
		float _weaponAngle;
		bool _isPositive;
		int _count;
		float _speed;
	};

	Boss();
	~Boss();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Attack() override;

	virtual void Hitted(shared_ptr<Collider> col) override;
	void RealHitted();


	float Angle(float angle) { return angle * (PI / 180); }

	void SetState(State_Boss type);
	void SetAndResetState(State_Boss type);
	void SetAndPlayState(State_Boss type);

	void TotalUpdate(State_Boss type);

	void ShakeEvent();

	void TurnEvent();
	void AttackReadyEvent();
	void AttackEvent();
	void GrogyEvent();

	void SetActionSpeed(State_Boss type, float speed);

	void LandAttackShakeEvent();
	void GrogyAttackShakeEvent();
	void JumpAttackShakeEvent();
	void GrogyEndEvent();
	void GrogyKnockBack();


	int Return();

	void AllStop();

#pragma region Update Function
	void LocationFix(State_Boss type);
	void DirFix();
	void Turn();
	void UnActiveIDle();
	void JumpMove();
	void Down();
	void LandChange();
	void BackStep();
	void JumpToIdle();
	void WeaponcolMove();
	void LastDance();
#pragma endregion

	void LandAttackPattern();
	void JumpAttackPattern();
	void AfterGroggyPattern();
	void JustJumpPattern();

	void Grogy();
	void GrogyRollingFinish();

	void SetPlayer(shared_ptr<Player> target) { _targetPlayer = target; };

	shared_ptr<Collider> GetCollider() { return _heatBox; }
	shared_ptr<Collider> GetGravityCollider() { return _col; }
	shared_ptr<class BossHead> GetHead() { return _head; }

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }
	void SetStart(bool value) { _isStart = value; }
	void SetLand(bool value) { _isLandActive = value; }

	Vector2 GetLandPoint() { return _landPoint; }
	bool _landBreak = false;
private :
	void SetLeft();
	void SetRight();
	shared_ptr<Collider> _heatBox;
	shared_ptr<Collider> _weaponCol;
	shared_ptr<Collider> _jumpLine;
	shared_ptr<Collider> _landLine;

	shared_ptr<class BossHead> _head;

	State_Boss _curstate = IDLE;
	State_Boss _oldstate = IDLE;

	float _chargeTime = 0.0f; // 보스가 공격준비모션에서 공격모션까지 차지하는 시간

	float _turnCoolTime = 2.0f; // 보스의 턴모션의 쿨타임(무한정 좌우가 바뀌는것을 막기 위한 쿨타임)
	float _attackCoolTime = 0.0f; // 보스의 패턴사이 간격
	float _shakeTiming = 0.0f; // 보스의 무기가 땅에 내려치는 순간에 shake 효과를 주기위해 만든 타이머
	float _jumpAttackTime = 0.0f; // 보스가 점프공격을 할 때 무기를 내려치는 순간을 조절하기 위한 타이머
	float _rollingTime = 0.0f; // 보스가 그로기상태가 될 때 얼마나 구를지를 조정하기 위한 타이머
	float _GrogyStopTime = 0.0f; // 보스가 누워있는 자세에서 머리가 빠져나오는 모션으로 바뀌기 까지의 시간을 조절하기 위한 타이머
	float _grogySpeed = 0.0f; // 보스 그로기시 굴러갈때 속도
	float _grogyTime = 0.0f; // 보스 그로기 지속 시간

	int _hitCount = 0;
	int _headHitCount = 0;
	int _armor = 30;

	WeaponMove _weaponMove = { -2.29f, true, 0 , 0.0f};

	Vector2 _landPoint = { 0.0f, 0.0f };

	Vector2 _location = { 0,0 };
	float _jumpTime = 0.0f;
	bool _isJump = false;
	bool _isAttack = false;
	bool _isJumpAttack = false;
	bool _isJustJump = false;
	bool _isJumpAndLandAttack = false;
	bool _isJumpAndGrogyAttack = false;

	bool _isGrogyAttack = false;
	bool _isTurn = false;
	bool _isWeaponMove = false;
	bool _isWeaponActive = false;
	bool _isColActive = true;
	bool _isLandActive = true;

	bool _lastDance = false;

	bool _isStart = true;

	bool _isGrogy = false;

	int _oldAttackType = 1;
	int _curAttackType = 0;

	int _isreturn = 0;

};

