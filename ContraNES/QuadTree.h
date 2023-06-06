#pragma once
#include "GameObject.h"
#include <map>
class TreeNode;
typedef TreeNode* LPTREENODE;

class TreeNode
{
private:
	int id;
	float x;
	float y;
	float width;
	float height;
	static int NodeCount;
	//float oleft, otop, oright, obottom;
	//float nleft, ntop, nright, nbottom;
	LPTREENODE parentNode;
	vector<LPTREENODE>* child;
	vector<LPGAMEOBJECT>* gameObjects;
	vector<LPGAMEOBJECT> gameObject;
public:
	TreeNode(float x, float y, float width, float height, LPTREENODE parent = NULL);
	void Split();

	BOOL CheckObject(LPGAMEOBJECT object, LPTREENODE node);
	BOOL CheckObj(float left, float top, float right, float bottom, LPTREENODE node);

	void AddObject(LPGAMEOBJECT object);
	void Update(LPGAMEOBJECT object);
	void ClearObject();
	vector<LPTREENODE>* IsObjectInside(LPGAMEOBJECT object);
	vector<LPGAMEOBJECT>* GetObject();
	void GetBoundingBox(float& left, float& top, float& right, float& down)
	{
		left = x;
		down = y;
		right = x + width;
		top = y + height;
	}
	vector<LPTREENODE>* NodeInCam();
};