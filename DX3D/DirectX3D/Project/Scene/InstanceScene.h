#pragma once
class InstanceScene : public Scene
{

	struct InstanceData
	{
		Matrix transform;

		Vector4 color = { 1, 1, 1, 1 };
	};

public:
	InstanceScene();
	~InstanceScene();

	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

private:
	//vector<Quad*> quads;

	const UINT COUNT = 50;

	Quad* quad;

	vector<InstanceData> instanceData;

	VertexBuffer* instanceBuffer;
};


