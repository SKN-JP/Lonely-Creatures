#pragma once

class Camera
{
public:
	RectF	restrictedRegion;
	RectF	drawingRegion;
	RectF	smoothDrawingRegion;
	Optional<Vec2>	gazePoint;

	Camera();
	void	update();
	Transformer2D	createTransformer2D(double _magnification = 1.0) const;
};