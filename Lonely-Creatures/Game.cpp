#include"Game.h"

Game::Game()
	: field(&assets)
	, display(&assets)
	, playSpeed(1)
	, drawObjectName(false)
{

	Window::SetTitle(U"Lonely Creatures");
	Window::Resize(1280, 720);

	assets.audio(U"���݂��܂̂�肩��.mp3").setLoop(true);
	//assets.audio(U"���݂��܂̂�肩��.mp3").play();
}

void	Game::update() {

	ClearPrint();

	//PlaySpeed�̒���
	if (KeyF1.down()) {
		if (playSpeed == 1) playSpeed = 0;
		else if (playSpeed > 1) playSpeed /= 2;
	}
	if (KeyF2.down()) {
		if (playSpeed == 0) playSpeed = 1;
		else if (playSpeed > 0 && playSpeed <= 64) playSpeed *= 2;
	}
	Print << U"�t���X�N���[���ɂ���ɂ�F11�L�[�A�w���X�o�[��\������ɂ�H�L�[�������Ă��������B";
	Print << U"���s���x��ύX����ɂ́AF1�L�[�A��������F2�L�[���g���Ă��������B" << U"���s���x = " << playSpeed;
	Print << U"������:" << Creature::numEnabled << U" ����������:" << int(Creature::numEnabled*100.0 / (double)field.creatures.size()) << U"%";
	Print << U"�}�e���A����:" << Material::numEnabled << U" ����������:" << int(Creature::numEnabled*100.0 / (double)field.creatures.size()) << U"%";

	//FullScreen
	if (KeyF11.down())
	{
		if (Window::GetState().fullScreen) Graphics::SetFullScreen(false, Size(1280, 720));
		else Graphics::SetFullScreen(true, Graphics::EnumOutputs().front().displayModes.back().size);
		//System::Update();
	}

	camera.update();

	if (KeyH.down()) field.drawHealthBar = !field.drawHealthBar;

	for (int i = 0; i < playSpeed; i++) field.update();

	if (MouseL.down())
	{
		auto t = camera.createTransformer2D();

		display.selectedCreature = nullptr;

		for (auto& c : field.creatures)
		{
			if (c.enabled && Circle(c.pos, c.size() / 2.0).intersects(Cursor::PosF()))
			{
				display.selectedCreature = &c;
				break;
			}
		}
	}

	{
		auto t = camera.createTransformer2D();

		field.draw();
	}

	if (KeyF.down()) drawObjectName = !drawObjectName;

	if (drawObjectName)
	{
		auto t = camera.createTransformer2D(1.0 / 16.0);

		for (auto& c : field.creatures)
		{
			if (c.enabled) assets.font(32)(c.name()).drawAt(c.pos.movedBy(0, -c.size() / 2.0 - 1.6)*16.0);
		}
		for (auto& m : field.materials)
		{
			if (m.enabled) assets.font(32)(m.name()).drawAt(m.drawPos().movedBy(0, -m.size() / 2.0 - 1.6)*16.0);
		}
	}

	if (display.selectedCreature != nullptr && !display.selectedCreature->enabled) display.selectedCreature = nullptr;
	if (display.selectedCreature != nullptr)
	{
		auto t = camera.createTransformer2D();
		auto* sc = display.selectedCreature;
		Circle(sc->drawPos(), sc->size() / 2.0).draw(Color(Palette::Skyblue, 96)).drawFrame(sc->size() / 20.0, Palette::Black);
		camera.gazePoint = sc->pos;
	}
	else
	{
		auto t = camera.createTransformer2D();
		for (auto& c : field.creatures)
		{
			if (Circle(c.drawPos(), c.size() / 2.0).intersects(Cursor::PosF()))
			{
				Circle(c.drawPos(), c.size() / 2.0).drawFrame(c.size() / 20.0, Palette::Black);
				break;
			}
		}
	}
}