#pragma once
class CircleCollider;
class RectCollider;

class Collider
{

protected :
	enum class ColliderType
	{
		NONE,
		CIRCLE,
		RECT
	};
public :

	enum ObjectType
	{
		PLAYER,
		MONSTER,
		WALL,
		NONE
	};

	Collider(ColliderType type);
	virtual ~Collider();

	virtual void Update();
	virtual void Render();
	virtual void CreateVertices() abstract;
	void CreatData();


	void SetRed() { _colorBuffer->SetColor(RED); _colorBuffer->Update(); }
	void SetGreen() { _colorBuffer->SetColor(GREEN); _colorBuffer->Update(); }
	void SetBlue() { _colorBuffer->SetColor(BLUE); _colorBuffer->Update(); }



	void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }
	Vector2 GetPos() { return _transform->GetPos(); }


	virtual bool IsCollision(Vector2 pos) abstract;
	
	bool IsCollision(shared_ptr<Collider> col, bool isObb = false);
	bool Block(shared_ptr<Collider> other);

	virtual bool Block(shared_ptr<class CircleCollider> other) abstract;
	virtual bool Block(shared_ptr<class RectCollider> other) abstract;

	virtual bool IsCollision(shared_ptr<CircleCollider> other, bool isObb = false) abstract;
	virtual bool IsCollision(shared_ptr<RectCollider> other, bool isObb = false) abstract;

	const shared_ptr<Transform> GetTransform() { return _transform; }

	void SetParent(shared_ptr<Transform> transform) { _transform->SetParent(transform); }

	ObjectType GetObjectType() { return _objectType; }
	void SetObjectType(ObjectType type) { _objectType = type; }
	
	static bool _isDebug;

protected :
	virtual bool AABB_Collision(shared_ptr<class CircleCollider> other) abstract;
	virtual bool AABB_Collision(shared_ptr<class RectCollider> other) abstract;

	virtual bool OBB_Collision(shared_ptr<class CircleCollider> other) abstract;
	virtual bool OBB_Collision(shared_ptr<class RectCollider> other) abstract;

	vector<Vertex> _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<Transform> _transform;
	shared_ptr<ColorBuffer> _colorBuffer;

	ColliderType _type;
	ObjectType _objectType = NONE;

};

