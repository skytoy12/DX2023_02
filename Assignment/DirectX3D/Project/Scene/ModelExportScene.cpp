#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Knight D Pelegrini";
	string name1 = "Y Bot";
	string name2 = "Groot";
	string name3 = "Dwarven_Axe";
	string name4 = "StanfordBunny";


	exporter = new ModelExporter(name4);
	exporter->ExportModel();
	//exporter->ExportClip("Running Backward");
	//exporter->ExportClip("Sad Idle");
	//exporter->ExportClip("Standing Melee Attack 360 High");



	model = new Model(name4);
}

ModelExportScene::~ModelExportScene()
{
	delete exporter;
	delete model;
}

void ModelExportScene::Update()
{
	model->Update();
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
	model->Render();
}

void ModelExportScene::PostRender()
{
	model->GetReader()->Debug();

}
