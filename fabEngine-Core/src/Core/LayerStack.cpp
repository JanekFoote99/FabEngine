#include "LayerStack.h"

namespace fabCoreGL
{
  LayerStack::~LayerStack()
  {
    for (Layer* layer : m_Layers)
    {
      delete layer;
    }
  }

  void LayerStack::pushLayer(Layer* layer)
  {
    m_Layers.push_back(layer);
    layer->OnAttach();
  }

  void LayerStack::popLayer(Layer* layer)
  {
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    m_Layers.erase(it);
  }
}