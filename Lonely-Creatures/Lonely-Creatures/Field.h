#pragma once

class Assets;

//��b�I�u�W�F�N�g
struct Object {

	enum struct Type {
		Creature,
		Material,
	};

	bool	isSigned;
	Type	type;
	double	y;
	double	vy;
	Vec2	v;
	Vec2	pos;
	Vec2	angle;
	bool	eraseFlag;

	Object() : isSigned(false), eraseFlag(false) {}
	Vec2	drawPos() const {
		return pos.movedBy(0, -y);
	}
};

//�����I�u�W�F�N�g
struct Creature : Object {

	enum struct Type {
		Clematis,
		Slug,
		Cricket,
	};

	enum struct State {
		Child,
		Adult,
	};

	enum struct Gender {
		None,
		Female,
		Male,
	};

	int		age;
	int		health;
	Type	type;
	State	state;
	Gender	gender;

	Creature(const Vec2& _pos, const Type& _type);

	int	maxHealth() const {
		switch (type)
		{
		case Type::Clematis:return 5;
		case Type::Slug:	return 12;
		case Type::Cricket:	return 20;
		default: return 100;
		}
	}
	double	size() const {
		switch (type)
		{
		case Type::Clematis:return 16.0;
		case Type::Slug:
			if (state == State::Adult) return 18.0;
			else return 8.0;
		case Type::Cricket:	return 32.0;
		default: return 16.0;
		}
	}
};

//�}�e���A���I�u�W�F�N�g
struct Material : Object {

	enum struct Type {
		Leaf,
		Meat,
		Iron,
		Fertilizer,
	};

	Type	type;
	int		age;

	Material(const Vec2& _pos, const Type& _type);
};

struct Chip {

	Array<Creature*> creatures;
	Array<Material*> materials;

	void	remove(Creature* _creature) { creatures.remove(_creature); }
	void	remove(Material* _material) { materials.remove(_material); }
	void	set(Creature* _creature) { creatures.emplace_back(_creature); }
	void	set(Material* _material) { materials.emplace_back(_material); }
};

struct Table {


	Grid<Chip> chips;
	double	width;
	Size	size;

	Table(double _width, const Size& _size);


	//�ł��]���l�̍������̂�Ԃ��A0.0�ȉ��̂��̂����Ȃ��ꍇ�Anullptr��Ԃ�
	Creature*	searchCreature(Vec2 _pos, double _range, double(*func)(Vec2, Creature*)) const;
	Chip*	chip(const Vec2& _pos);
};

//�t�B�[���h
struct Field {

	RectF	region;
	Table	table;
	Assets*	assets;
	size_t	maxNumCreatures;
	size_t	maxNumMaterials;
	Array<Creature>	creatures;
	Array<Material>	materials;

	Field(Assets* _assets);

	void	update();
	void	draw() const;
};