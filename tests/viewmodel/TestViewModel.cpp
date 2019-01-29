#include "google_test.h"
#include "toy_includes.h"
#include "viewitems.h"
#include "viewmodel.h"
#include <QDebug>

using namespace ModelView;

class TestViewModel : public ::testing::Test
{
public:
    ~TestViewModel();
};

TestViewModel::~TestViewModel() = default;

TEST_F(TestViewModel, initialState)
{
    ViewModel viewModel;
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}

TEST_F(TestViewModel, fromMultiLayer)
{
    ToyItems::SampleModel model;
    auto multiLayerItem = model.insertNewItem(ToyItems::Constants::MultiLayerType);

    ViewModel viewModel;
    viewModel.setSessionModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex mlIndex = viewModel.index(0, 0);

    // it should be ViewLabelItem looking at our MultiLayer item
    auto viewItem = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(mlIndex));
    EXPECT_TRUE(viewItem != nullptr);
    EXPECT_EQ(viewItem->item(), multiLayerItem);
}

//! Model with Layer. The layer has single property: thickness.

TEST_F(TestViewModel, fromLayer)
{
    ToyItems::SampleModel model;
    auto layerItem = model.insertNewItem(ToyItems::Constants::LayerType);

    // constructing viewModel from sample model
    ViewModel viewModel;
    viewModel.setSessionModel(&model);

    // root item should have one child, item looking at our layerItem
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing to viewItem representing layerItem
    QModelIndex layerIndex = viewModel.index(0, 0);
    auto viewItem = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(layerIndex));
    EXPECT_TRUE(viewItem != nullptr);
    EXPECT_EQ(viewItem->item(), layerItem);

    // it has one row and two columns, corresponding to our "thickness" property
    EXPECT_EQ(viewModel.rowCount(layerIndex), 1);
    EXPECT_EQ(viewModel.columnCount(layerIndex), 2);

    // accessing to views representing label and value of thickness property
    QModelIndex thicknessLabelIndex = viewModel.index(0, 0, layerIndex);
    auto thicknessLabelView
        = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(thicknessLabelIndex));
    EXPECT_TRUE(thicknessLabelView != nullptr);

    QModelIndex thicknessValueIndex = viewModel.index(0, 1, layerIndex);
    auto thicknessValueView
        = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(thicknessValueIndex));
    EXPECT_TRUE(thicknessValueView != nullptr);

    // internally, views for label and data should point to single SessionItem corresponding to
    // thickness property
    EXPECT_EQ(thicknessLabelView->item(), layerItem->getItem(ToyItems::Layer::P_THICKNESS));
    EXPECT_EQ(thicknessValueView->item(), layerItem->getItem(ToyItems::Layer::P_THICKNESS));
}

//! Model with VectorItem. The vector has three properties: x, y, z.

TEST_F(TestViewModel, fromVector)
{
    ToyItems::SampleModel model;
    auto vectorItem = model.insertNewItem(ToyItems::Constants::VectorType);

    // constructing viewModel from sample model
    ViewModel viewModel;
    viewModel.setSessionModel(&model);

    // root item should have one child, item looking at our vectorItem
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing to viewItem representing layerItem
    QModelIndex vectorIndex = viewModel.index(0, 0);

    // it has three rows and two columns, corresponding to our P_X, P_Y, P_Z
    EXPECT_EQ(viewModel.rowCount(vectorIndex), 3);
    EXPECT_EQ(viewModel.columnCount(vectorIndex), 2);

    // ViewLabelItem and ViewDataItem correspondint to P_X
    auto pxLabel
        = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(viewModel.index(0, 0, vectorIndex)));
    auto pxData
        = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(viewModel.index(0, 1, vectorIndex)));
    EXPECT_EQ(pxLabel->item(), vectorItem->getItem(ToyItems::Vector::P_X));
    EXPECT_EQ(pxData->item(), vectorItem->getItem(ToyItems::Vector::P_X));

    // ViewLabelItem and ViewDataItem correspondint to P_Y
    pxLabel
        = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(viewModel.index(1, 0, vectorIndex)));
    pxData
        = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(viewModel.index(1, 1, vectorIndex)));
    EXPECT_EQ(pxLabel->item(), vectorItem->getItem(ToyItems::Vector::P_Y));
    EXPECT_EQ(pxData->item(), vectorItem->getItem(ToyItems::Vector::P_Y));

    // ViewLabelItem and ViewDataItem correspondint to P_Z
    pxLabel
        = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(viewModel.index(2, 0, vectorIndex)));
    pxData
        = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(viewModel.index(2, 1, vectorIndex)));
    EXPECT_EQ(pxLabel->item(), vectorItem->getItem(ToyItems::Vector::P_Z));
    EXPECT_EQ(pxData->item(), vectorItem->getItem(ToyItems::Vector::P_Z));
}
