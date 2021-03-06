#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 50

#include "Module.h"
#include "p2Point.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLAYER,
	COLLIDER_PLAYER2,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_PLAYER2_SHOT,
	COLLIDER_PLAYER_HIT,
	COLLIDER_PLAYER2_HIT,
	COLLIDER_PLAYER_GRAB,
	COLLIDER_PLAYER2_GRAB,
	COLLIDER_PLAYER_GRABBOX,
	COLLIDER_PLAYER2_GRABBOX,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(iPoint position)
	{
		rect.x = position.x;
		rect.y = position.y;
	}

	void SetPos(int posx, int posy) {
		rect.x = posx;
		rect.y = posy;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr);
	Collider* AddCollider(Collider collider);
	void DebugDraw();
	void RemoveDeletedColliders();
	void CalculateCollisions();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
};

#endif // __ModuleCollision_H__