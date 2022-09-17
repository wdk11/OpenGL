#pragma once
#include "Test.h"

namespace test {

	class TestClearColor : public Test//继承了上个函数
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltatime) override;//override检查纯虚函数有没有被重写
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_ClearColor[4];//记录颜色

	};
}