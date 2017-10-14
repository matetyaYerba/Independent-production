# include <Siv3D.hpp>

#define score 180, 100, 120, 170, 200, 240, 250, 300, 350, 400

void start();

void Main()
{

	FilePath folder(L"Example/p.txt");
	TextWriter writer(folder);

	int sum_score = 0;
	int num[3];
	int num_r[3];

	Rect rect_m[10] = {
			{ 205, 122, 31, 10 },
			{ 196, 220, 27, 9 },
			{ 167, 275, 22, 9 },
			{ 490, 234, 19, 10 },
			{ 465, 284, 34, 11 },
			{ 548, 137, 13, 14 },
			{ 548, 205, 23, 17 },
			{ 50, 206, 12, 10 },
	};

	num[0] = RandomSelect({ score });
	num[1] = RandomSelect({ score });
	num[2] = RandomSelect({ score });

	num_r[0] = Random(7);
	num_r[1] = Random(7);
	num_r[2] = Random(7);

	while (num_r[0] == num_r[1])
	{
		num_r[1] = Random(7);
	}
	while (num_r[1] == num_r[2] || num_r[2] == num_r[0])
	{
		num_r[2] = Random(7);
	}

	Rect goal[3];
	goal[0] = rect_m[num_r[0]];
	goal[1] = rect_m[num_r[1]];
	goal[2] = rect_m[num_r[2]];

	const Image image(L"Example/1_2.png");
	const Texture clear_image1(L"Example/c_back1.jpg");
	const Texture clear_image2(L"Example/c_back22.jpg");
	const Texture clear_image3(L"Example/c_back34.png");
	const Sound se_jet(L"Example/nc19462_2.wav");
	const Sound se_get(L"Example/nc92253.mp3");
	const Sound se_out(L"Example/nc34608.wav");
	const Sound se_iyo(L"Example/iyou.mp3");
	const Sound se_gbgm(L"Example/nc85054.mp3");
	const Sound se_end(L"Example/nc42872.mp3");

	const bool useAlpha = true;

	const MultiPolygon polygon = Imaging::FindExternalContours(image, useAlpha);

	MultiPolygon simplifiedPolygon = polygon.simplified(1.5);

	const Texture texture(image);

	Font font(30);

	Window::Resize(image.width, image.height);
	double gg = 0.04;

	Circle pollen;
	double g = 0, gx = 0;
	pollen.x = 300;
	pollen.y = 10;
	pollen.r = 3;

	Rect ef(1, 1);

	start();

	const Font font2(10, Typeface::Black);

	texture.draw();
	pollen.drawFrame(2, 0, Palette::White);

	for (int i = 0; i < 3; i++){
		font2(num[i]).draw(goal[i].x, goal[i].y + 5, Palette::Green);
	}

	Rect score_rect(0, 180, 600, 60);

	se_end.setPosSec(-3);

	WaitKey();

	while (System::Update())
	{

		texture.draw();
		for (int i = 0; i < 3; i++){
			font2(num[i]).draw(goal[i].x,goal[i].y + 5, Palette::Green);
		}

		if (gx > 0){
			gx -= 0.01;
		}
		else if (gx < 0){
			gx += 0.01;
		}

		g += gg;

		if (gg < 0.03) gg += 0.0004;

		if (Input::KeyUp.pressed || Input::KeyW.pressed){
			se_jet.play();

			g -= 0.08;
			gg -= 0.0007;

			ef.setCenter(pollen.x, pollen.y + 5.5);
			ef.draw();
			ef.setCenter(pollen.x + 2.5, pollen.y + 6);
			ef.draw();
			ef.setCenter(pollen.x - 2.5, pollen.y + 6);
			ef.draw();
		}
		else
		{
			se_jet.stop();
		}

		if (Input::KeyRight.pressed || Input::KeyD.pressed){
			gx += 0.035;
		}
		if (Input::KeyLeft.pressed || Input::KeyA.pressed){
			gx -= 0.035;
		}

		pollen.y += g;
		pollen.x += gx;
		const MultiPolygon movedpolygon = simplifiedPolygon;
		
		if (movedpolygon.intersects(pollen) || pollen.y > 400){

			se_out.playMulti();
			se_jet.stop();
			//font(L"Game Over").draw();
			pollen.drawFrame(1, 1, Palette::Black);
			ef.setCenter(pollen.x, pollen.y);
			ef.draw();
			ef.setCenter(pollen.x- (gx * 2), pollen.y-(g * 2));
			ef.draw();
			ef.setCenter(pollen.x + (gx * 2), pollen.y - gg);
			ef.draw();

			System::Update();
			System::Sleep(500);

			se_end.playMulti(0.7);
			clear_image1.draw();
			score_rect.draw(Palette::Red);
			font(sum_score).draw(score_rect.center.x, score_rect.center.y - 30);
			font(L"Pt").draw(score_rect.center.x + 35, score_rect.center.y - 30);

			WaitKey();
			se_end.stopMulti();
			{
				sum_score = 0;
				num[0] = RandomSelect({ score });
				num[1] = RandomSelect({ score });
				num[2] = RandomSelect({ score });

				num_r[0] = Random(7);
				num_r[1] = Random(7);
				num_r[2] = Random(7);

				while (num_r[0] == num_r[1])
				{
					num_r[1] = Random(7);
				}
				while (num_r[1] == num_r[2] || num_r[2] == num_r[0])
				{
					num_r[2] = Random(7);
				}

				goal[0] = rect_m[num_r[0]];
				goal[1] = rect_m[num_r[1]];
				goal[2] = rect_m[num_r[2]];

				g = 0;
				gx = 0;
				pollen.x = 300;
				pollen.y = 10;
				pollen.r = 3;

				start();

				texture.draw();
				pollen.drawFrame(2, 0, Palette::White);

				for (int i = 0; i < 3; i++){
					font2(num[i]).draw(goal[i].x, goal[i].y + 5, Palette::Green);
				}

				WaitKey();

			}
		}//アウト判定

		const Point pos = Mouse::Pos();
		
		for (int i = 0; i < 3; i++){
			if (goal[i].intersects(pollen) && g < 0.2){
				se_get.setVolume(0.6);
				se_get.play();
				se_jet.stop();

				se_iyo.playMulti(0.05);
				se_gbgm.playMulti(0.05);
				//font(L"Game Clear").draw();
				pollen.y++;
				pollen.drawFrame(0, 1, Palette::White);
				if (goal[i].center.x - 1 <= pollen.center.x && pollen.center.x <= goal[i].center.x + 1){
					sum_score = num[i] * 2;
					font2(L"良!").draw(pollen.center.x - 7, pollen.center.y - 25, Palette::Red);
				}
				else {
					sum_score = num[i];
				}


				System::Update();
				System::Sleep(500);
				
				if (sum_score > 350){
					pollen.draw(Palette::Black);
					clear_image3.draw();
					score_rect.draw(Palette::Red);
					font(sum_score).draw(score_rect.center.x - 50, score_rect.center.y - 30);
					font(L"Pt").draw(score_rect.center.x + 35, score_rect.center.y - 30);
				}
				else{
					pollen.draw(Palette::Black);
					clear_image2.draw();
					score_rect.draw(Palette::Red);
					
					font(sum_score).draw(score_rect.center.x - 50, score_rect.center.y - 30);
					font(L"Pt").draw(score_rect.center.x + 35, score_rect.center.y - 30);
				}
				WaitKey();
				
				se_iyo.stopMulti();
				se_gbgm.stopMulti();
				{
					sum_score = 0;
					num[0] = RandomSelect({ score });
					num[1] = RandomSelect({ score });
					num[2] = RandomSelect({ score });

					num_r[0] = Random(7);
					num_r[1] = Random(7);
					num_r[2] = Random(7);

					while (num_r[0] == num_r[1])
					{
						num_r[1] = Random(7);
					}
					while (num_r[1] == num_r[2] || num_r[2] == num_r[0])
					{
						num_r[2] = Random(7);
					}

					goal[0] = rect_m[num_r[0]];
					goal[1] = rect_m[num_r[1]];
					goal[2] = rect_m[num_r[2]];

					g = 0;
					gx = 0;
					pollen.x = 300;
					pollen.y = 10;
					pollen.r = 3;

					start();

					texture.draw();
					pollen.drawFrame(2, 0, Palette::White);

					for (int i = 0; i < 3; i++){
						font2(num[i]).draw(goal[i].x, goal[i].y + 5, Palette::Green);
					}
					
					WaitKey();

				}
			}
		} //ゴール判定

		pollen.drawFrame(0, 1, Palette::White);
		if (Input::KeyZ.pressed){
			for (int i = 0; i < 3; i++){
				goal[i].draw(Palette::Blue);
				Point(goal[i].center.x, goal[i].y).draw(Palette::Red);
			}
		}

		/*
		Point first;
		if (Input::MouseL.clicked){
			first = pos;
		}

		if (Input::MouseL.pressed){
			Rect txtbox = { first, Mouse::Pos().x - first.x, Mouse::Pos().y - first.y };
			txtbox.draw(Color(0, 0, 225, 125));
		}
		if (Input::MouseL.released){
			Point second = Mouse::Pos();
			writer.writeln(first.x, L", ", second.y, L", ", second.x - first.x, L", ", first.y - second.y);
		}
		*/
	}
}


void start()
{
	const Image startj(L"Example/start.jpg");
	const Image startj2(L"Example/start2.jpg");
	const Sound bgm(L"Example/nc711.mp3");
	const Texture startw(startj);
	const Texture startw2(startj2);
	Font font(30);

	const Point pos(20, 100);
	const Point pos2(20, 160);

	bool flag = true;

	bgm.setPosSec(2);
	while (System::Update())
	{
		bgm.setVolume(0.06);
		bgm.play();
		startw.draw();
		if (Input::KeyUp.clicked){
			flag = true;
		}
		else if (Input::KeyDown.clicked){
			flag = false;
		}
		else if (Input::KeyEnter.clicked){
			if (flag){
				break;
			}
			else{
				System::Exit();
			}
		}

		font(L"START").draw(pos,flag ? Palette::Blue : Palette::Black, 1);
		font(L"EXIT").draw(pos2,flag ? Palette::Black : Palette::Blue, 1);
	}
	startw2.draw();
}