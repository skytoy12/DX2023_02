#pragma once
class Action
{
public :
	struct Clip
	{
		Vector2 _startPos;
		Vector2 _size;
		weak_ptr<SRV> _srv;

		Clip(float x, float y, float w, float h, shared_ptr<SRV> srv)
			:_startPos(x, y), _size(w, h), _srv(srv)
		{
			
		}
	};

	enum Type
	{
		END,
		LOOP,
		PINGPONG
	};

	Action(vector<Clip> clips, string name = "", Type type = Type::LOOP, float speed = 0.1f);
	~Action();

	void Update();

	void Play();
	void Pause();
	void Stop();
	void Reset();

	void SetType(Type _type) { _repeatType = _type; }

	void SetSpeed(float speed) { _speed = speed; }

	const Action::Clip& GetCurClip() { return _clips[_curClipIndex]; }
	Action::Type GetReapeatType() { return _repeatType; }
	bool IsPlay() { return _isPlay; }


	void SetEndEvent(CallBack endEvent) { _endEvent = endEvent; }
	void SetAlmostEvent(CallBack almostEvent) { _almostEnd = almostEvent; }
	void SetLoopEvent(CallBack loopEvent) { _loopEvent = loopEvent; }


private :
	string _name;
	vector<Clip> _clips;

	Type _repeatType = Type::LOOP;
	bool _isPlay = false;

	UINT _curClipIndex = 0;

	float _time = 0.0f;
	float _speed = 0.0f;

	bool _isReverse = false;

	CallBack _almostEnd = nullptr;
	CallBack _endEvent = nullptr;
	CallBack _loopEvent = nullptr;

};

