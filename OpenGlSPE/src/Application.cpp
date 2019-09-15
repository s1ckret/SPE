#include "Application.h"

Application::Application()
{
	if (!glfwInit())
		terminate();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		terminate();
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using OpenGL %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init("#version 130");
}

Application::~Application()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}

void Application::Run()
{
	GLfloat positions[] = {
		-5.f, -5.f,
		5.f, -5.f,
		5.f,  5.f,
		-5.f,  5.f
	};

	unsigned int indecies[]{
		0, 1, 2,
		2, 3, 0
	};

	VertexBuffer vb(positions, 8 * sizeof(float));
	VertexArray va;
	VertexBufferLayout vbl;
	vbl.Push<float>(2);
	va.AddBuffer(vb, vbl);

	IndexBuffer ib(indecies, 6);

	Shader shader("res/shaders/Basic.shader");
	shader.Bind();
	shader.setUniform4f("u_Color", 0.0, 0.0, 0.5, 1.0);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	Renderer renderer;

	float r = 0.f;
	float inc = 0.01f;
	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	glm::mat4 projection = glm::ortho(-20.f, 20.f, -20.f, 20.f, -1.0f, 1.0f);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		Draw();
		renderer.Clear();


		renderer.Draw(va, ib, shader);
		shader.setUniform4f("u_Color", r, 0.0f, 0.5f, 1.0);
		shader.setUniformMat4f("u_MVP", projection);
		ImGuiDraw();

		if (r > 1.0) {
			inc = -0.01f;
		}
		else if (r < 0.0) {
			inc = 0.01f;
		}

		r += inc;

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		HandleEvent();
	}

}

void Application::Init()
{
}

void Application::HandleInput()
{
}

void Application::Update(const float dt)
{
}

void Application::HandleEvent()
{
	glfwPollEvents();
}

void Application::Draw()
{
}

void Application::ImGuiDraw()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	{
		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}