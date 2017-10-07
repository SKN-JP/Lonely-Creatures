#pragma once

class Assets;
struct Field;
struct Chip;
struct Material;

enum struct MType {
	Leaf,
	Meat,
	Iron,
	Fertilizer,
};
enum struct CType {
	Clematis,
	Slug,
	Cricket,
};

//��b�I�u�W�F�N�g
struct Object {


	int		age;
	Chip*	registeredChip;
	bool	enabled;
	double	y;
	double	vy;
	Vec2	v;
	Vec2	pos;
	Vec2	angle;

	static	Field*	field;
	static	Assets*	assets;

	Object()
		: registeredChip(nullptr)
		, enabled(true)
		, age(0)
	{}
	Vec2	drawPos() const {
		return pos.movedBy(0, -y);
	}
};

//�����I�u�W�F�N�g
struct Creature : Object {

	enum struct State {
		Egg,
		Seed,
		Child,
		Adult,
	};

	enum struct Gender {
		None,
		Female,
		Male,
	};

	int		health;
	CType	type;
	State	state;
	Gender	gender;

	static int	numEnabled;

	Creature();

	int		maxHealth() const;
	double	size() const;
	void	erase();
	void	addMaterial(MType _type, double _force = 0.0, int _num = 1);
};

//�}�e���A���I�u�W�F�N�g
struct Material : Object {

	MType	type;

	static int	numEnabled;

	Material();
	double	size() const { return 8.0; }
	void	erase();
};

struct Chip {

	Array<Creature*> creatures;
	Array<Material*> materials;

	void	remove(Creature* _creature);
	void	remove(Material* _material);
	void	set(Creature* _creature);
	void	set(Material* _material);
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
		Creature::numEnabled++;
		for (auto& c : creatures) {
			if (!c.enabled) {
				c = Creature();	//���Z�b�g;
				return &c;
			}
		}
		return &creatures.emplace_back();
	}
	Material*	newMaterial() {
		Material::numEnabled++;
		for (auto& m : materials) {
			if (!m.enabled) {
				m = Material();	//���Z�b�g;
				return &m;
			}
		}
		return &materials.emplace_back();
	}
};