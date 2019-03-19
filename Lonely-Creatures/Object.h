#pragma once

class Assets;
struct Field;

/*
Object�N���X�͕��̉^����\�����邽�߂̃N���X

*/

//��b�I�u�W�F�N�g
struct Object {

	bool	isSigned;	//Table�ɓo�^���ꂽ��
	bool	eraseFlag;	//���̃t���[���ŏ�������
	double	y;		//���x
	double	vy;		//�㉺�����̑��x
	Vec2	v;		//���ʕ����̑��x
	Vec2	pos;	//���W
	Vec2	angle;	//�����Ă������ len = 1.0

	static	Field*	field;
	static	Assets*	assets;

	Object()
		: isSigned(false)
		, eraseFlag(false)
		, y(0.0)
		, vy(0.0)
		, v(0.0, 0.0)
		, pos(0.0, 0.0)
		, angle(RandomVec2())
	{}

	Vec2	drawPos() const;
	double	angleAsRadian() const;	//���a
};

//�����I�u�W�F�N�g
struct Creature : Object {

	enum struct State {
		Child,
		Adult,
	};

	enum struct Type {
		Clematis,
		Slug,
		Criket,
	};

	int		age;
	int		health;
	Type	type;
	State	state;

	Creature()
		: age(0)
		, health(0)
		, type(Type::Clematis)
	{}

	double	size() const;
	int		maxHealth() const;
	void	update();
	void	draw() const;
};

//�}�e���A���I�u�W�F�N�g
struct Material : Object {

	enum struct Type {
		Leaf,
		Meat,
		Fertilizer,
	};

	int		age;
	Type	type;

	Material()
		: age(0)
		, type(Type::Leaf)
	{}
};
