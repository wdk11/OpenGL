#pragma once
#include "Test.h"

namespace test {

	class TestClearColor : public Test//�̳����ϸ�����
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltatime) override;//override��鴿�麯����û�б���д
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_ClearColor[4];//��¼��ɫ

	};
}