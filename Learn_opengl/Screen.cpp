#include"Screen.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


Screen::Screen(int w, int h) :width(w), heigth(h)
{
	Init();
}

Screen::Screen() : width(800), heigth(600)
{
	Init();
}

void Screen::Display()
{
	glfwPollEvents();

	//�����Ļ�Լ�������
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwGetFramebufferSize(Screen::instance().window, &width, &heigth);
	glViewport(0, 0, width, heigth);
}

bool Screen::isClosed()
{
	return glfwWindowShouldClose(window);
}

void Screen::Init()
{
	glfwInit();//��ʼ��GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//����opengl�汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//����opengl�汾
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//ʹ�ú���ģʽ,ʹ�þɰ溯��ʱ�����
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//��ֹ�������ڴ�С

	window = glfwCreateWindow(width, heigth, "LearnOpenGL", nullptr, nullptr);//�������ڲ����ô��ڴ�С

	//����ʧ��ʱ
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);//�趨Ϊ��ǰ����
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	////��ʼ��GLEW,���ڹ���opengl�ĺ���ָ��
	glewExperimental = GL_TRUE;
	//��ʼ��ʧ��ʱ
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return;
	}
	//��ʼ��glad
	/*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return ;
	}*/

	//���ô���
	glViewport(0, 0, width, heigth);//ǰ���������������½ǵ�λ��
	//������Ȳ���
	glEnable(GL_DEPTH_TEST);


	// ��ʼ��imgui������
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// ����imguiģʽ
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// ����ImGui
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 100");
}