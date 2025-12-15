#include "GameManager.h"
void GameManager::NewGame() {
	std::ifstream configFile("Config.txt");
	float totalTime = 0;
	float playerSpeed=6;
	float emySpeed=3;
	int emyNum=12;
	int treeNum=100;	
	int boxNum=12;
	int rockNum=20;
	int num_object01=30;
	int num_object02=30;
	int num_object03=30;
	int num_object04=30;
	float clock = 60;
	configFile >> clock;
	configFile >> playerSpeed;
	configFile >> emySpeed;
	configFile >> emyNum;
	configFile >> treeNum;
	configFile >> boxNum;
	configFile >> rockNum;
	configFile >> num_object01;
	configFile >> num_object02;
	configFile >> num_object03;
	configFile >> num_object04;
	System::Init();
	auto window = System::window.get();
	auto core = System::core.get();
	auto shaders = System::shaders.get();
	auto psos = System::psos.get();
	auto timer = System::timer.get();
	//
	//window->SetDisplayFullscreen(WIDTH, HEIGHT, 32);
	window->SetFullscreen();
	window->clipMouseToWindow();
	window->MouseCursor(false);
	auto cam = System::mainCamera;
	auto player = System::player;
	System::LoadModel("Models/TRex.gem", "Textures/emy.png", 1, 1);
	System::LoadModel("", "Textures/sand.png", 3, 1);
	System::LoadModel("Models/gun.gem", "Textures/gun.png", 0, 1);
	System::LoadModel("Models/tree01.gem", "Textures/tree.png", 0, 2);
	System::LoadModel("Models/rock.gem", "Textures/rock.png", 0, 3);
	System::LoadModel("Models/box.gem", "Textures/box.png", 0, 4);
	System::LoadModel("Models/grass.gem", "Textures/bush.png", 5, 1);
	System::LoadModel("Models/bush.gem", "Textures/bush.png", 5, 2);
	System::LoadModel("Models/grass01.gem", "Textures/grass00.png", 5, 3);
	System::LoadModel("Models/plant01.gem", "Textures/grass01.png", 5, 4);
	System::LoadModel("Models/leaf.gem", "Textures/leaf.png", 5, 5);
	
	//player->transform.scaling = Vec3(1.0f, 1.0f, 1.0f);
	cam->AddComponent(std::make_shared<Camera>());
	player->AddComponent(std::make_shared<Move>(playerSpeed));
	player->AddComponent(std::make_shared<Collision>(1, 0.5f, 1));
	//player->AddComponent(std::make_shared<Render>("Models/gun.gem", "Textures/role.png", 0, 1, Vec3(1000, 1000, 1000)));

	auto gun = GameObject::Create();
	gun->AddComponent(std::make_shared<Gun>());
	gun->AddComponent(std::make_shared<Render>("", "", 0, 1, Vec3(1000, 1000, 1000)));
	gun->AddComponent(std::make_shared<Image>("Textures/scope.png", Vec3(1.2f, 1.f, 1.f)));
	

	cam->AddComponent(std::make_shared<Raycast>(4));
	cam->AddComponent(std::make_shared<PlayerShoot>());
	cam->AddComponent(std::make_shared<Image>("Textures/aim.png", Vec3(0.1f, 0.1f, 0.1f)));
	//cam->AddComponent(std::make_shared<Render>(5));
	for (int i = 0; i < treeNum; i++) {
		auto tree = GameObject::Create();
		tree->transform.position = Vec3(randomRange(-50,50), 0, randomRange(-40, 40));
		tree->AddComponent(std::make_shared<Collision>(1, 0.5f, 6,0.5f));
		tree->AddComponent(std::make_shared<Render>("", "", 0,2, Vec3(300 * randomRange(0.6f, 1.2f), 300 * randomRange(0.6f, 1.2f), 300 * randomRange(0.6f, 1.2f))));
	}
	for (int i = 0; i < boxNum; i++) {
		auto b = GameObject::Create();
		b->transform.position = Vec3(randomRange(-40, 40), 1, randomRange(-40, 40));
		b->AddComponent(std::make_shared<Collision>(1, 2, 4, 2));
		b->AddComponent(std::make_shared<Render>("", "", 0, 4));
	}
	for (int i = 0; i < num_object01; i++) {
		auto g = GameObject::Create();
		g->transform.position = Vec3(randomRange(-40, 40), 1, randomRange(-40, 40));
		g->AddComponent(std::make_shared<Collision>(4, 2, 3, 2));
		g->AddComponent(std::make_shared<Render>("", "", 5, 1));
	}
	for (int i = 0; i < num_object02; i++) {
		auto g = GameObject::Create();
		g->transform.position = Vec3(randomRange(-40, 40), 1, randomRange(-40, 40));
		g->AddComponent(std::make_shared<Collision>(2, 2, 3, 2));
		g->AddComponent(std::make_shared<Render>("", "", 5, 2,Vec3(1000 * randomRange(0.8f, 1.2f),1000 * randomRange(0.8f, 1.2f),1000 * randomRange(0.8f, 1.2f))));
	}
	for (int i = 0; i < num_object03; i++) {
		auto g = GameObject::Create();
		g->transform.position = Vec3(randomRange(-40, 40), 1, randomRange(-40, 40));
		g->AddComponent(std::make_shared<Collision>(2, 2, 3, 2));
		g->AddComponent(std::make_shared<Render>("", "", 5, 3, Vec3(1000 * randomRange(0.8f, 1.2f), 1000 * randomRange(0.8f, 1.2f), 1000 * randomRange(0.8f, 1.2f))));
	}
	for (int i = 0; i < num_object04; i++) {
		auto g = GameObject::Create();
		g->transform.position = Vec3(randomRange(-40, 40), 1, randomRange(-40, 40));
		g->AddComponent(std::make_shared<Collision>(2, 2, 3, 2));
		g->AddComponent(std::make_shared<Render>("", "", 5, 4, Vec3(1000*randomRange(0.8f, 1.2f), 1000 * randomRange(0.8f, 1.2f), 1000 * randomRange(0.8f, 1.2f))));
	}
	for (int i = 0; i < rockNum; i++) {
		auto g = GameObject::Create();
		g->transform.position = Vec3(randomRange(-42, 42), 1, randomRange(-42, 42));
		g->AddComponent(std::make_shared<Collision>(3,0.8f,1));
		g->AddComponent(std::make_shared<Render>("", "", 0, 3, Vec3(randomRange(75,120), randomRange(75, 120), randomRange(75, 120))));
	}
	for (int i = 0; i < emyNum; i++) {
		auto g = GameObject::Create();
		float r = randomRange(0, 100);
		if (r < 25) {
			g->transform.position = Vec3(-52, 0, randomRange(-50, 50));
		}
		else if (r < 50)
		{
			g->transform.position = Vec3(52, 0, randomRange(-50, 50));
		}
		else if (r < 75)
		{
			g->transform.position = Vec3(randomRange(-50, 50), 0, -52);
		}
		else if (r < 101)
		{
			g->transform.position = Vec3(randomRange(-50, 50), 0, 52);
		}
		g->AddComponent(std::make_shared<Collision>(4, 3,6,3));
		g->AddComponent(std::make_shared<Render>("", "", 1, 1, Vec3(1, 1, 1)));
		g->AddComponent(std::make_shared<Enemy>(emySpeed));
	}
	///
	auto wall_01 = GameObject::Create();
	wall_01->transform.position = Vec3(0, 4, -50);
	wall_01->AddComponent(std::make_shared<Collision>(1,100,8,1));
	wall_01->AddComponent(std::make_shared<Render>("", "", 3, 1, Vec3(100, 8, 1)));
	auto wall_02 = GameObject::Create();
	wall_02->transform.position = Vec3(0, 4, 50);
	wall_02->AddComponent(std::make_shared<Collision>(1, 100, 8, 1));
	wall_02->AddComponent(std::make_shared<Render>("", "", 3, 1, Vec3(100, 8, 1)));
	auto wall_03 = GameObject::Create();
	wall_03->transform.position = Vec3(-50, 4, 0);
	wall_03->AddComponent(std::make_shared<Collision>(1, 1, 8, 100));
	wall_03->AddComponent(std::make_shared<Render>("", "", 3, 1, Vec3(1, 8, 100)));
	auto wall_04 = GameObject::Create();
	wall_04->transform.position = Vec3(50, 4, 0);
	wall_04->AddComponent(std::make_shared<Collision>(1, 1, 8, 100));
	wall_04->AddComponent(std::make_shared<Render>("", "", 3, 1, Vec3(1, 8, 100)));
	///
	auto ground = GameObject::Create();
	ground->transform.position = Vec3(0, 0.5f, 0);
	ground->AddComponent(std::make_shared<Render>("Models/tree.gem", "Textures/ground.png", 2, -1, Vec3(50, 1, 50)));

	auto start = GameObject::Create();
	start->m_IsActive = false;
	start->AddComponent(std::make_shared<Image>("Textures/JS.png", Vec3(1.f, 0.7f, 1.f)));

	auto win = GameObject::Create();
	win->m_IsActive = false;
	win->AddComponent(std::make_shared<Image>("Textures/win.png", Vec3(1.f, 0.7f, 1.f)));

	auto lose = GameObject::Create();
	lose->m_IsActive = false;
	lose->AddComponent(std::make_shared<Image>("Textures/lose.png", Vec3(1.f, 0.7f, 1.f)));
	bool quit = false;
	while (!quit)
	{
		if (System::gameState == -1)
		{
			core->beginFrame();
			window->checkInput();
			window->MouseInWindowLoop();
			if (window->GetKeyDown(VK_ESCAPE))
			{
				quit = true;
			}
			if (window->GetKeyDown(VK_RETURN) || window->GetKeyDown(VK_SPACE) || window->GetMouseButtonDown(0))
			{
				System::gameState = 0;
			}

			core->beginRenderPass();
			Matrix p = Matrix::perspective(0.01f, 10000.0f, WIDTH / HEIGHT, 60.0f);
			Matrix v = Matrix::lookAt(cam->transform.position, cam->transform.position + cam->transform.front(), Vec3(0, 1, 0));
			cam->GetComponent<Camera>()->vp = v * p;
			start->GetComponent<Image>()->uiRender();
			
			core->finishFrame();
		}
		else if (System::gameState==0)
		{
			core->beginFrame();
			float dt = timer->deltaTime;
			totalTime += dt;
			window->checkInput();
			window->MouseInWindowLoop();
			if (window->GetKeyDown(VK_ESCAPE))
			{
				quit = true;
			}
			if (totalTime>clock) {
				totalTime = 0;
				System::gameState = 1;
			}
			System::run();
			core->finishFrame();
		}
		else if (System::gameState == 1)
		{
			core->beginFrame();
			window->checkInput();
			window->MouseInWindowLoop();
			timer->dt();
			if (window->GetKeyDown(VK_ESCAPE))
			{
				quit = true;
			}
			clock += timer->deltaTime;
			if (clock > 2) {
				if (window->GetKeyDown(VK_RETURN) || window->GetKeyDown(VK_SPACE) || window->GetMouseButtonDown(0))
				{
					clock = 0;
					System::gameState = -1;
				}
			}
			core->beginRenderPass();
			Matrix p = Matrix::perspective(0.01f, 10000.0f, WIDTH / HEIGHT, 60.0f);
			Matrix v = Matrix::lookAt(cam->transform.position, cam->transform.position + cam->transform.front(), Vec3(0, 1, 0));
			cam->GetComponent<Camera>()->vp = v * p;
			win->GetComponent<Image>()->uiRender();

			core->finishFrame();
		}
		else if (System::gameState == 2)
		{
			core->beginFrame();
			window->checkInput();
			window->MouseInWindowLoop();
			timer->dt();
			if (window->GetKeyDown(VK_ESCAPE))
			{
				quit = true;
			}
			clock += timer->deltaTime;
			if (clock > 2) {
				if (window->GetKeyDown(VK_RETURN) || window->GetKeyDown(VK_SPACE) || window->GetMouseButtonDown(0))
				{
					clock = 0;
					System::gameState = -1;
				}
			}
			
			core->beginRenderPass();
			Matrix p = Matrix::perspective(0.01f, 10000.0f, WIDTH / HEIGHT, 60.0f);
			Matrix v = Matrix::lookAt(cam->transform.position, cam->transform.position + cam->transform.front(), Vec3(0, 1, 0));
			cam->GetComponent<Camera>()->vp = v * p;
			lose->GetComponent<Image>()->uiRender();

			core->finishFrame();
		}
	}
	core->flushGraphicsQueue();
}