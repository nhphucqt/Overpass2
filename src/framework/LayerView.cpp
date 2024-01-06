#include <LayerView.hpp>

LayerView::LayerView() {
    // Do nothing
}

LayerView::LayerView(EventPublisher* publisher) : ViewGroup(publisher) {
    // Do nothing
}

void LayerView::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    // Do nothing
}