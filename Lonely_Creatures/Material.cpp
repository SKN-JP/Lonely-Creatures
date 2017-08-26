#include"Material.h"
#include"Area.h"

void	Material::joinArea()
{
	joinedArea = &areas.at(getAreaPos(pos));
	joinedArea->materials.emplace_back(this);
}
void	Material::erase()
{
	if (joinedArea != nullptr) joinedArea->materials.remove(this);
	reset();
}
void	Material::reset()
{
	enabled = false;
	materialType = -1;
	n = 0.0;
	pos = Vec2::Zero();
	joinedArea = nullptr;
}
Material*	newMaterial()
{
	for (auto& m : materials)
	{
		if (!m.enabled) return &m;
	}
	LOG_ERROR(L"Material Max");
	return nullptr;
}
Material*	nearestMaterial(const Vec2& _pos, int _materialType)
{
	Point p(int(_pos.x / areaWidth), int(_pos.y / areaWidth));
	Material*	nearest = nullptr;

	for (int x = Max(0, p.x - 1); x < Min(areas.size().x, p.x + 2); x++)
	{
		for (int y = Max(0, p.y - 1); y < Min(areas.size().y, p.y + 2); y++)
		{
			for (auto* m : areas.at(y, x).materials)
			{
				if (m->materialType == _materialType && (nearest == nullptr || nearest->pos.distanceFrom(_pos) > m->pos.distanceFrom(_pos)))
				{
					nearest = m;
				}
			}
		}
	}

	return nearest;
}
Material*	setMaterial(int _type, double _n, const Vec2& _pos, const double _f)
{
	auto* m = newMaterial();
	if (m == nullptr) LOG_ERROR(L"Materialが限界数に達しました。");
	m->enabled = true;
	m->pos = _pos;
	m->n = _n;
	m->materialType = _type;
	m->joinArea();
	m->v = RandomVec2(_f);
	return m;
}
void	updateMaterials()
{
	for (auto& m : materials)
	{
		if (m.enabled)
		{
			switch (m.materialType)
			{
			case 1:
				for (int i = 0; i < m.n; i++)
				{
					if (RandomBool(0.001))
					{
						double s = 2.0;
						if (m.n > s)
						{
							setMaterial(0, s, m.pos, 1);
							m.n -= s;
						}
						else m.materialType = 0;
					}
				}
				break;
			default:
				break;
			}

			if (!m.pos.isZero())
			{
				if (getArea(m.pos + m.v) != m.joinedArea)
				{
					if (m.joinedArea != nullptr) m.joinedArea->materials.remove(&m);
					m.pos += m.v;
					if (m.pos.x < 0) m.pos.x = 0;
					if (m.pos.y < 0) m.pos.y = 0;
					if (m.pos.x > 1024) m.pos.x = 1024;
					if (m.pos.y > 1024) m.pos.y = 1024;
					m.joinArea();
				}
				else
				{
					m.pos += m.v;
					if (m.pos.x < 0) m.pos.x = 0;
					if (m.pos.y < 0) m.pos.y = 0;
					if (m.pos.x > 1024) m.pos.x = 1024;
					if (m.pos.y > 1024) m.pos.y = 1024;
				}
				m.v *= 0.90;
			}
		}
	}
}