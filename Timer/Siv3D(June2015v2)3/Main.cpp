# include <Siv3D.hpp>

void Main()
{
	//const Sound sound(L"Example/ta_ge_kane01.mp3");
	const Sound sound(L"Example/nc87543.wav");
	const Font font(40);

	font(L"START").draw();
	WaitKey();

	TimerMinute timerMinute;
	TimerSec timerSec;

	timerMinute.start();
	timerSec.start();

	while (System::Update())
	{
		if (timerSec.elapsed() == 180){
			sound.play();
		}
		/*if (timerMinute.elapsed() >= 180 && flag2){
		sound.play();
		flag2 = false;
		}*/
		if (timerSec.elapsed() == 300){
			sound.play();
		}

		if (Input::KeyShift.pressed && Input::KeySpace.clicked){
			font(L"START").draw();
			WaitKey();

			timerMinute.restart();
			timerSec.restart();
		}
		font(timerMinute.elapsed(), L"分経過").draw(0, 0);

		font(Pad(timerSec.elapsed(), { 2, '0' }), L"秒経過").draw(0, 100);
		int minute = timerMinute.elapsed();
		int sec = timerSec.elapsed();

		font(Pad(timerMinute.elapsed(), { 2, '0' }), L":", Pad(timerSec.elapsed() - minute * 60, { 2, '0' })).draw(0, 200);
	}
}