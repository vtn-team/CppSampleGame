#pragma once

class IGameObject;
class SysPhysics;
class Collider2D : public std::enable_shared_from_this<Collider2D> {
public:
	enum COLLIDER_TYPE {
		INVALID_TYPE,
		AABB,
		SPHERE,
		OBB
	};

	enum COLLIDER_TAG {
		INVALID_TAG,
		PLAYER,
		ENEMY,
		BULLET,
		MAX_COLLIDER_TAG
	};
private:
	friend SysPhysics;

	COLLIDER_TYPE _type;
	COLLIDER_TAG _tag;

protected:
	std::weak_ptr<IGameObject> _target;
	std::function<bool(std::shared_ptr<Collider2D>)> _hitCallback;
	std::shared_ptr<Collider2D> GetPtr() { return shared_from_this(); }

	Collider2D() {}
public:
	Collider2D(COLLIDER_TYPE type, std::weak_ptr<IGameObject> link);
	virtual ~Collider2D();

	COLLIDER_TYPE GetType() { return _type; }
	COLLIDER_TAG GetTag() { return _tag; }
	std::weak_ptr<IGameObject> GetGameObject() { return _target; }

	void SetCallback(std::function<bool(std::shared_ptr<Collider2D>)> callback);
	void UpdateTag(COLLIDER_TAG tag);
	virtual bool IsHit(std::shared_ptr<Collider2D> target) = 0; //targetに対して当たっているか
};

class AABBCollider : public Collider2D {

	AABBCollider() {}
public:
	AABBCollider(std::weak_ptr<IGameObject> link) :
		Collider2D(COLLIDER_TYPE::AABB, link) {}
	bool IsHit(std::shared_ptr<Collider2D> target); //targetに対して当たっているか
};

class OBBCollider : public Collider2D {
};

class SphereCollider : public Collider2D {
	Vector2 _pos;
	float _radius;

	SphereCollider() {}

public:
	SphereCollider(Vector2 p, float r);
	void UpdatePos(Vector2 p) { _pos = p; }
	void UpdateRadius(float r) { _radius = r; }
	Vector2& GetPos() { return _pos; }
};