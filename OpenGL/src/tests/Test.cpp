#include "Test.h"
#include "imgui/imgui.h"
namespace test {

	TestMenu::TestMenu(Test*& currentTestPointer)
		: m_CurrentTest(currentTestPointer)
	{

	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))//如果按下了first里的数据的按钮，则执行second里面功能
				m_CurrentTest = test.second();//会返回一个Test*()指针
		}
	}

}

