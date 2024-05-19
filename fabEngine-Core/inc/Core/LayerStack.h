#pragma once
#include <Layer.h>
#include <vector>

namespace fabCoreGL
{
  class LayerStack
  {
  public:
    LayerStack() = default;
    ~LayerStack();

    void pushLayer(Layer* layer);
    void popLayer(Layer* layer);

    std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
    std::vector<Layer*>::iterator end() { return m_Layers.end(); }
  private:
    std::vector<Layer*> m_Layers;
  };
}