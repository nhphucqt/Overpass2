#ifndef LAYER_VIEW_HPP
#define LAYER_VIEW_HPP

#include <ViewGroup.hpp>

class LayerView : public ViewGroup {
public:
    typedef std::unique_ptr<LayerView> Ptr;

public:
    LayerView();
    LayerView(EventPublisher* publisher);

protected:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif