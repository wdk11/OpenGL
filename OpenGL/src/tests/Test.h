#pragma once
#include <functional>
#include <vector>
#include <string>
namespace test {
	class Test
	{
	public:
		Test() {};
		virtual ~Test() {};
		//û�ж��崿�麯������Ϊ���ǿ�����ѡ���ѡ����Щ�������Լ���Ҫʵ�ֵģ�������Ǵ��麯����ÿ������Ҫʵ��
		virtual void OnUpdate(float deltatime) {};//֡�����ǹ̶���
		virtual void OnRender() {};//������Ⱦ��
		virtual void OnImGuiRender() {};//IMGUI���õĵط�
	};

	class TestMenu : public Test//��Ҫ�������£������������в��Եļ��ϣ�����Ŷ������Ҫһ��ָ��Test���ָ��
		//���봢��һ�����ǿ����ṩTest������
		//�����Ǿ��ǳ����ڲ��Բ˵��еİ�ť��ǩ
	{
	public:
		TestMenu(Test*& currentTestPointer);

		void OnImGuiRender() override;//IMGUI���õĵط�
	private:
		Test*& m_CurrentTest;//ָ��currentTest��ָ����Ҫ�����ԭ������Ϊ���ǵĲ˵��ı䵱ǰӦ���л��currentTest
		//���������Ǵ������һ��Testָ������ã��������ǾͿ��Ըı䵱ǰ�Ĳ�����Ŀ
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;//������һ������
		//������һ���ɶԵ�������ÿһ�԰���һ���ַ����Լ�һ�����ز���ָ��ĺ�������������
	};
}