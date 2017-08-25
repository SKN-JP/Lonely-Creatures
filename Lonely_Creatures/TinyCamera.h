#pragma once

struct TinyCamera
{
	TinyCamera();
	void	update();
	Vec2	getCursorPos() const;
	Mat3x2	getMat3x2(int _delta = 0) const;
	Transformer2D createTransformer(int _delta = 0) const;

	RectF	outputRegion;		//��ʕ`���̈�
	RectF	restrictedRegion;	//���_�ړ������̈�
	RectF	drawingRegion;		//���z�`��̈�
	RectF	smoothDrawingRegion;//���`��̈�
	Optional<Vec2>	gazePoint;	//�����_
};

extern TinyCamera tinyCamera;

void	initTinyCamera();