#pragma once
#include <string>

namespace fabCoreGL
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(float time) {};
		virtual void OnImGuiRender() {};
	protected:
		std::string m_name;
	};
}