#include "QuadTree.h"
#include "Utils.h"
#include "Game.h"

int TreeNode::NodeCount = 0;

BOOL TreeNode::CheckObject(LPGAMEOBJECT object, LPTREENODE node)
{
	float oleft, otop, oright, obottom;
	object->GetBoundingBox(oleft, otop, oright, obottom);
	float nleft, ntop, nright, nbottom;
	node->GetBoundingBox(nleft, ntop, nright, nbottom);
	if (oleft >= nright || nleft >= oright)
		return false;
	if (otop <= nbottom || ntop <= obottom)
		return false;
	return true;
}

BOOL TreeNode::CheckObj(float left, float top, float right, float bottom, LPTREENODE node)
{
	return true;
}

TreeNode::TreeNode(float x, float y, float width, float height, LPTREENODE parent) {
	id = NodeCount;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	NodeCount++;
	child = NULL;
	gameObjects = NULL;
	parentNode = parent;
}
void TreeNode::AddObject(LPGAMEOBJECT object)
{
	if (!CheckObject(object, this))
		return;
	if (child == NULL)
	{
		if (gameObjects == NULL)
			gameObjects = new vector<LPGAMEOBJECT>();
		for (int i = 0; i < gameObjects->size(); i++)
			if (gameObjects->at(i) == object)
				return;
		gameObjects->push_back(object);
		return;
	}
	else
	{
		for (int i = 0; i < child->size(); i++)
			child->at(i)->AddObject(object);
	}
}
void TreeNode::Update(LPGAMEOBJECT object)
{
	vector<LPTREENODE>* treeNodeList = this->IsObjectInside(object);
	for (int i = 0; i < treeNodeList->size(); i++)
	{
		if (!CheckObject(object, treeNodeList->at(i)))
		{
			vector<LPGAMEOBJECT>* objectList = treeNodeList->at(i)->gameObjects;
			objectList->erase(std::remove(objectList->begin(), objectList->end(), object));
			if (objectList->size() == 0)
				treeNodeList->at(i)->gameObjects = NULL;
		}
	}
	this->AddObject(object);
}
vector<LPTREENODE>* TreeNode::NodeInCam()
{
	if (gameObjects != NULL)
	{
		vector<LPTREENODE>* a = new vector<LPTREENODE>();
		a->push_back(this);
		return a;
	}
	float left, top;
	CGame::GetInstance()->GetCamPos(left, top);
	float right = left + CGame::GetInstance()->GetBackBufferWidth();
	float bottom = top;
	top = top + CGame::GetInstance()->GetBackBufferHeight();
	if (!CheckObj(left, top, right, bottom, this))
		return new vector<LPTREENODE>();
	if (child != NULL)
	{
		vector<LPTREENODE>* a = new vector<LPTREENODE>();
		for (int i = 0; i < child->size(); i++)
		{
			vector<LPTREENODE>* temp = child->at(i)->NodeInCam();
			if (temp != NULL)
			{
				a->insert(a->end(), temp->begin(), temp->end());
			}
		}
		return a;
	}
	return new vector<LPTREENODE>();
}
void TreeNode::Split()
{
	/*float CamW, CamH;
	CamW = CGame::GetInstance()->GetBackBufferWidth();
	CamH = CGame::GetInstance()->GetBackBufferHeight();*/
	if (child != NULL)
	{
		for (int i = 0; i < child->size(); i++)
			child->at(i)->Split();
	}
	else
	{

		LPTREENODE node1 = new TreeNode(x, y, width / 2, height / 2, this);
		LPTREENODE node2 = new TreeNode(x + width / 2, y, width / 2, height / 2, this);
		LPTREENODE node3 = new TreeNode(x, y - height / 2, width / 2, height / 2, this);
		LPTREENODE node4 = new TreeNode(x + width / 2, y - height / 2, width / 2, height / 2, this);
		child = new vector<LPTREENODE>();
		child->push_back(node1);
		child->push_back(node2);
		child->push_back(node3);
		child->push_back(node4);
		if (gameObjects == NULL)
			return;
		for (int i = 0; i < gameObjects->size(); i++)
		{
			float left, top, right, down;
			LPGAMEOBJECT temp = gameObjects->at(i);
			temp->GetBoundingBox(left, top, right, down);
			if (CheckObject(gameObjects->at(i), node1))
				node1->AddObject(temp);
			if (CheckObject(gameObjects->at(i), node2))
				node2->AddObject(temp);
			if (CheckObject(gameObjects->at(i), node3))
				node3->AddObject(temp);
			if (CheckObject(gameObjects->at(i), node4))
				node4->AddObject(temp);
		}
		gameObjects = NULL;
	}

}

void TreeNode::ClearObject() {
	for (int i = 0; i < gameObject.size(); i++) {
		if (gameObject[i]->IsDeleted()) {
			delete gameObject[i];
			gameObject.erase(gameObject.begin() + i);
		}
	}
}
vector<LPTREENODE>* TreeNode::IsObjectInside(LPGAMEOBJECT object)
{
	if (gameObjects != NULL)
	{
		for (int i = 0; i < gameObjects->size(); i++)
			if (gameObjects->at(i) == object)
			{
				vector<LPTREENODE>* a = new vector<LPTREENODE>();
				a->push_back(this);
				return a;
			}
		return NULL;
	}
	if (child == NULL)
		return NULL;
	vector<LPTREENODE>* a = new vector<LPTREENODE>();
	for (int i = 0; i < child->size(); i++)
	{
		vector<LPTREENODE>* node = child->at(i)->IsObjectInside(object);
		if (node != NULL)
			a->insert(a->end(), node->begin(), node->end());
	}
	if (a->size() > 0)
		return a;
	return NULL;
}

vector<LPGAMEOBJECT>* TreeNode::GetObject() {
	if (child != NULL)
	{
		vector<LPGAMEOBJECT>* result = new vector<LPGAMEOBJECT>();
		for (int i = 0; i < child->size(); i++)
		{
			LPTREENODE temp = child->at(i);
			vector<LPGAMEOBJECT>* gameObjectList = temp->GetObject();
			if (gameObjectList != NULL)
				result->insert(result->end(), gameObjectList->begin(), gameObjectList->end());

		}
		return result;
	}
	else
		return gameObjects;
}
