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
		//没有定义纯虚函数是因为我们可以有选择的选择哪些是我们自己想要实现的，如果都是纯虚函数就每个都需要实现
		virtual void OnUpdate(float deltatime) {};//帧速率是固定的
		virtual void OnRender() {};//用来渲染的
		virtual void OnImGuiRender() {};//IMGUI放置的地方
	};

	class TestMenu : public Test//主要做两件事，包含我们所有测试的集合，所以哦我们需要一个指向Test类的指针
		//还想储存一个我们可以提供Test的名称
		//所以那就是出现在测试菜单中的按钮标签
	{
	public:
		TestMenu(Test*& currentTestPointer);

		void OnImGuiRender() override;//IMGUI放置的地方
	private:
		Test*& m_CurrentTest;//指向currentTest的指针需要这个的原因是因为我们的菜单改变当前应用中活动的currentTest
		//在这里我们传入的是一个Test指针的引用，这样我们就可以改变当前的测试项目
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;//创建了一个容器
		//里面有一个成对的向量，每一对包含一个字符串以及一个返回测试指针的函数，不带参数
	};
}