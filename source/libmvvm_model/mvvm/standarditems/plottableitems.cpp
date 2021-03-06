// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/standarditems/plottableitems.h>

using namespace ModelView;

TextItem::TextItem() : CompoundItem(Constants::TextItemType)
{
    addProperty(P_TEXT, "")->setDisplayName("Text");
    addProperty(P_FONT, "Helvetica")->setDisplayName("Font");
    addProperty(P_SIZE, 12)->setDisplayName("Size");
}
