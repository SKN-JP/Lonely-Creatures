#pragma once

class Assets;
struct Field;

//��b�I�u�W�F�N�g
struct Object {

	enum struct Type {
		Creature,
		Material,
	};

	bool	registered;
	bool	enabled;
	Type	type;
	double	y;
	double	vy;
	Vec2	v;
	Vec2	pos;
	Vec2	angle;

	static	Field*	field;
	static	Assets*	assets;

	Object() 
		: registered(false)
		, enabled(true)
	{}
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

	Creature();
	Creature(const Vec2& _pos, const Type& _type);

	int		maxHealth() const;
	double	size() const;
	void	erase();
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

	Material();
	Material(const Vec2& _pos, const Type& _type);
	double	size() const { return 8.0; }
	void	erase();
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
	Material*	searchMaterial(Vec2 _pos, double _range, double(*func)(Vec2, Material*)) const;
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
	Creature*	newCreature() {
		for (auto& c : creatures) {
			if (!c.enabled) {
				c = Creature();	//���Z�b�g;
				return &c;
			}
		}
		return &creatures.emplace_back();
	}
	Material*	newMaterial() {
		for (auto& m : materials) {
			if (!m.enabled) {
				m = Material();	//���Z�b�g;
				return &m;
			}
		}
		return &materials.emplace_back();
	}
};