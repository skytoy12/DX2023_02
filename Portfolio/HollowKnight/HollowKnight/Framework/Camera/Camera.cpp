#include "framework.h"
#include "Camera.h"
Camera* Camera::_instance = nullptr;
Camera::Camera()
{
	_view = make_shared<Transform>();
	_uiView = make_shared<Transform>();
	_uiView->Update();

	_projection = make_shared<MatrixBuffer>();

	// XMMATRIX projectM = XMMatrixOrthographicOffCenterLH(0, WIN_WIDTH, 0, WIN_HEIGHT, 0.0f, 1.0f);
	XMMATRIX projectM = XMMatrixOrthographicLH(WIN_WIDTH, WIN_HEIGHT, 0.0f, 1.0f);

	_projection->SetData(projectM);
	_projection->Update();
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (_target.expired() == false)
		FollowMode();
	else
		FreeMode();

	_view->Update();
	Shake();
}

void Camera::PostRender()
{
}

void Camera::ShakeStart(float magnitude, float duration, float reduceDamping)
{
	_magnitude = magnitude;
	_duration = duration;
	_reduceDamping = reduceDamping;

	_originPos = _view->GetWorldPosition() * -1.0f;

}

void Camera::SetViewPort(UINT width, UINT height)
{
}


void Camera::AddVector2(const Vector2& pos)
{
	_view->AddVector2(pos * -1);
}

void Camera::SetPosition(Vector2& pos)
{
	_view->SetPosition(pos * -1);
}

Vector2 Camera::GetWorldMousePos()
{
	XMMATRIX inverseM = DirectX::XMMatrixInverse(nullptr, _view->GetMatrix());

	Vector2 mousePos = MOUSE_POS;

	mousePos -= CENTER;

	return mousePos.TransformCoord(inverseM);
}

void Camera::FollowMode()
{
	Vector2 targetPos = _target.lock()->GetWorldPosition() - _offSet;
	targetPos.x *= _view->GetScale().x;
	targetPos.y *= _view->GetScale().y;

	if (targetPos.x < _leftBottom.x + WIN_WIDTH * 0.5f)
		targetPos.x = _leftBottom.x + WIN_WIDTH * 0.5f;

	if (targetPos.x > _rightTop.x - WIN_WIDTH * 0.5f)
		targetPos.x = _rightTop.x - WIN_WIDTH * 0.5f;

	if (targetPos.y < _leftBottom.y + WIN_HEIGHT * 0.5f)
		targetPos.y = _leftBottom.y + WIN_HEIGHT * 0.5f;

	if (targetPos.y > _rightTop.y - WIN_HEIGHT * 0.5f)
		targetPos.y = _rightTop.y - WIN_HEIGHT * 0.5f;

	Vector2 lerp = LERP( _view->GetWorldPosition(), -targetPos, DELTA_TIME * 5.0f);
	_view->SetPosition(lerp);
}

void Camera::FreeMode()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS('W'))
			AddVector2(UP_VECTOR * DELTA_TIME * _speed);
		if (KEY_PRESS('S'))
			AddVector2(-UP_VECTOR * DELTA_TIME * _speed);
		if (KEY_PRESS('A'))
			AddVector2(-RIGHT_VECTOR * DELTA_TIME * _speed);
		if (KEY_PRESS('D'))
			AddVector2(RIGHT_VECTOR * DELTA_TIME * _speed);
	}
}

void Camera::Shake()
{
	if (_duration <= 0.0f)
		return;

	_duration -= DELTA_TIME;
	_magnitude -= _reduceDamping * DELTA_TIME;

	if (_magnitude <= 0.0f)
	{
		_magnitude = 0.0f;
		_duration = 0.0f;
	}

	if (_target.expired() == false)
	{
		Vector2 targetPos = (_target.lock()->GetWorldPosition() - _offSet);

		targetPos.x *= _view->GetScale().x;
		targetPos.y *= _view->GetScale().y;

		if (targetPos.x < _leftBottom.x + WIN_WIDTH * 0.5f)
			targetPos.x = _leftBottom.x + WIN_WIDTH * 0.5f;

		if (targetPos.x > _rightTop.x - WIN_WIDTH * 0.5f)
			targetPos.x = _rightTop.x - WIN_WIDTH * 0.5f;

		if (targetPos.y < _leftBottom.y + WIN_HEIGHT * 0.5f)
			targetPos.y = _leftBottom.y + WIN_HEIGHT * 0.5f;

		if (targetPos.y > _rightTop.y - WIN_HEIGHT * 0.5f)
			targetPos.y = _rightTop.y - WIN_HEIGHT * 0.5f;

		_originPos = targetPos;

	}

	Vector2 randPos;
	randPos.x = _originPos.x + MyMath::RandomFloat(-_magnitude, _magnitude);
	randPos.y = _originPos.y + MyMath::RandomFloat(-_magnitude, _magnitude);

	_randomPos = randPos;
	SetPosition(randPos);

	if (_duration <= 0.0f)
	{
		SetPosition(_originPos);
	}
}
